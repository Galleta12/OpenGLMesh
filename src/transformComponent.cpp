#include "TransformComponent.h"

TransformComponent::TransformComponent(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
:position(pos),eulerAngles(rot),scaleFactor(scale)
{

}


void TransformComponent::update(float deltaTime)
{
    applyTRS(deltaTime);
}


void TransformComponent::draw(Shader &shader)
{
}

//need to work more on this
void TransformComponent::setUpRotationQuaterion(float deltaTime)
{
    
       //calculate the new modelMatrix
    glm::quat rotation =  glm::quat(glm::radians(eulerAngles));
    
    glm::quat interpolatedRotation = glm::slerp(rotationQuat, rotation, deltaTime);

    rotationQuat = interpolatedRotation;
}

void TransformComponent::applyTRS(float deltaTime)
{

    
    //start with the identity
    glm::mat4 ident = glm::mat4(1.0f);
        
    //caculate the new position
    glm::mat4 traslation = glm::translate(ident,position);

	rotationQuat = glm::quat(glm::radians(glm::vec3(eulerAngles.x,eulerAngles.y,eulerAngles.z))) ;

    //apply rotation
    glm::mat4 rotationMatrix = glm::mat4_cast(rotationQuat);

    //finally just add the scale
    glm::mat4 scaleMatrix = glm::scale(ident,scaleFactor);

    //hence the final modelmatrix is
    modelMatrix = traslation * rotationMatrix * scaleMatrix;

}
