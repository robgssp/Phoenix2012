#ifndef IMAGETRACKER_H
#define IMAGETRACKER_H
#include "Robot.h"
#include "nivision.h"
#include <vector>

class ImageTracker {
	Robot *robot_;
	Image *image;
	std::vector<RectangleMatch> matches;
public:
	ImageTracker(Robot *robot);
	/**
	 * Gets the latest image from the camera and analyzes it.
	 * Use horizOffset() for tracking purposes.
	 */
	void updateImage();
	double horizOffset();
};

#endif
