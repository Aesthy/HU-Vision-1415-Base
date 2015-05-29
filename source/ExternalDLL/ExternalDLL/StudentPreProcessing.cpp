#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"
#include <tuple>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <array>

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	int imageSize = image.getWidth() * image.getHeight();
	IntensityImageStudent* IM = new IntensityImageStudent(image.getWidth(),image.getHeight());
	RGB rgb;
	for (int i = 0; i < imageSize; ++i){
		rgb = image.getPixel(i);
		//Intensity p = (0.2126 * rgb.r) + (0.7152 * rgb.g) + (0.0722 * rgb.b);
		Intensity p = rgb.g;
		IM->setPixel(i, p);
	}	
	return IM;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	IntensityImageStudent* IM = new IntensityImageStudent(image.getWidth(), image.getHeight());
	if (image.getWidth() * image.getHeight() <= 40000){
		for (int y = 0; y < image.getHeight(); ++y){
			for (int x = 0; x < image.getWidth(); ++x){
				IM->setPixel(x, y, image.getPixel(x, y));
			}
		}
		return IM;
	}
	int pixelCount = image.getHeight() * image.getWidth();
	float mult = static_cast<float>(40000) / pixelCount;
	mult = sqrt(mult);
	IM = new IntensityImageStudent(image.getWidth() * mult, image.getHeight() * mult);

	float newIntensity = 0;
	for (int y = 0; y < IM->getHeight(); ++y){
		for (int x = 0; x < IM->getWidth(); ++x){
			float oldX = x / mult;
			float oldY = y / mult;
			float dX = 1 - (oldX - floor(oldX));
			float dY = 1 - (oldY - floor(oldY));
			newIntensity = (dX * dY) * image.getPixel(floor(oldX), floor(oldY));
			newIntensity += ((1 - dX) * dY) * image.getPixel(floor(oldX) + 1, floor(oldY));
			newIntensity += (dX * (1 - dY)) * image.getPixel(floor(oldX), floor(oldY) + 1);
			newIntensity += ((1 - dX) * (1 - dY)) * image.getPixel(floor(oldX) + 1, floor(oldY) + 1);
			IM->setPixel(x , y, newIntensity);
		}
	}
	return IM;
}

IntensityImage* StudentPreProcessing::applyGaussian(const IntensityImage &image, int kernelSize) const{
	//Creating kernel
	double normalisationFactor = 0;
	double sigma = 2.5;
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
			IM->setPixel(x, y, (sum / normalisationFactor));
		}
	}
	return IM;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	//std::array<int, 9 * 9> kernel{ {
	//		0, 0, 0, 1, 1, 1, 0, 0, 0,
	//		0, 0, 0, 1, 1, 1, 0, 0, 0,
	//		0, 0, 0, 1, 1, 1, 0, 0, 0,
	//		1, 1, 1, -4, -4, -4, 1, 1, 1,
	//		1, 1, 1, -4, -4, -4, 1, 1, 1,
	//		1, 1, 1, -4, -4, -4, 1, 1, 1,
	//		0, 0, 0, 1, 1, 1, 0, 0, 0,
	//		0, 0, 0, 1, 1, 1, 0, 0, 0,
	//		0, 0, 0, 1, 1, 1, 0, 0, 0
	//	} };
	std::array<int, 3 * 3> kernel{ {
			0, 1, 0,
			1,-4, 1,
			0, 1, 0, 
		} };

	IntensityImageStudent* IM = new IntensityImageStudent(image.getWidth(), image.getHeight());
	int imageWidth = image.getWidth();
	int sum = 0;
	int temp = 0;
	int maxX = image.getWidth() - 4;
	int maxY = image.getHeight() - 4;
	for (int y = 4; y < maxY; ++y){
		for (int x = 4; x < maxX; ++x){
			sum = 0;
			//for (int ky = 0; ky < 3; ++ky){
				//for (int kx = 0; kx < 3; ++kx){
					temp = 0;
					//if (kernel[ky * 3 + kx] == 0) {
						//continue;
					//}
					for (int by = 0; by < 3; ++by){
						for (int bx = 0; bx < 3; ++bx){
							sum += image.getPixel((x - 4 - (3 + bx)) + imageWidth * (y - 4 - (0 + by)));
							sum += image.getPixel((x - 4 - (0 + bx)) + imageWidth * (y - 4 - (3 + by)));
							sum += image.getPixel((x - 4 - (6 + bx)) + imageWidth * (y - 4 - (3 + by)));
							sum += image.getPixel((x - 4 - (3 + bx)) + imageWidth * (y - 4 - (6 + by)));
							temp += image.getPixel((x - 4 - (3 + bx)) + imageWidth * (y - 4 - (3 + by)));
						}
					}
					sum += temp * -4;

					//if (kernel[ky * 9 + kx] == 0) continue;
					//sum += image.getPixel((x - kx - 4) + imageWidth * (y - ky - 4)) * kernel[ky * 9 + kx];
				/*}
			}*/
			if (sum > 255){
				sum = 255;
			}
			if (sum < 0){
				sum = 0;
			}
			IM->setPixel(x - 4 + imageWidth * (y - 4), sum);
		}
	}
	return IM;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImageStudent* IM = new IntensityImageStudent(image.getWidth(), image.getHeight());
	int imageSize = image.getWidth() * image.getHeight();
	for (int i = 0; i < imageSize; ++i){
		Intensity p = image.getPixel(i);
		if (p > 200){
			IM->setPixel(i, 0);
		}
		else{
			IM->setPixel(i, 255);
		}
	}
	return IM;
}