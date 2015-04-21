#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"
#include <tuple>
IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	int imageSize = image.getWidth() * image.getHeight();
	IntensityImageStudent* IM = new IntensityImageStudent(image.getWidth(),image.getHeight());
	RGB rgb;
	for (int i = 0; i < imageSize; ++i){
		rgb = image.getPixel(i);
		Intensity p = (0.2126 * rgb.r) + (0.7152 * rgb.g) + (0.0722 * rgb.b);
		IM->setPixel(i, p);
	}	
	return IM;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	IntensityImageStudent* IM = new IntensityImageStudent(image.getWidth(), image.getHeight());
	std::vector<std::tuple<int, int, int>> neighbours = {
		( 0, 0, 4) };
		//{ 0, 0, 4 },
		//{ -1, 0, 1 },
		//{ 1, 0, 1 },
		//{ 0, -1, 1 },
		//{ 0, 1, 1 },
		//{ -1, -1, 1 },
		//{ -1, 1, 1 },
		//{ 1, 1, 1 },
		//{ 1, -1, 1 } };

	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}