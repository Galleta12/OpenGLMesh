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
#include <algorithm> 

class BezierCurveComponent : public Component{

    public:
        BezierCurveComponent(glm::vec4 color, int numSegments,
        std::vector<glm::vec3>& controlPoints, float startTime, float endTime);


        void update(float deltaTime) override;
        
        //void draw(Shader& shader) override;
        
        void drawBezier(Shader& shader, const CameraComponent &cameraComponent);

        bool bezierExist(){
            return mExist;
        }

        float getStartTime(){
            return mStartTime;
        }
        float getEndTime(){
            return mEndTime;
        }


        const glm::vec3 &getBezierPos() const{return currentBezierCurvePos;}

        void setPosBezier(float currentTime);

    private:

        
        float mStartTime;
        float mEndTime;
        
        bool mExist = false;
        
        void renderPointTS(int topology_type);
        
        void setNumSegments(Shader& shader);

        void setLineColor(Shader& shader);

        void setWorldViewProj(Shader& shader,const CameraComponent &cameraComponent);


        void reverseControl();

        void setNewStartAndEndPoint();

		VAO mVAO;

    
        int m_numSegments = 50;

        glm::vec4 mColor;

        glm::mat4 model = glm::mat4(1.0f);

        glm::vec3 currentBezierCurvePos;

        std::vector<glm::vec3> controlPointList;
};