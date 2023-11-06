#version 400 core
// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;


// Outputs the current position for the Fragment Shader
out vec3 position;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 uv_coordinates_tex;


// Imports the model matrix from the main function
uniform mat4 model;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;



// Imports of the matrix
uniform mat4 u_projection_matrix;


//Import view matrix
uniform mat4 u_view_matrix;



void main()
{
	
	// calculates current position in global space
	vec3 global_position= vec3(model * vec4(aPos, 1.0f));

	Normal = vec3(model * vec4(aNormal, 1.0f));
	
	color = aColor;
	
	uv_coordinates_tex = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	
	//eye coordinates
	position = vec3(u_view_matrix *vec4(global_position, 1.0f));
	
	//in clip space
	gl_Position = u_projection_matrix * vec4(position, 1.0);

	
	
}