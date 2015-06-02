#include "StudentLocalization.h"
#include <iostream>
#include <fstream>
#include <string>
#include "ImageIO.h"
#include <utility>

#include <math.h>
#include <cstdio>
#include <sstream>
#include "SonnetXVIII.h"
#include "HereBeDragons.h"
#include "RGBImageStudent.h"
#include "ImageFactory.h"

bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	
	int imageHeight = image.getHeight();
	int imageWidth  = image.getWidth();

	int samples = 10;
	int sampleHeight = imageHeight / samples;

	std::vector<int> blackGraphY(imageHeight);
	std::vector<std::vector<int>> blackGraphsX(samples, std::vector<int>(imageWidth));

	//histogram y
	for (int y = 0; y < imageHeight; y++){
		for (int x = 0; x < imageWidth; x++){
			if (image.getPixel(x, y) == 0){
				blackGraphY[y]++;
			}
		}
	}
	//histogrammen x
	for (int i = 0; i < samples; i++){
		int yHeigth = i * sampleHeight;
		for (int x = 0; x < imageWidth; x++){
			for (int y = yHeigth; y < yHeigth + sampleHeight; y++){
				if (image.getPixel(x, y) == 0){
					blackGraphsX[i][x]++;
				}
			}
		}
	}


	
	std::pair<int, int> headTop;
	int peakBegin = 0 , peakEnd = 0, headTopY;
	bool peakFound = false;

	//Headtop y
	for (int i = 0; i < blackGraphY.size(); ++i){
		if (blackGraphY[i] > 5){
			headTopY = i;
			headTop.second = i;
			break;
		}
	}
	//headTop x links
	for (int j = 0; j < blackGraphsX[headTopY / sampleHeight].size(); j++){
		if (blackGraphsX[headTopY / sampleHeight][j] > 2){
			if (!peakFound){
				peakBegin = j;
			}
		}
	}
	//headTop x rechts
	for (int j = blackGraphsX[headTopY / sampleHeight].size(); j > 0; j--){
		if (blackGraphsX[headTopY / sampleHeight][j] > 2){
			if (!peakFound){
				peakEnd = j;
			}
		}
	}
	headTop.first = (peakBegin + peakEnd)/2;
	



	std::pair<int, int> headWidth(0, 0);
	int height = 0;
	bool breaak = false;
	
	peakFound = false;
	//Head links
 	for (int i = 0; i < blackGraphsX.size(); i++){
		for (int j = 0; j < blackGraphsX[i].size(); j++){
			if (blackGraphsX[i][j] > 5){
				if (headWidth.first == 0){
					headWidth.first = j;
					break;
				}
				else if (j < (headWidth.first + 2)){
					headWidth.first = j;
					height = i *sampleHeight;
					break;
				}
				else if(headWidth.first != 0){
					breaak = true;
					break;
				}
			}
		}
		if (breaak){
			break;
		}
	}

	breaak = false;
	//head rechts
	for (int i = 0; i < blackGraphsX.size(); i++){
		for (int j = blackGraphsX[i].size(); j > 0; j--){// Due rand
			if (blackGraphsX[i][j] > 5){
				if (headWidth.second == 0){
					headWidth.second = j;
					break;
				}
				else if (j > (headWidth.second -2)){
					headWidth.second = j;
					height = i *sampleHeight;
					break;
				}
				else if (headWidth.second != 0){
					breaak = true;
					break;
				}
			}
		}
		if (breaak){
			break;
		}
	}

	//gemiddelde waarde y histogram
	int averageY = 0;
	int max = 0;
	int div;
	for (int i = 0; i < blackGraphY.size(); i++){
		if (blackGraphY[i] > max){
			max = blackGraphY[i];
		}
		averageY += blackGraphY[i];
	}

	averageY = averageY / blackGraphY.size();
	div = (max - averageY) / 4;
	


	//wangenY
	int cheekHeight = 0;
	for (int i = height; i < blackGraphY.size(); ++i){
		if (blackGraphY[i] <= averageY + div){
			if (!peakFound){
				peakBegin = i;
				peakFound = true;
			}
		}
		else if (peakFound && (i - peakBegin) >  10){
			cheekHeight = peakBegin + (i - peakBegin) / 2;
			peakFound = false;
			break;
		}
		else{
			peakFound = false;
		}
	}



	std::pair<int, int> wang1;
	std::pair<int, int> wang2;

	int whitesFound = 0;
	int wangenHoogte = 0;
	bool sideFound = 
	peakFound = false;
	//Wangen x
	for (int i = (cheekHeight / sampleHeight); i < (cheekHeight / sampleHeight) + 2; i++){
		for (int j = headWidth.first; j <= headWidth.second; j++){
			if (blackGraphsX[i][j] > 5){
				sideFound = true;
			}
			if (blackGraphsX[i][j] < 5 && sideFound){
				if (!peakFound){
					if (whitesFound == 0){
						wang1.first = j;
						wangenHoogte = (i * sampleHeight) + (sampleHeight /3);
						peakFound = true;
					}
					else{
						wang2.first = j;
						wangenHoogte = (i * sampleHeight) + (sampleHeight / 3);
						peakFound = true;
					}
				}
			}
			else if (peakFound){
				if (whitesFound == 0){
					if ((j - wang1.first) > (headWidth.second - headWidth.first) / 6){
						wang1.second = j;
						whitesFound++;
					}
					peakFound = false;
				
				}
				else{
					if ((j - wang2.first) > (headWidth.second - headWidth.first) / 6){
						wang2.second = j;
						whitesFound++;
					}
					peakFound = false;
				}
			}
			if (whitesFound == 2){
				break;
			}
		}
		sideFound = false;
		if (whitesFound == 2){
			break;
		}
	}
	
	for (int j = 0; j < blackGraphsX[wangenHoogte/sampleHeight].size(); j++){
		if (blackGraphsX[wangenHoogte / sampleHeight][j] > 8){
			headWidth.first = (headWidth.first + j) / 2;
			break;
		}
	}

	for (int j = blackGraphsX[wangenHoogte / sampleHeight].size(); j > 0; j--){
		if (blackGraphsX[wangenHoogte / sampleHeight][j] > 8){
			headWidth.second = (headWidth.second + j) / 2;
			break;
		}
	}

	features.putFeature(Feature(Feature::FEATURE_HEAD_TOP, Point2D<double>(headTop.first, headTop.second)));
	features.putFeature(Feature(Feature::FEATURE_HEAD_LEFT_SIDE, Point2D<double>(headWidth.first, wangenHoogte)));
	features.putFeature(Feature(Feature::FEATURE_HEAD_RIGHT_SIDE, Point2D<double>(headWidth.second, wangenHoogte)));

	return true;
}

bool StudentLocalization::stepFindNoseMouthAndChin(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindChinContours(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}