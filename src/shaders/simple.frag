#version 400 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the current position from the Vertex Shader
in vec3 position;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 uv_coordinates_tex;

// Gets the Texture Unit from the main function
uniform sampler2D diffuse0;


uniform sampler2D specular0;


// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;

//for the second light
// Gets the color of the light from the main function
uniform vec4 lightColor2;
// Gets the position of the light from the main function
uniform vec3 lightPos2;


// Gets the position of the camera from the main function
uniform vec3 u_eye_position;







vec4 pointLight()
{
	// used in two variables so I calculate it here to not have to do it twice
	vec3 v_s = lightPos2 - u_eye_position;

	// intensity of light with respect to distance
	float dist = length(v_s);
	
	// float a = 0.05;
	// float b = 0.01;
	
	float a = 3.0;
	float b = 0.7;
	
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 v_normal = normalize(Normal);
	vec3 lightDirection = normalize(v_s);
	
	float lambert = max(dot(v_normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	
	vec3 viewDirection = normalize(u_eye_position - position);
	vec3 reflectionDirection = reflect(-lightDirection, v_normal);
	
	
	float phong = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = phong * specularLight;

	return (texture(diffuse0, uv_coordinates_tex) * (lambert * inten + ambient) + texture(specular0, uv_coordinates_tex).r * specular * inten) * lightColor2;
}






vec4 spotLight()
{

	
	// controls how big the area that is lit up is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(u_eye_position - position);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(u_eye_position - position);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// calculates the intensity of the position based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, uv_coordinates_tex) * (diffuse * inten + ambient) + texture(specular0, uv_coordinates_tex).r * specular * inten) * lightColor;

}

vec4 spotLight2()
{

	
	// controls how big the area that is lit up is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(u_eye_position - position);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(u_eye_position - position);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// calculates the intensity of the position based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, uv_coordinates_tex) * (diffuse * inten + ambient) + texture(specular0, uv_coordinates_tex).r * specular * inten) * lightColor2;

}




void main()
{
	//FragColor = pointLight();
	FragColor = spotLight() + spotLight2();

}



