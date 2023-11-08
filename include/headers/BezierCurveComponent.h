#pragma once


#include<string>
#include"VAO.h"
#include"EBO.h"
#include <vector>
#include <memory>
#include "ECS.h"
#include "Components.h"
#include "ShaderClass.h"
#include "IncludesForMath.h"

class BezierCurveComponent : public Component{

    public:
        BezierCurveComponent(glm::vec4 color, int numSegments);


        void update(float deltaTime) override;
        
        //void draw(Shader& shader) override;
        
        void drawBezier(Shader& shader, const CameraComponent &cameraComponent);

        bool bezierExist(){
            return mExist;
        }

    private:

        bool mExist = false;
        
        void renderPointTS(int topology_type);
        
        void setNumSegments(Shader& shader);

        void setLineColor(Shader& shader);

        void setWorldViewProj(Shader& shader,const CameraComponent &cameraComponent);

		VAO mVAO;

        

        int m_numSegments = 50;

        glm::vec4 mColor;

        glm::mat4 model = glm::mat4(1.0f);

};