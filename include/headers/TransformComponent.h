#pragma once

#include "Components.h"
#include "IncludesForMath.h"
#include "ShaderClass.h"

class TransformComponent : public Component
{
    public:
        TransformComponent(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
        
        void update(float deltaTime) override;
        void draw(Shader &shader) override;

        glm::vec4 colorLight;
        // Getters for position, scaleFactor, and eulerAngles
        const glm::vec3& getPosition() const { return position; }
        const glm::vec3& getScaleFactor() const { return scaleFactor; }
        const glm::vec3& getEulerAngles() const { return eulerAngles; }
        
        const glm::mat4& getModelMatrix() const { return modelMatrix; }

        // Setters for position, scaleFactor, and eulerAngles
        void setPosition(const glm::vec3& pos) { position = pos; }
        void setScaleFactor(const glm::vec3& scale) { scaleFactor = scale; }
        void setEulerAngles(const glm::vec3& angles) { eulerAngles = angles; }

        void applyTRS(float deltaTime);

    private:
        
        void setUpRotationQuaterion(float deltaTime);

        glm::vec3 scaleFactor;
        //'XYZ' as pitch, yaw, and roll
        //is in degrees
        glm::vec3 eulerAngles;

        glm::quat rotationQuat;

        glm::mat4 modelMatrix = glm::mat4(1.0f);

        glm::vec3 position;
};