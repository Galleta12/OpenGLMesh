#pragma once
#include "IncludesForMath.h"
#include "vector"

std::vector<glm::vec3> bezierControl1{
    glm::vec3(-0.95f, -0.95+2.0f,  0.0f),
    glm::vec3(0.0f, 2.0f,    0.0f),
    glm::vec3(0.0f, 2.0f,    0.0f),
    glm::vec3(0.0f, 2.0f,  -0.95f)
};


//for the bezier two
std::vector<glm::vec3> bezierControl2{
    glm::vec3(-0.95f, -0.95+2.0f,  0.0f),
    glm::vec3(0.0f, 2.0f,    0.0f),
    glm::vec3(-0.95f, 2.0f,    2.0f),
    glm::vec3(-0.95f, 2.0f,  2.95f)
};


 std::vector<glm::vec3>  applyTransformationForNewControlBezier(std::vector<glm::vec3> bezierPoints,glm::vec3 pos, glm::vec3 eulerAngles,glm::vec3 scale){
    
    
    std::vector<glm::vec3> newControlPoint;
    
    for (glm::vec3& point : bezierPoints) {
        glm::mat4 identity = glm::mat4(1.0f);
        //caculate the new position
        glm::mat4 traslation = glm::translate(identity,pos);

        glm::quat rotationQuat = glm::quat(glm::radians(glm::vec3(eulerAngles.x,eulerAngles.y,eulerAngles.z))) ;

        //apply rotation
        glm::mat4 rotationMatrix = glm::mat4_cast(rotationQuat);

        //finally just add the scale
        glm::mat4 scaleMatrix = glm::scale(identity,scale);

        glm::mat4 TRS = traslation * rotationMatrix * scaleMatrix;

        glm::vec4 newPos = TRS * glm::vec4(point, 1.0f);

        newControlPoint.push_back(glm::vec3(newPos.x,newPos.y,newPos.z));
    
    }
    
    return newControlPoint;
 
}