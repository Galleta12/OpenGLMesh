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

		// Draws the mesh
		void Draw(Shader& shader, CameraComponent& camera);
		void draw(Shader& shader) override;
	
	private:

		std::vector <Vertex> vertices;
		std::vector <GLuint> indices;
		std::vector <Texture> textures;
		// Store VAO in public so it can be used in the Draw function
		VAO VAO;

};


