#pragma once
#include "glm/glm.hpp"
#include <vector>

class Camera {
private:
	int imageWidth;
	int imageHeight;
	float focalLength;
	float aspectRatio;
	glm::vec3 eye;
	glm::vec3 dir;
public:
	Camera();
	// Sets up a campera positioned at eyePos, pointing towards dir
	Camera(int imageWidth, int imageHeight, glm::vec3 eyePos, glm::vec3 dir, float focalLength);
	// Generates x/y offsets used from generating rays from the camera position that point towards pixels on the image plane
	// U is the x offset, V is the y offset
	float GetUValue(int xPixel) const;
	float GetVValue(int yPixel) const;
	glm::vec3 getEye() const;
	void setEye(glm::vec3 eye);
	glm::vec3 getDir() const;
	void setDir(glm::vec3 dir);
	int GetImageWidth() const;
	int GetImageHeight() const;
	// Distance of the image plane from the camera position
	float GetFocalLength() const;
	float GetAspectRatio() const;
	// Updates the viewport size and aspect ratio
	bool resizeImagePlane(int newWidth, int newHeight);
};