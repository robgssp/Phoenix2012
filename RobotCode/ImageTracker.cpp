#include "ImageTracker.h"
#include "Log.h"

ImageTracker::ImageTracker(Robot *robot) {
	this->robot_ = robot;
	image_ = imaqCreateImage(IMAQ_IMAGE_HSL, DEFAULT_BORDER_SIZE);
	processedImage_ = imaqCreateImage(IMAQ_IMAGE_U8, DEFAULT_BORDER_SIZE);
	processedImage_ = NULL;
	loopCount_ = 0;
}

static Range selectAll = {0, 255};
static Range selectLuminance = {240, 255};
static ParticleFilterCriteria2 particleCiteria[] = {{
		IMAQ_MT_BOUNDING_RECT_WIDTH,
		0, 20, // lower and upper bounds for particle match
		FALSE, FALSE // not calibrated values, not exclusive values
}, {
		IMAQ_MT_BOUNDING_RECT_HEIGHT,
		0, 20, // lower and upper bounds for particle match
		FALSE, FALSE // not calibrated values, not exclusive values
}};

const ParticleFilterOptions2 particleOpts = {
		TRUE, // reject matches
		TRUE, // reject border
		TRUE, // fill holes
		TRUE  // use connectivity-8
};

static RectangleDescriptor rectangleDescriptor = {
	100, 500, 100, 500
};

/**
 * Gets the latest image from the camera and analyzes it.
 * Use horizOffset() for tracking purposes.
 */
void ImageTracker::updateImage() {
	robot_->camera->GetImage(image_);
	
	imaqDispose(processedImage_);
	imaqCreateImage(IMAQ_IMAGE_U8, DEFAULT_BORDER_SIZE);
	imaqExtractColorPlanes(image_, IMAQ_HSL, NULL, NULL, processedImage_);
	
	imaqThreshold(processedImage_, processedImage_, 230, 255, TRUE, 1.0);
	
	int numParticles = 0;
	imaqParticleFilter4(processedImage_, processedImage_, particleCiteria, 2, &particleOpts, NULL, &numParticles);
	
	int matchCount = 0;
	RectangleMatch *temp = imaqDetectRectangles(
			processedImage_, &rectangleDescriptor, NULL, NULL, NULL, &matchCount);
	
	robot_->log->info("%d matches", matchCount);
	robot_->log->info("looped %d times", ++loopCount_);
	
	matches_.clear();
	for(int i = 0; i < matchCount; ++i) matches_.push_back(temp[i]);
	imaqDispose(temp);
}

void ImageTracker::writeFiles() {
	RGBValue colorTable[256];
	memset(colorTable, 0, sizeof(colorTable));
	colorTable[0].R = 0;
	colorTable[1].R = 255;
	colorTable[0].G = colorTable[1].G = 0;
	colorTable[0].B = colorTable[1].B = 0;
	colorTable[0].alpha = colorTable[1].alpha = 0;
	int error = imaqWriteFile(processedImage_, "/analyzed.png", colorTable);
	robot_->log->info("%s", imaqGetErrorText(error));
}

std::vector<RectangleMatch> ImageTracker::matches() { return matches_; }
