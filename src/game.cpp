
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;
//------------------------------

#include <assimp/Importer.hpp>      
#include <assimp/scene.h>       
#include <assimp/postprocess.h>



#include "Game.h"
#include<iostream>

#include "IncludesForMath.h"
#include <vector>
#include "Components.h"

#include "ModelEntity.h"

#include "Mesh.h"
#include "MainCamera.h"
#include "GameObject.h"


//initialize static variables
int Game::Width = 0;
int Game::Height = 0;

bool Game::isRunning = false;
        
GLFWwindow* Game::window = nullptr;

Game::WhoISCamera Game::cameraViewState = Game::WhoISCamera::MAINCAMERA;

Shader *shaderProgram = nullptr;

Shader *geomShader = nullptr;

Shader  *lightShader = nullptr;

Shader  *bezierShader = nullptr;

ModelEntity *modelEntity  = nullptr;
//Model *model = nullptr;



//Camera *mainCamera = nullptr;

MainCamera *mainCamera = nullptr;
GameObject *lightEntity = nullptr;

GameObject *floorEntity = nullptr;

//Model *modelEntity = nullptr;


//Mesh *floorEntity = nullptr;
//Mesh *lightEntity = nullptr;

Manager manager;


auto &bezierEntity(manager.addEntity());






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

	glPointSize(10.0f);
    glLineWidth(10.0f);

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
	

}

void Game::display()
{

    glEnable(GL_DEPTH_TEST);

    //glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 0.0f);
    
	glViewport(0, 0, Width, Height);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
   

	

	
	
	const CameraComponent camera = *mainCamera->getCameraComponent();

   

	
	
	for(auto& m :meshesWorld){
		//m->draw(*geomShader);
		m->draw(*shaderProgram);
		
		if(m->hasComponent<BezierCurveComponent>()){
			BezierCurveComponent *bezier = &m->getComponent<BezierCurveComponent>();
			bezier->drawBezier(*bezierShader,camera);
		
		}
	
	}
	

	for(auto& l :lightsWorld){
		l->draw(*lightShader);
	}


	for(auto& c : camerasWorld){
        //c->draw(*geomShader);
        c->draw(*shaderProgram);
    }
	
	
	
	for(auto& c : camerasWorld){
        c->draw(*lightShader); 
    }
	
    
	for(auto& c : camerasWorld){
        c->draw(*bezierShader); 
    }



	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
		// Take care of all GLFW events
	glfwPollEvents();

}

void Game::clean()
{

    
	glfwDestroyWindow(window);
	window = NULL;
    // Terminate GLFW before ending the program
	
    glfwTerminate();
     std::cout << "Game closed" << std::endl;
}

void Game::setUpShaderAndBuffers()
{


	
	
	geomShader = new Shader("normals.vert", "normals.geom","normals.frag");
	shaderProgram = new Shader("simple.vert", "simple.geom","simple.frag");
	

	//primivite mesh
	//floorEntity.addComponent<PlaneComponent>("planks.png","planksSpec.png");
	
	floorEntity = dynamic_cast<GameObject*>(&manager.addEntityClass<GameObject>("planks.png","planksSpec.png"));

	lightShader = new Shader("light.vert", "light.frag");
	
	
	lightEntity = dynamic_cast<GameObject*>(&manager.addEntityClass<GameObject>());
	
    
	bezierShader = new Shader("bezier.vert","bezier.tcs","bezier.tes","bezier.frag");


	//add bezier for testing
	bezierEntity.addComponent<BezierCurveComponent>(glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),50);
	bezierEntity.addGroup(Game::groupMeshes);



}

void Game::setUpEntities()
{

    


	//std::string modelPath = "models/map/scene.gltf";
	//std::string modelPath = "models/wolf_demon_low_poly/scene.gltf";
	//std::string modelPath = "models/spider/spider.obj";
	std::string modelPath = "models/airplane/scene.gltf";
	
	
	
	modelEntity = dynamic_cast<ModelEntity*>(&manager.addEntityClass<ModelEntity>((modelPath).c_str()));
	
	
	
	//purple
	//glm::vec4 lightColor = glm::vec4(1.0f, 0.4f, 0.8f, 0.3f);
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	
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
	
	
	geomShader->use();

	geomShader->set_model_matrix(objectModel);
	
	
 	//mainCamera  = new Camera(Game::Width, Game::Height, glm::vec3(0.0f, 0.0f, 2.0f));
	mainCamera = dynamic_cast<MainCamera*>(&manager.addEntityClass<MainCamera>());


	

}

void Game::drawFirstViewPort(float deltaTime)
{


}

void Game::setLights()
{
}
