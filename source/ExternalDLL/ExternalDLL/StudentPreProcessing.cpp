#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	int imageSize = image.getWidth() * image.getHeight();
	IntensityImageStudent* IM = new IntensityImageStudent(image.getWidth(),image.getHeight());
	for (int i = 0; i < imageSize; ++i){
		//Intensity p = (0.2126 * image.getPixel(i).r) + (0.7152 * image.getPixel(i).g) + (0.0722 * image.getPixel(i).b);
		Intensity p = (0.5 * image.getPixel(i).r) + (0 * image.getPixel(i).g) + (0.5 * image.getPixel(i).b);
		IM->setPixel(i, p);
	}	
	return IM;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}