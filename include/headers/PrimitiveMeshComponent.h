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
    
    
        
         
        
    protected:
        
        std::vector <Texture> tex;
        std::vector <GLuint> ind;
        std::vector <Vertex> verts;
        
        void SetUpVertices();
    
 
       

};