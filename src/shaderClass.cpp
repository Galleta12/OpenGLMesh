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

Shader::Shader(const char *vertexFile, const char *tCS, const char *tES, const char *fragmentFile)
{

	fs::path currentPath = fs::current_path();
    fs::path vertFileName = vertexFile;
    fs::path fragFile = fragmentFile;

    fs::path vertShaderPath = currentPath / "src" / "shaders" / vertFileName;
    
	
	//tessallator control and evaluation shader
	fs::path tessControlPath = currentPath / "src" / "shaders" / tCS;
    fs::path tessEvaluationPath = currentPath / "src" / "shaders" / tES;

    
	fs::path fragShaderPath = currentPath / "src" / "shaders" / fragFile;
	
	//for the vert  
    std::ifstream vert_shader_file(vertShaderPath);


    std::string vert_shader_source((std::istreambuf_iterator<char>(vert_shader_file)), std::istreambuf_iterator<char>());
    
	vert_shader_file.close();



	//for the tess control path
	std::ifstream tCS_shader_file(tessControlPath);


    std::string tcs_shader_source((std::istreambuf_iterator<char>(tCS_shader_file)), std::istreambuf_iterator<char>());
    
	
	tCS_shader_file.close();

	//for the evaluation


	std::ifstream tES_shader_file(tessEvaluationPath);


    std::string tES_shader_source((std::istreambuf_iterator<char>(tES_shader_file)), std::istreambuf_iterator<char>());
    
	
	tES_shader_file.close();


	//for the frag
    std::ifstream frag_shader_file(fragShaderPath);

    std::string frag_shader_source((std::istreambuf_iterator<char>(frag_shader_file)), std::istreambuf_iterator<char>());
    
	frag_shader_file.close();


	
	const char* vertexSource = vert_shader_source.c_str();
	
	
	const char* tCSSource = tcs_shader_source.c_str();
	
	const char* tECSource = tES_shader_source.c_str();
	
	const char* fragmentSource = frag_shader_source.c_str();

	
	//for the vertex
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexSource, NULL);

	glCompileShader(vertexShader);

	compileErrors(vertexShader, "VERTEX");

	
	
	//for the tcs
	
	
	GLuint tCSShader = glCreateShader(GL_TESS_CONTROL_SHADER);

	glShaderSource(tCSShader, 1, &tCSSource, NULL);

	glCompileShader(tCSShader);

	compileErrors(tCSShader, "TESSELATORCONTROLSHADER");
	
	
	//for the tES
	GLuint tESShader = glCreateShader(GL_TESS_EVALUATION_SHADER);

	glShaderSource(tESShader, 1, &tECSource, NULL);

	glCompileShader(tESShader);

	compileErrors(tESShader, "TESSELATOREVALUATIONSHADER");

	
	
	
	
	//for the fragment
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	
	glCompileShader(fragmentShader);
	
	compileErrors(fragmentShader, "FRAGMENT");

	
	
	
	ID = glCreateProgram();
	
	glAttachShader(ID, vertexShader);
	
	
	
	glAttachShader(ID, tCSShader);
	
	glAttachShader(ID, tESShader);
	
	glAttachShader(ID, fragmentShader);
	
	
	
	
	glLinkProgram(ID);
	
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	
	glDeleteShader(vertexShader);
	
	
	glDeleteShader(tCSShader);
	
	glDeleteShader(tESShader);
	

	glDeleteShader(fragmentShader);


	//save values
	numSegmentsLoc = glGetUniformLocation(ID, "gNumSegments");
	lineColorLoc = glGetUniformLocation(ID, "gLineColor");




	
	modelMatrixLoc = glGetUniformLocation(ID, "model");
	
    viewMatrixLoc = glGetUniformLocation(ID, "u_view_matrix");

	projectionMatrixLoc = glGetUniformLocation(ID, "u_projection_matrix");



}

Shader::Shader(const char *vertexFile, const char *gEOM, const char *fragmentFile)
{

	fs::path currentPath = fs::current_path();
    
	
	fs::path vertFileName = vertexFile;
	fs::path geoFileName = gEOM;
    fs::path fragFile = fragmentFile;

    fs::path vertShaderPath = currentPath / "src" / "shaders" / vertFileName;
    
	fs::path geomShaderPath = currentPath / "src" / "shaders" / geoFileName;
    
	fs::path fragShaderPath = currentPath / "src" / "shaders" / fragFile;

	
	  
    std::ifstream vert_shader_file(vertShaderPath);


    std::string vert_shader_source((std::istreambuf_iterator<char>(vert_shader_file)), std::istreambuf_iterator<char>());
    
	vert_shader_file.close();
    
	//for the geo
	std::ifstream geo_shader_file(geomShaderPath);

    std::string geo_shader_source((std::istreambuf_iterator<char>(geo_shader_file)), std::istreambuf_iterator<char>());
    
	geo_shader_file.close();

    
	//frag	
	std::ifstream frag_shader_file(fragShaderPath);

    std::string frag_shader_source((std::istreambuf_iterator<char>(frag_shader_file)), std::istreambuf_iterator<char>());
    frag_shader_file.close();



	const char* vertexSource = vert_shader_source.c_str();
	
	//geo
	const char* geoSource = geo_shader_source.c_str();
	
	const char* fragmentSource = frag_shader_source.c_str();


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexSource, NULL);

	glCompileShader(vertexShader);

	compileErrors(vertexShader, "VERTEX");
	
	//geo load shader
	GLuint geoShader = glCreateShader(GL_GEOMETRY_SHADER);

	glShaderSource(geoShader, 1, &geoSource, NULL);

	glCompileShader(geoShader);

	compileErrors(geoShader, "GEO");
	

	//frag
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	
	glCompileShader(fragmentShader);
	
	compileErrors(fragmentShader, "FRAGMENT");

	
	ID = glCreateProgram();
	
	glAttachShader(ID, vertexShader);
	
	glAttachShader(ID, geoShader);
	
	glAttachShader(ID, fragmentShader);
	
	glLinkProgram(ID);
	
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	
	glDeleteShader(vertexShader);
	
	glDeleteShader(geoShader);
	
	glDeleteShader(fragmentShader);



	//save the variables

	modelMatrixLoc = glGetUniformLocation(ID, "model");
	
    viewMatrixLoc = glGetUniformLocation(ID, "u_view_matrix");

	projectionMatrixLoc = glGetUniformLocation(ID, "u_projection_matrix");

	eyePosLoc = glGetUniformLocation(ID, "u_eye_position");
	
	
	lightPosLoc = glGetUniformLocation(ID, "lightPos");

	
	lightColorLoc = glGetUniformLocation(ID, "lightColor");
	
	
	lightPosLoc2 = glGetUniformLocation(ID, "lightPos2");

	
	lightColorLoc2 = glGetUniformLocation(ID, "lightColor2");
	

	isExplosionLoc = glGetUniformLocation(ID, "isExplosion");


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

void Shader::set_light_position2(float x, float y, float z)
{
	 glUniform3f(lightPosLoc2, x, y, z);

}


void Shader::set_light_color2(float x, float y, float z, float w)
{
	glUniform4f(lightColorLoc2, x, y, z, w);

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




void Shader::set_num_segments_Tesallator(int numSegments)
{

	glUniform1i(numSegmentsLoc, numSegments);
}

void Shader::set_line_color_Tesallator(glm::vec4 color)
{

    glUniform4f(lineColorLoc, color.x, color.y, color.z, color.w);

}

void Shader::set_explosion_geo(bool isExplosion)
{

	
	glUniform1i(isExplosionLoc,1);
}
