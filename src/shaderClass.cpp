#include"ShaderClass.h"

// Reads a text file and outputs a string with everything in the text file

//still need to read more about this
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;





// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	
	fs::path currentPath = fs::current_path();
    fs::path vertFileName = vertexFile;
    fs::path fragFile = fragmentFile;

    fs::path vertShaderPath = currentPath / "src" / "shaders" / vertFileName;
    fs::path fragShaderPath = currentPath / "src" / "shaders" / fragFile;

	
	  
    std::ifstream vert_shader_file(vertShaderPath);


    std::string vert_shader_source((std::istreambuf_iterator<char>(vert_shader_file)), std::istreambuf_iterator<char>());
    
	vert_shader_file.close();

    std::ifstream frag_shader_file(fragShaderPath);

    std::string frag_shader_source((std::istreambuf_iterator<char>(frag_shader_file)), std::istreambuf_iterator<char>());
    frag_shader_file.close();



	const char* vertexSource = vert_shader_source.c_str();
	const char* fragmentSource = frag_shader_source.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexSource, NULL);

	glCompileShader(vertexShader);

	compileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	
	glCompileShader(fragmentShader);
	
	compileErrors(fragmentShader, "FRAGMENT");

	ID = glCreateProgram();
	
	glAttachShader(ID, vertexShader);
	
	glAttachShader(ID, fragmentShader);
	
	glLinkProgram(ID);
	
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	
	glDeleteShader(vertexShader);
	
	glDeleteShader(fragmentShader);



	//save the variables

	modelMatrixLoc = glGetUniformLocation(ID, "model");
	
    viewMatrixLoc = glGetUniformLocation(ID, "u_view_matrix");

	projectionMatrixLoc = glGetUniformLocation(ID, "u_projection_matrix");

	eyePosLoc = glGetUniformLocation(ID, "u_eye_position");
	
	lightPosLoc = glGetUniformLocation(ID, "lightPos");

	
	
	lightColorLoc = glGetUniformLocation(ID, "lightColor");
	

	



	lightSpecularLoc = glGetUniformLocation(ID, "u_ligh_specular");

	ambientLightLoc = glGetUniformLocation(ID, "u_ambient_light");
	


	squareConstantAmbientALoc = glGetUniformLocation(ID, "squareConstantA");
	squareConstantAmbientBLoc = glGetUniformLocation(ID, "squareConstantB");
	
	outConeLoc = glGetUniformLocation(ID, "outerCone");
	innerConeLoc = glGetUniformLocation(ID, "innerCone");
  
	materialShininessLoc = glGetUniformLocation(ID, "u_shinisses");

}


void Shader::use()
{
	try {
        glUseProgram(ID);
    }
        catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::set_model_matrix(const glm::mat4 matrix_array)
{

	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(matrix_array));
}


void Shader::set_view_matrix(const glm::mat4 matrix_array)
{

	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(matrix_array));
}

void Shader::set_projection_matrix(const glm::mat4 matrix_array)
{
	glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(matrix_array));
}

void Shader::set_position_attribute(const glm::mat4 matrix_array)
{
}

void Shader::set_normal_attribute(const glm::mat4 matrix_array)
{
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}

void Shader::set_light_position(float x, float y, float z)
{

	 glUniform3f(lightPosLoc, x, y, z);

}

void Shader::set_light_color(float x, float y, float z, float w)
{
	glUniform4f(lightColorLoc, x, y, z, w);

}

void Shader::set_light_diffuse(float red, float green, float blue)
{
}

void Shader::set_material_diffuse(float red, float green, float blue)
{
}

void Shader::set_eye_position(float x, float y, float z)
{
	   glUniform3f(eyePosLoc, x, y, z);
}

void Shader::set_light_specular(float ambient)
{
}

void Shader::set_material_specular(float red, float green, float blue)
{
}

void Shader::set_material_shininess(float shininess)
{
}

void Shader::set_global_ambient(float ambient)
{
}

void Shader::set_ambient_light(float ambient)
{
}

void Shader::set_square_a(float a)
{
}

void Shader::set_square_b(float b)
{
}

void Shader::set_outer_cone(float a)
{
}

void Shader::set_inner_cone(float b)
{
}
