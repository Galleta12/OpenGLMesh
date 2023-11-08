#include "PlaneComponent.h"

PlaneComponent::PlaneComponent(const char* tex, const char* specular)
{

     // Vertices coordinates
    Vertex vertices[] =
    { //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
        Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    Texture textures[]
	{
		Texture(tex, "diffuse", 0),
		Texture(specular, "specular", 1)
	};

    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> texture(textures, textures + sizeof(textures) / sizeof(Texture));
    
    PrimitiveMeshComponent::verts = verts;
    PrimitiveMeshComponent::ind = ind;
    PrimitiveMeshComponent::tex = texture;



}

PlaneComponent::PlaneComponent(const char* tex)
{

         // Vertices coordinates
    Vertex vertices[] =
    { //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
        Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    Texture textures[]
	{
		Texture(tex, "diffuse", 0),
		
	};

    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> texture(textures, textures + sizeof(textures) / sizeof(Texture));
    
    PrimitiveMeshComponent::verts = verts;
    PrimitiveMeshComponent::ind = ind;
    PrimitiveMeshComponent::tex = texture;

 


}
