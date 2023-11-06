#include "CameraComponent.h"

CameraComponent::CameraComponent(glm::vec3 _eyePosition)
{

    Position = _eyePosition;
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::setLooKViewCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    glm::mat4 view = glm::mat4(1.0f);
    Position = eye;
	view = glm::lookAt(Position, center, Up);
    viewMatrix = view;
}

void CameraComponent::setPerspectiveProjection(float fov, float _aspect, float _near, float _far)
{

    zoom = fov;
    glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(zoom, _aspect, _near, _far);
    projectionMatrix = projection;

}

void CameraComponent::draw(Shader &shader)
{
     
    //we dont want to draw
    // if(!shouldDraw)return;

    // setViewShader(shader);
    // setProjectionShader(shader);

}

void CameraComponent::update(float deltaTime)
{
    if(!shouldDraw)return;
 
    

}

void CameraComponent::drawComponent(Shader &shader)
{

    setViewShader(shader);
    setProjectionShader(shader);
}

void CameraComponent::setViewShader(Shader &shader)
{
    shader.set_view_matrix(viewMatrix);
}

void CameraComponent::setProjectionShader(Shader &shader)
{
	shader.set_projection_matrix(projectionMatrix);
}




void CameraComponent::setOrthoGraphicProjection(float _left, float _right, float _bottom, float _top, float _nearPlane, float _farPlane)
{
}
