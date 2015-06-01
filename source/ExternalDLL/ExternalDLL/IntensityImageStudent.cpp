#include "IntensityImageStudent.h"

std::vector<Intensity> IntensityImageStudent::getStorage() const{
	return m_pixelStorage;
}

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {}

//done
IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) :
IntensityImage(other.getWidth(), other.getHeight()) {
	m_pixelStorage = other.getStorage();
}

//done
IntensityImageStudent::IntensityImageStudent(const int width, const int height) :
IntensityImage(width, height) {
	m_pixelStorage.resize(height * width);
}

//done
IntensityImageStudent::~IntensityImageStudent() {}

//done
void IntensityImageStudent::set(const int width, const int height) {
	IntensityImage::set(width, height);
	m_pixelStorage.resize(height * width);
}

//done
void IntensityImageStudent::set(const IntensityImageStudent &other) {
	IntensityImage::set(other.getWidth(), other.getHeight());
	m_pixelStorage = other.getStorage();
}
//done
void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	m_pixelStorage[(y * getWidth()) + x] = pixel;
}
//done
void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	m_pixelStorage[i] = pixel;
}
//done
Intensity IntensityImageStudent::getPixel(int x, int y) const {
	return m_pixelStorage[(y * getWidth()) + x];
}
//done
Intensity IntensityImageStudent::getPixel(int i) const {
	return m_pixelStorage[i];
}