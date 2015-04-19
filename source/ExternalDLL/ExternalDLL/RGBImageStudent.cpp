#include "RGBImageStudent.h"

std::vector<RGB> RGBImageStudent::getStorage() const{
	return m_pixelStorage;
}

//done
RGBImageStudent::RGBImageStudent() : RGBImage(){}
//(TODO)
RGBImageStudent::RGBImageStudent(const RGBImageStudent &other):
RGBImage(other.getWidth(), other.getHeight())
{
	m_pixelStorage = other.getStorage();
}

//done
RGBImageStudent::RGBImageStudent(const int width, const int height): 
RGBImage(width, height)
{
	m_pixelStorage.resize(height * width);
}

//done
RGBImageStudent::~RGBImageStudent(){}

//done
void RGBImageStudent::set(const int width, const int height) {
	RGBImage::set(width, height);
	m_pixelStorage.resize(width * height);
}
//done
void RGBImageStudent::set(const RGBImageStudent &other) {
	RGBImage::set(other.getWidth(), other.getHeight());
	m_pixelStorage = other.getStorage();
}

//done
void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	int pixelPosition = (y * this->getWidth()) + x;
	if (pixelPosition < static_cast<int>(m_pixelStorage.size()) && pixelPosition >= 0){
		m_pixelStorage[pixelPosition] = pixel;
	}
}

//done
void RGBImageStudent::setPixel(int i, RGB pixel) {
	if (i < static_cast<int>(m_pixelStorage.size()) && i >= 0){
		m_pixelStorage[i] = pixel;
	}
}

//done
RGB RGBImageStudent::getPixel(int x, int y) const {
	int pixelPosition = (y * this->getWidth()) + x;
	if (pixelPosition < static_cast<int>(m_pixelStorage.size()) && pixelPosition >= 0){
		return m_pixelStorage[pixelPosition];
	}else{
		return 0;
	}
}

//done
RGB RGBImageStudent::getPixel(int i) const {
	if (i < static_cast<int>(m_pixelStorage.size()) && i >= 0){
		return m_pixelStorage[i];
	}else{
		return 0;
	}
}