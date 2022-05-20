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
	std::vector<Mesh> meshes;
	// Creates a blank model
	Model();
	// Creates a model using data from the filePath
	// Must point towards a 3D model file supported by ASSIMP
	Model(std::string filePath);
	// Creates a model by copying another model
	Model(Model model, const std::shared_ptr<Material> mat);
	bool addMesh(Mesh& mesh);
	bool IsHit(Ray ray, float t0, float t1, HitData& record);
	BoundingBox boundingBox() const;
	glm::vec3 Color(HitData& hitData, WorldState& world);
	glm::vec3 GetSurfaceNormal(HitData& hitData);
	glm::vec3 GetUnitSurfaceNormal(HitData& hitData);
	glm::vec3 GetIntersectionPoint(HitData& hitData);
private:
	
};

// Class with static methods used to import a model from file
// Uses ASSIMP
class ModelImporter {
public:
	static Model loadModel(std::string filePath);
private:
	static bool processNode(aiNode* node, const aiScene* scene, Model& model);
	static bool processMesh(aiMesh* mesh, const aiScene* scene, Model& model);
};