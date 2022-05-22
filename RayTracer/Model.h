#pragma once
#include "Surface.h"
#include "Mesh.h"
#include <vector>
#include "glm/glm.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
// INCLUDES FOR DEVELOPMENT
#include "BaseShader.h"

// Class for holding data on a model
class Model : public Surface {
public:
	Model();
	// Creates a model using data from the filePath
	// Must point towards a 3D model file supported by ASSIMP
	Model(std::string filePath, std::shared_ptr<Material> mat);
	bool addMesh(Mesh& mesh);
	bool IsHit(const std::shared_ptr<Surface>& callingSurface, Ray ray, float t0, float t1, HitData& record);
	BoundingBox boundingBox() const;
	glm::vec3 Color(HitData& hitData, WorldState& world);
	glm::vec3 GetSurfaceNormal(HitData& hitData);
	glm::vec3 GetUnitSurfaceNormal(HitData& hitData);
	glm::vec3 GetIntersectionPoint(HitData& hitData);
private:
	std::vector<Mesh> meshes;
};

// Class with static methods used to import a model from file
// Uses ASSIMP
class ModelImporter {
public:
	static Model loadModel(std::string filePath, std::shared_ptr<Material> mat);
private:
	static bool processNode(aiNode* node, const aiScene* scene, Model& model);
	static bool processMesh(aiMesh* mesh, const aiScene* scene, Model& model);
};