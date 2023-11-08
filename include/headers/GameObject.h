#pragma once

#include "Game.h"
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>       
#include <assimp/postprocess.h> 
#include "ECS.h"
#include "Components.h"
#include "LightComponent.h"
#include "PlaneComponent.h"

class PrimitiveMeshComponent;
class LightComponent;
class PlaneComponent;
class Mesh;
class GameObject : public Entity {

public:
    GameObject(Manager& mManager, const char* tex, const char* specular);
    GameObject(Manager& mManager, const char* tex);
    GameObject(Manager& mManager);

    ~GameObject();

    void update(float deltaTime) override;
    void draw(Shader& shader) override;

private:
    PrimitiveMeshComponent* pri = nullptr;
    Mesh* mMesh = nullptr;

};