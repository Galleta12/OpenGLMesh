#include "ModelEntity.h"
#include "MeshNoComponent.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)


ModelEntity::ModelEntity(Manager &mManger, const char *file,
glm::vec3 pos, glm::vec3 euler, glm::vec3 scale,bool geoNormal
)
:Entity(mManger)
{

    Entity::addComponent<TransformComponent>(pos, euler, scale);

    transform = &Entity::getComponent<TransformComponent>();



    mFile = file;
    if(geoNormal){
        Entity::addGroup(Game::groupMeshesNormal);   

    }else{

        Entity::addGroup(Game::groupMeshes);   
    }
    LoadModel();
}

ModelEntity::~ModelEntity()
{

}

void ModelEntity::update(float deltaTime)
{
    if(hasBezier){

        //set the new position in the transform
        transform->setPosition(bezier->getBezierPos());    
        
    }
    
    Entity::update(deltaTime);

}

void ModelEntity::draw(Shader &shader)
{
    
    //Entity::draw(shader);


    for (unsigned int i = 0; i < mMeshesList.size(); i++)
	{
		mMeshesList[i].MeshNoComponent::Draw(shader,transform->getModelMatrix());
	}


}

void ModelEntity::setUpBezier(BezierCurveComponent &curveBezier)
{
    hasBezier = true;
    //save the bezier entity
    bezier = &curveBezier;
}

void ModelEntity::setExplosionGeo(Shader &shader,bool isExplision)
{
    shader.set_explosion_geo(isExplision);

}

void ModelEntity::LoadModel()
{
    
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(mFile, ASSIMP_LOAD_FLAGS); 

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){

        std::cout << "Error Assimp"<< importer.GetErrorString() << std::endl;
    }
    else{
        std::cout <<"Succes Assimp import Model" << std::endl;
        TransverseNode(scene->mRootNode, scene);

    }

    
}

void ModelEntity::TransverseNode(aiNode *node, const aiScene *scene)
{

    // process all nodes meshes
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        //mMeshesList.push_back(&ProccessMeshes(mesh, scene));			
        mMeshesList.push_back(ProccessMeshes(mesh, scene));			
    }
    // if there are childs do the same
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        TransverseNode(node->mChildren[i], scene);
    }

}



MeshNoComponent ModelEntity::ProccessMeshes(aiMesh *mesh, const aiScene *scene)
{
    
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        
        
        
        Vertex vertex;
        //if(mesh->HasPositions()){
            
            glm::vec3 vectorPos = glm::vec3(0.0f,0.0f,0.0f);
            //vertices position on the mesh loaded by assimp
            vectorPos.x = mesh->mVertices[i].x;
            vectorPos.y = mesh->mVertices[i].y;
            vectorPos.z = mesh->mVertices[i].z;

            vertex.position = vectorPos;


            
        //}
        //for the normals
        if(mesh->HasNormals()){
            glm::vec3 vectorNormal = glm::vec3(0.0f,0.0f,0.0f);
            vectorNormal.x = mesh->mNormals[i].x;
            vectorNormal.y = mesh->mNormals[i].y;
            vectorNormal.z = mesh->mNormals[i].z;
            //save it in the vertex struct
            vertex.normal =vectorNormal;
        }
        //now for the texture
        if(mesh->HasTextureCoords(0)){
	        glm::vec2 texCoor = glm::vec2(0.0f,0.0f);

            texCoor.x = mesh->mTextureCoords[0][i].x;
            texCoor.y = mesh->mTextureCoords[0][i].y;

            vertex.texUV = texCoor;

        }
        else{
            vertex.texUV = glm::vec2(0.0f,0.0f);
        }

        
        //saved the vertices
        vertices.push_back(vertex);

    }

    //this is for the index buffer
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);        
        }
    }    

    //now save the texture data
    //this is with the material of the current node/mesh
    //aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];  

    //if there textures
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        //here we will check if we should skip the texture
        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, 
                                        aiTextureType_DIFFUSE, "texture_diffuse");
        
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        
        
        std::vector<Texture> specularMaps = LoadMaterialTextures(material, 
                                            aiTextureType_SPECULAR, "texture_specular");
        
        
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());


    }


   return MeshNoComponent(vertices,indices,textures);


}

std::vector<Texture> ModelEntity::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    
    std::string filename = std::string(mFile);
	std::string fileDirectory = filename.substr(0, filename.find_last_of('/') + 1);

    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        
        aiString str;
        mat->GetTexture(type, i, &str);
        
        //check if the texture was loaded
        bool skip = false;
        for (unsigned int j = 0; j < mLoadedTexName.size(); j++){
            //if the name is the same
            if(std::strcmp(mLoadedTexName[i].data(), str.C_Str()) == 0){
                //we push an already loaded texture, we dont need to load it anymore
                textures.push_back(mLoadedTex[j]);
                skip = true;
                break;
            }
        }
        
        
        if(!skip){

            if(typeName == "texture_diffuse"){
                
                Texture diffuse = Texture((fileDirectory + str.C_Str()).c_str(), "diffuse", mLoadedTex.size());
                textures.push_back(diffuse);
                mLoadedTex.push_back(diffuse);
                mLoadedTexName.push_back(str.C_Str());

            }
            else if(typeName == "texture_specular"){
                Texture specular = Texture((fileDirectory + str.C_Str()).c_str(), "specular", mLoadedTex.size());
                textures.push_back(specular);
                mLoadedTex.push_back(specular);
                mLoadedTexName.push_back(str.C_Str());


            }
        }
        
        
        
    }
    return textures;
}

