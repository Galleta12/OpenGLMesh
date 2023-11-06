#pragma once


#include <vector>
#include <memory>
#include "ECS.h"
#include "Components.h"
#include "ShaderClass.h"
#include "IncludesForMath.h"

//the camera will have reference to the view and projection matrix
class CameraComponent : public Component{

    public:

       
        bool shouldDraw = false;
        
        //zoom this is the fov
        //this is a 90 degree fox, always in radians
        float zoom = 0.0f;
        //keep track of the position of the camera. this is in world space
        glm::vec3 Position;
        //set up view and projectionMatrix        
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 viewMatrix = glm::mat4(1.0f);
	    glm::mat4 projectionMatrix = glm::mat4(1.0f);

        //bool is orthographic
        
        bool isOrthoGraphic = false;
        
        CameraComponent(glm::vec3 _eyePosition);
        
        ~CameraComponent();

        void setLooKViewCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
        void setPerspectiveProjection(float fov, float _aspect, float _near, float _far);
        
   
        //we want on the draw set up the shaders
        void draw(Shader& shader) override;
        void update(float deltaTime) override; 
        //for the orthographic as well

    
        void setViewShader(Shader& shader);
        
        void setProjectionShader(Shader& shader);
        
        void setOrthoGraphicProjection(float _left, float _right, float _bottom, float _top, float _nearPlane, float _farPlane);
        

      
    
    private:


      
        
};

