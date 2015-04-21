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
	m_pixelStorage[(y * this->getWidth()) + x] = pixel;
}

//done
void RGBImageStudent::setPixel(int i, RGB pixel) {
	m_pixelStorage[i] = pixel;
}

//done
RGB RGBImageStudent::getPixel(int x, int y) const {
	return m_pixelStorage[(y * this->getWidth()) + x];
}

//done
RGB RGBImageStudent::getPixel(int i) const {
	return m_pixelStorage[i];
}