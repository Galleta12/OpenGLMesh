#include "GameObject.h"


GameObject::GameObject(Manager &mManager, const char *tex, const char *specular,
glm::vec3 pos, glm::vec3 euler, glm::vec3 scale)
:Entity(mManager)
{

    
    
    SetUpTransform(pos, euler, scale);    
    
    //add the components
    Entity::addComponent<PlaneComponent>(tex, specular);
    
    
    pri =   &Entity::getComponent<PlaneComponent>();
    //for the mesh

    Entity::addComponent<Mesh>(pri->getVerts(),pri->getInd(), pri->getTextures());



    Entity::addGroup(Game::groupMeshes);


}


//this means that is a light
GameObject::GameObject(Manager &mManager,glm::vec3 pos, glm::vec3 euler, 
glm::vec3 scale)
:Entity(mManager)
{

    SetUpTransform(pos, euler, scale);    
    

    Entity::addComponent<LightComponent>();
    
    
    pri =   &Entity::getComponent<LightComponent>();
    //for the mesh

    Entity::addComponent<Mesh>(pri->getVerts(),pri->getInd());



    Entity::addGroup(Game::groupLights);

}

GameObject::~GameObject()
{

}

void GameObject::setUpBezier(BezierCurveComponent &curveBezier)
{
    
    hasBezier = true;
    //save the bezier entity
    bezier = &curveBezier;


}

void GameObject::update(float deltaTime)
{
    
    if(hasBezier){

        //set the new position in the transform
        transform->setPosition(bezier->getBezierPos());    
        
    }
    Entity::update(deltaTime);
}

void GameObject::draw(Shader &shader)
{
    Entity::draw(shader);
}

void GameObject::SetUpTransform(glm::vec3 pos, glm::vec3 euler, glm::vec3 scale)
{


    Entity::addComponent<TransformComponent>(pos, euler, scale);

    transform = &Entity::getComponent<TransformComponent>();

}
