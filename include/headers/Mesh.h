#pragma once

#include<string>

#include"VAO.h"
#include"EBO.h"
#include "ECS.h"
#include "Components.h"
#include"Texture.h"

class CameraComponent;

class Mesh : public Component
{
	public:

		// Initializes the mesh
		Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
		Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices);

		void draw(Shader& shader) override;
	
	private:
		void drawMeshTex(Shader& shader);
	
		std::vector <Vertex> vertices;
		std::vector <GLuint> indices;
		std::vector <Texture> textures;
		// Store VAO in public so it can be used in the Draw function
		VAO VAO;

};


