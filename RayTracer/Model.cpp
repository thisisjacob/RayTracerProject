#include "Model.h"

Model::Model() {}

Model::Model(std::string filePath) {
	Model model = ModelImporter::loadModel(filePath);
	this->meshes = model.meshes;
	this->mat = model.mat;
}

Model::Model(Model model, const std::shared_ptr<Material> mat) {
	for (Mesh& mesh : model.meshes)
		this->meshes.push_back(mesh);

	this->mat = mat;

}

bool Model::addMesh(Mesh& mesh) {
	meshes.push_back(mesh);
	return true;
}

bool Model::IsHit(Ray ray, float t0, float t1, HitData& record) {
	bool res = false;
	for (const Mesh& mesh : meshes) {
		for (Triangle surface : mesh.surfaces) {
			res = res || surface.IsHit(ray, t0, record.T, record);
		}
	}
	return res;
}

BoundingBox Model::boundingBox() const {
	return BoundingBox(glm::vec3(), glm::vec3());
}

glm::vec3 Model::Color(HitData& record, WorldState& world) {
	return mat->Shading(record, world);
}

glm::vec3 Model::GetSurfaceNormal(HitData& record) {
	return glm::vec3();
}

glm::vec3 Model::GetUnitSurfaceNormal(HitData& record) {
	return glm::vec3();
}

glm::vec3 Model::GetIntersectionPoint(HitData& record) {
	return glm::vec3();
}

Model ModelImporter::loadModel(std::string filePath) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate);

	Model model = Model();
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Error importing model in file path: " << filePath << "\n";
	}

	processNode(scene->mRootNode, scene, model);
	return model;
}

bool ModelImporter::processNode(aiNode* node, const aiScene* scene, Model& model) {
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene, model);
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene, model);
	}

	return true;
}

bool ModelImporter::processMesh(aiMesh* mesh, const aiScene* scene, Model& model) {
	Mesh newMesh;
	for (int i = 0; i < mesh->mNumVertices; i += 3) {
		glm::vec3 aVertex;
		aVertex.x = mesh->mVertices[i].x;
		aVertex.y = mesh->mVertices[i].y;
		aVertex.z = mesh->mVertices[i].z;
		glm::vec3 bVertex;
		bVertex.x = mesh->mVertices[i + 1].x;
		bVertex.y = mesh->mVertices[i + 1].y;
		bVertex.z = mesh->mVertices[i + 1].z;
		glm::vec3 cVertex;
		cVertex.x = mesh->mVertices[i + 2].x;
		cVertex.y = mesh->mVertices[i + 2].y;
		cVertex.z = mesh->mVertices[i + 2].z;
		// TESTING SHADER - DELETE LATER
		std::shared_ptr<Material> shader2 = std::make_shared<BlinnPhong>();
		std::dynamic_pointer_cast<BlinnPhong>(shader2)->SetDiffuseCoeff(glm::vec3(0.2, 0.2, 0.7));
		std::dynamic_pointer_cast<BlinnPhong>(shader2)->SetAmbientCoeff(glm::vec3(0.2, 0.2, 0.7));
		std::dynamic_pointer_cast<BlinnPhong>(shader2)->SetAmbientIntensity(glm::vec3(0.2, 0.2, 0.2));
		std::dynamic_pointer_cast<BlinnPhong>(shader2)->SetSpecularCoeff(glm::vec3(0.5, 0.5, 0.5));
		std::dynamic_pointer_cast<BlinnPhong>(shader2)->SetPhongExponent(16.0);
		newMesh.surfaces.push_back(Triangle(aVertex, bVertex, cVertex, shader2));
	}
	model.addMesh(newMesh);
	return true;
}