#pragma once

#include "Game.h"
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>       
#include <assimp/postprocess.h> 
#include "ECS.h"
#include "Components.h"
#include "MeshNoComponent.h"

class TransformComponent;
class ModelEntity : public Entity{

    public:
        ModelEntity(Manager &mManger, const char* file,
        glm::vec3 pos, glm::vec3 euler, glm::vec3 scale, bool geoNormal=false);
        ~ModelEntity();

		void update(float deltaTime) override;
        void draw(Shader &shader) override;
        void setUpBezier(BezierCurveComponent &curveBezier);

        void setExplosionGeo(Shader &shader,bool isExplision);
    private:
        bool hasBezier = false;
        BezierCurveComponent *bezier = nullptr;
        void LoadModel();


        void TransverseNode(aiNode *node, const aiScene *scene);
        //Mesh ProccessMeshes(aiMesh *mesh, const aiScene *scene);
        MeshNoComponent ProccessMeshes(aiMesh *mesh, const aiScene *scene);

        std::vector<Texture>LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

        //save all meshes
        //std::vector<Mesh*> mMeshesList;
        std::vector<MeshNoComponent> mMeshesList;
        const char* mFile;


        //variables to prevent loading the same texture several times
        std::vector<std::string> mLoadedTexName;
	    //store texture of all meshes to use
        std::vector<Texture> mLoadedTex;
        //for the transfomr
        TransformComponent *transform = nullptr;

}; 