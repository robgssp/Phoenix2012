#ifndef IMAGETRACKER_H
#define IMAGETRACKER_H
#include "Robot.h"
#include "nivision.h"
#include <vector>

class ImageTracker {
	Robot *robot_;
	Image *image_;
	Image *processedImage_;
	std::vector<RectangleMatch> matches_;
	int loopCount_;
public:
	ImageTracker(Robot *robot);
	void updateImage();
	double horizOffset();
	void writeFiles();
	std::vector<RectangleMatch> matches();
};

#endif
