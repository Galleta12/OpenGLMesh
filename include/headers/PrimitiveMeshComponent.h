#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include "Game.h"
#include "Components.h"
#include "Texture.h"
#include "ShaderClass.h"
#include "IncludesForMath.h"

class PrimitiveMeshComponent : public Component{


    public:
        PrimitiveMeshComponent();

        void draw(Shader& shader) override;

        std::vector<Vertex>& getVerts(){
            return verts;
        }
        
        std::vector<GLuint> &getInd(){
            return ind;
        }
        
        std::vector<Texture> &getTextures(){
            return tex;
        }
    
    private:
        
         
        glm::vec3 scaleFactor;
        //'XYZ' as pitch, yaw, and roll
        //is in degrees
        glm::vec3 eulerAngles;

        glm::quat rotationQuat;

        glm::mat4 modeMatrix;

        glm::vec3 position;
    protected:
        
        std::vector <Texture> tex;
        std::vector <GLuint> ind;
        std::vector <Vertex> verts;
        
        void SetUpVertices();
    
 
       

};