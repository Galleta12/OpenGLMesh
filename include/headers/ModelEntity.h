#pragma once

#include "Game.h"
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>       
#include <assimp/postprocess.h> 
#include "ECS.h"
#include "Components.h"
#include "MeshNoComponent.h"

class ModelEntity : public Entity{

    public:
        ModelEntity(Manager &mManger, const char* file);
        ~ModelEntity();

		void draw(Shader &shader) override;
        
    private:
        
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


}; 