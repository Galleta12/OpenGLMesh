#pragma once
#pragma once

#include<string>

#include"VAO.h"
#include"EBO.h"
#include "ECS.h"
#include "Components.h"
#include"Texture.h"

class MeshNoComponent {


    public:

        MeshNoComponent (std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
        void Draw(Shader& shader, const glm::mat4 &modelMatrix);

    private:
        std::vector <Vertex> vertices;
		std::vector <GLuint> indices;
		std::vector <Texture> textures;
		// Store VAO in public so it can be used in the Draw function
		VAO VAO;

};