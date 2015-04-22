#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"
#include <tuple>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

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


IntensityImage* StudentPreProcessing::applyGaussian(const IntensityImage &image, int kernelSize) const{
	//Creating kernel
	double normalisationFactor = 0;
	double sigma = kernelSize/3;
	std::vector<std::tuple<int, int, double>> kernel;
	kernel.resize(kernelSize * kernelSize);
	for (int y = 0; y < kernelSize; ++y){
		for (int x = 0; x < kernelSize; ++x){
			int dX = x - (kernelSize / 2);
			int dY = y - (kernelSize / 2);
			double gaussian =  1 / (2 * M_PI * sigma * sigma)  * std::exp(-(dX * dX + dY * dY) / (2 * sigma * sigma));
			kernel[y * kernelSize + x] = std::make_tuple(dX, dY, gaussian );
			normalisationFactor += gaussian;
		}
	}

	//Applying kernel
	IntensityImageStudent* IM = new IntensityImageStudent(image.getWidth(), image.getHeight());
	int maxY = image.getHeight() - (kernelSize / 2);
	int maxX = image.getWidth() - (kernelSize / 2);
	double sum = 0;
	for (int y = kernelSize / 2; y < maxY; ++y){
		for (int x = kernelSize / 2; x < maxX; ++x){
			sum = 0;
			for (auto pixel : kernel){
				sum += image.getPixel(x + std::get<0>(pixel), y + std::get<1>(pixel)) * std::get<2>(pixel);
			}
			//std::cout << sum  << std::endl;
			IM->setPixel(x, y, (sum / normalisationFactor));
		}
	}
	return IM;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	IntensityImageStudent* IM = new IntensityImageStudent(image.getWidth(), image.getHeight());
	int imageSize = image.getWidth() * image.getHeight();
	applyGaussian(*IM, 5);
	return IM;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}