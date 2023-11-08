#pragma once
#include "Components.h"
#include "ShaderClass.h"

 
class PrimitiveMeshComponent;

class PlaneComponent : public PrimitiveMeshComponent{
    
    public:  
        PlaneComponent(const char* tex, const char* specular);
        
        
        PlaneComponent(const char* tex);


};