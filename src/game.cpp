
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;
//------------------------------


#include "Game.h"
#include<iostream>

#include "IncludesForMath.h"
#include <vector>
#include "Components.h"

#include"Model.h"
#include "Mesh.h"
#include "MainCamera.h"
//#include"Camera.h"



//initialize static variables
int Game::Width = 0;
int Game::Height = 0;

bool Game::isRunning = false;
        
GLFWwindow* Game::window = nullptr;

Game::WhoISCamera Game::cameraViewState = Game::WhoISCamera::MAINCAMERA;

Shader *shaderProgram = nullptr;

Shader  *lightShader = nullptr;

Model *model = nullptr;



//Camera *mainCamera = nullptr;

MainCamera *mainCamera = nullptr;


Mesh *floorEntity = nullptr;
Mesh *lightEntity = nullptr;

Manager manager;

// auto &floorEntity(manager.addEntity());
// auto &lightEntity(manager.addEntity());
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

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


Game::Game()
{

    
	glfwInit();


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	
	// set glfw that we will use the open gl moder functiontions
		
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

Game::~Game()
{



}

void Game::init(const char *title, int posX, int posY, int width, int height, bool fullscreen)
{


    Width = width;
    Height = height;


	window = glfwCreateWindow(Width, height, title, NULL, NULL);
    // Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//we faile to create
        isRunning = false;
        return;
	}

    //start opegl
    // Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//load glad for using modern opengl functionalities
	gladLoadGL();
	

	//initial viewport
	glViewport(0, 0, width, height);

    isRunning = true;

    setUpShaderAndBuffers();
    setUpEntities();



}


auto& camerasWorld(manager.getGroup(Game::groupCameras));

auto& meshesWorld(manager.getGroup(Game::groupMeshes));
auto& lightsWorld(manager.getGroup(Game::groupLights));


void Game::handleEvents()
{


      //ppointet ro the orthocamera
    if(glfwWindowShouldClose(window)){
        isRunning = false;
    }
	
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
		
		cameraViewState = WhoISCamera::MAINCAMERA;
	
	}
	
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
		
	
	}



}

void Game::update(float deltaTime)
{

    
	manager.refresh();
    manager.update(deltaTime);
	
	
	// mainCamera->Inputs(Game::window, deltaTime);

    // mainCamera->updateMatrix(90.0f, 0.1f, 100.0f);


}

void Game::display()
{

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    
	glViewport(0, 0, Width, Height);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


   

	// Updates and exports the camera matrix to the Vertex Shader
	//mainCamera->updateMatrix(90.0f, 0.1f, 100.0f);

	
	
	
	//model->Draw(*shaderProgram, *mainCamera->getCameraComponent());
   

	floorEntity->Draw(*shaderProgram, *mainCamera->getCameraComponent());
	lightEntity->Draw(*lightShader, *mainCamera->getCameraComponent());
    

    // for(auto& c : camerasWorld){
    //    c->draw(*shaderProgram); 
    // }
	

	// for(auto& m : meshesWorld){
	// 	m->draw(*shaderProgram);
	// }



	// for(auto& l : lightsWorld){
	// 	l->draw(*lightShader);
	// }

	// for(auto& c : camerasWorld){
    //     c->draw(*lightShader); 
    // }
	
	


	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
		// Take care of all GLFW events
	glfwPollEvents();

}

void Game::clean()
{


   
	
	// shaderProgram->Delete();
    // lightShader->Delete();

    
	glfwDestroyWindow(window);
	window = NULL;
    // Terminate GLFW before ending the program
	
    glfwTerminate();
     std::cout << "Game closed" << std::endl;
}

void Game::setUpShaderAndBuffers()
{





    
	
	Texture textures[]
	{
		Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};
	
	shaderProgram = new Shader("default.vert", "default.frag");

	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	floorEntity  = new Mesh(verts,ind, tex);
	
	lightShader = new Shader("light.vert", "light.frag");
	
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));


	lightEntity = new Mesh(lightVerts, lightInd, tex);



}

void Game::setUpEntities()
{

    
	//purple
	glm::vec4 lightColor = glm::vec4(1.0f, 0.4f, 0.8f, 0.3f);
	
	//glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);


	lightShader->use();
	lightShader->set_model_matrix(lightModel);
	lightShader->set_light_color(lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	
	shaderProgram->use();

	shaderProgram->set_model_matrix(objectModel);
	
	shaderProgram->set_light_color(lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	
	shaderProgram->set_light_position(lightPos.x, lightPos.y, lightPos.z);

 	//mainCamera  = new Camera(Game::Width, Game::Height, glm::vec3(0.0f, 0.0f, 2.0f));
	mainCamera = dynamic_cast<MainCamera*>(&manager.addEntityClass<MainCamera>());


	

}

void Game::drawFirstViewPort(float deltaTime)
{


}

void Game::setLights()
{
}
