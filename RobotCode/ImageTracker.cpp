#include "ImageTracker.h"

ImageTracker::ImageTracker(Robot *robot) {
	this->robot_ = robot;
	image = NULL;
}

static Range redRange = {133, 158};
static Range greenRange = {152, 168};
static Range blueRange = {146, 171};
static ParticleFilterCriteria2 particleCiteria[] = {{
		IMAQ_MT_BOUNDING_RECT_WIDTH,
		0, 20, // lower and upper bounds for particle match
		FALSE, FALSE // not calibrated values, not exclusive values
}, {
		IMAQ_MT_BOUNDING_RECT_HEIGHT,
		0, 20, // lower and upper bounds for particle match
		FALSE, FALSE // not calibrated values, not exclusive values
}};

static RectangleDescriptor rectangleDescriptor = {
	100, 500, 100, 500
};

const ParticleFilterOptions2 particleOpts = {
		TRUE, // reject matches
		TRUE, // reject border
		TRUE, // fill holes
		TRUE  // use connectivity-8
};

void ImageTracker::updateImage() {
	if(image) imaqDispose(image);
	robot_->camera->GetImage(image);
	
	int bordersize;
	imaqGetBorderSize(image, &bordersize);
	ImageType type;
	imaqGetImageType(image, &type);
	
	Image *processedImage = imaqCreateImage(type, bordersize);
	
	imaqColorThreshold(processedImage, image, 1, IMAQ_HSV, &redRange, &greenRange, &blueRange);
	imaqParticleFilter4(processedImage, processedImage, particleCiteria, 2, &particleOpts, NULL, NULL);
	int matchCount;
	RectangleMatch *temp = imaqDetectRectangles(
			processedImage, &rectangleDescriptor, NULL, NULL, NULL, &matchCount);
	
	matches.clear();
	for(int i = 0; i < matchCount; ++i) matches.push_back(temp[i]);
	imaqDispose(temp);
	imaqDispose(processedImage);
}
