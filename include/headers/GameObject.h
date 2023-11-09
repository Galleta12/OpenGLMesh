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
class TransformComponent;
class GameObject : public Entity {

public:
    GameObject(Manager& mManager, const char* tex, const char* specular,
    glm::vec3 pos, glm::vec3 euler, glm::vec3 scale
    );
    
    GameObject(Manager& mManager,glm::vec3 pos, glm::vec3 euler, 
    glm::vec3 scale);

    ~GameObject();

    
    void setUpBezier(BezierCurveComponent &curveBezier);
    
    void update(float deltaTime) override;
    void draw(Shader& shader) override;
    



    const TransformComponent &getTransform() const{
        return *transform;
    }

private:
    bool hasBezier = false;
    PrimitiveMeshComponent* pri = nullptr;
    Mesh* mMesh = nullptr;
    TransformComponent *transform = nullptr;
    BezierCurveComponent *bezier = nullptr;
    void SetUpTransform(glm::vec3 pos, glm::vec3 euler, glm::vec3 scale);

};