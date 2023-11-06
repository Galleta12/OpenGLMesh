
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



Game::Game()
{

    
	glfwInit();

	// opengl version 3.3
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

	
	
	
	model->Draw(*shaderProgram, *mainCamera->getCameraComponent());
   

	// floorEntity->Draw(*shaderProgram, *mainCamera->getCameraComponent());
	// lightEntity->Draw(*lightShader, *mainCamera->getCameraComponent());
    

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





    
	
	shaderProgram = new Shader("default.vert", "default.frag");


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	
    
    shaderProgram->use();
	
    
    
    shaderProgram->set_light_color(lightColor.x, lightColor.y, lightColor.z, lightColor.w);    
    shaderProgram->set_light_position(lightPos.x, lightPos.y, lightPos.z);

	
   

	
}

void Game::setUpEntities()
{

    

	
 	//mainCamera  = new Camera(Game::Width, Game::Height, glm::vec3(0.0f, 0.0f, 2.0f));
	mainCamera = dynamic_cast<MainCamera*>(&manager.addEntityClass<MainCamera>());


	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string modelPath = "map/scene.gltf";
	
	//std::string modelPath = "bunny/scene.gltf";
	
	// Load in a model
	model = new Model((modelPath).c_str());




	

}

void Game::drawFirstViewPort(float deltaTime)
{


}

void Game::setLights()
{
}
