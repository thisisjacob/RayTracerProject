#pragma once
#include <vector>
#include <glm/glm.hpp>

// Used to hold an manipulate data of a raytraced image
class RTImage {
public:
	RTImage();
	RTImage(int newWidth, int newHeight);
	// The pixel data
	// Only direct modification should be changing existing values
	std::vector<glm::vec3> pixels;
	int getHeight();
	void setHeight(int newHeight);
	int getWidth();
	void setWidth(int newWidth);
	// Resets all of the pixel data, but preserves the height and width
	void erasePixels();
	// Resizes the pixel array and resets the data
	void resizePixels(int newWidth, int newHeight);
private:
	int height;
	int width;
};