#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include<vector>
#include "IncludesForMath.h"


class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);
	
    Shader(const char* vertexFile,const char* tCS , const char* tES ,const char* fragmentFile);
    
    Shader(const char* vertexFile,const char* gEOM ,const char* fragmentFile);

	
	//use shader
	void use();
	// Deletes the Shader Program
	
	void Delete();

	
	void set_model_matrix(const glm::mat4 matrix_array);
	
	void set_view_matrix(const glm::mat4 matrix_array );
    
	
	void set_projection_matrix(const glm::mat4 matrix_array );


    void set_position_attribute(const glm::mat4 matrix_array );
    
	void set_normal_attribute(const glm::mat4 matrix_array );
        

    void set_light_position(float x, float y, float z);
    
    
    
    void set_light_color(float x, float y, float z, float w);
    
    
    
    void set_light_position2(float x, float y, float z);
    
    
    
    void set_light_color2(float x, float y, float z, float w);
    






    void set_light_diffuse(float red, float green, float blue);
        
    void set_material_diffuse(float red, float green, float blue);
         
    void set_eye_position(float x, float y, float z);

    void set_light_specular(float ambient);

    void set_material_specular(float red, float green, float blue);
       
    void set_material_shininess(float shininess);
   
    void set_global_ambient(float ambient);
    
    void set_ambient_light(float ambient);
    
    
    void set_square_a(float a);
    void set_square_b(float b);
    
    void set_outer_cone(float a);
    void set_inner_cone(float b);

  
    //for the tesallator
    void set_num_segments_Tesallator(int numSegments);
    
    void set_line_color_Tesallator(glm::vec4 color);
  


private:
	

    GLuint positionLoc;
    GLuint normalLoc;
    GLuint modelMatrixLoc;
    
    GLuint lightPosLoc;
   
    
    GLuint lightColorLoc;


    //for the second    
    GLuint lightPosLoc2;
   
    
    GLuint lightColorLoc2;






    
    GLuint lightDiffuseLoc;
    
    GLuint materialDiffuseLoc; 
    
    GLuint eyePosLoc;
    
    GLuint lightSpecularLoc;
    
    GLuint materialSpecularLoc;  
    
    
    GLuint viewMatrixLoc;
    
    GLuint projectionMatrixLoc;
    
    GLuint materialShininessLoc;


    GLuint globalAmbientLoc;
    GLuint ambientLightLoc;
    
    GLuint squareConstantAmbientALoc;
    
    GLuint squareConstantAmbientBLoc;


    GLuint outConeLoc;
    
    GLuint innerConeLoc;

	
    //for the tesallator

    GLuint numSegmentsLoc;
    
    GLuint  lineColorLoc;

	
	
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);


	template <typename T>
    float* vectorToArray(const std::vector<T>& vector);
};


#endif

