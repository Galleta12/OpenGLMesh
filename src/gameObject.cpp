#include "GameObject.h"

GameObject::GameObject(Manager &mManager, const char *tex, const char *specular)
:Entity(mManager)
{

    //add the components
    Entity::addComponent<PlaneComponent>(tex, specular);
    
    
    pri =   &Entity::getComponent<PlaneComponent>();
    //for the mesh

    Entity::addComponent<Mesh>(pri->getVerts(),pri->getInd(), pri->getTextures());



    Entity::addGroup(Game::groupMeshes);


}

GameObject::GameObject(Manager &mManager, const char *tex)
:Entity(mManager)
{


}

GameObject::GameObject(Manager &mManager)
:Entity(mManager)
{

    
    Entity::addComponent<LightComponent>();
    
    
    pri =   &Entity::getComponent<LightComponent>();
    //for the mesh

    Entity::addComponent<Mesh>(pri->getVerts(),pri->getInd());



    Entity::addGroup(Game::groupLights);

}

GameObject::~GameObject()
{

}

void GameObject::update(float deltaTime)
{
    Entity::update(deltaTime);
}

void GameObject::draw(Shader &shader)
{
    Entity::draw(shader);
}
