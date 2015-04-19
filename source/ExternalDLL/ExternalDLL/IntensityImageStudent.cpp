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
	int pixelPosition = (y * this->getWidth()) + x;
	if (pixelPosition < static_cast<int>(m_pixelStorage.size()) && pixelPosition >= 0){
		m_pixelStorage[pixelPosition] = pixel;
	}
}
//done
void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	if (i < static_cast<int>(m_pixelStorage.size()) && i >= 0){
		m_pixelStorage[i] = pixel;
	}
}
//done
Intensity IntensityImageStudent::getPixel(int x, int y) const {
	int pixelPosition = (y * this->getWidth()) + x;
	if (pixelPosition < static_cast<int>(m_pixelStorage.size()) && pixelPosition >= 0){
		return m_pixelStorage[pixelPosition];
	}
	else{
		return 0;
	}
}
//done
Intensity IntensityImageStudent::getPixel(int i) const {
	if (i < static_cast<int>(m_pixelStorage.size()) && i >= 0){
		return m_pixelStorage[i];
	}
	else{
		return 0;
	}
}