#version 400 core
// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;


// // Outputs the current position for the Fragment Shader
//out vec3 position;
// // Outputs the normal for the Fragment Shader
// out vec3 Normal;
// // Outputs the color for the Fragment Shader
// out vec3 color;
// // Outputs the texture coordinates to the Fragment Shader
// out vec2 uv_coordinates_tex;



out DATA
{
    vec3 Normal;
	vec3 color;
	vec2 uv_coordinates_tex;
    mat4 projection;
	vec3 position;
} data_out;






// Imports the model matrix from the main function
uniform mat4 model;



// Imports of the matrix
uniform mat4 u_projection_matrix;


//Import view matrix
uniform mat4 u_view_matrix;



void main()
{
	
	//this is output in  a opengl buil-int per vextex pos
	//positio in world space in the geo we apply clip coord
	gl_Position = model * vec4(aPos, 1.0f);
	data_out.position = vec3(model * vec4(aPos, 1.0f));
	data_out.Normal = vec3(model * vec4(aNormal, 1.0f)); 
	data_out.color = aColor; 	
	data_out.uv_coordinates_tex = mat2(0.0, -1.0, 1.0, 0.0) * aTex; 	
	data_out.projection =  u_projection_matrix * u_view_matrix; 	
	
	//this is for the position that will be used in the frag shader
	// vec3 global_position= vec3(model * vec4(aPos, 1.0f));
	// position = vec3(u_view_matrix *vec4(global_position, 1.0f));
	
}
// void main()
// {
	
// 	// calculates current position in global space
// 	vec3 global_position= vec3(model * vec4(aPos, 1.0f));

// 	Normal = vec3(model * vec4(aNormal, 1.0f));
	
// 	color = aColor;
	
// 	uv_coordinates_tex = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	
// 	//eye coordinates
// 	position = vec3(u_view_matrix *vec4(global_position, 1.0f));
	
// 	//in clip space
// 	gl_Position = u_projection_matrix * vec4(position, 1.0);

	
	
// }