
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;


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
#include "ControlPointsVertices.h"


//white

glm::vec4 lightColor1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); 

glm::vec4 lightColor2 = glm::vec4(1.0f, 0.4f, 0.8f, 0.3f);

#define LighColor1 lightColor1.x, lightColor1.y, lightColor1.z, lightColor1.w

#define LighColor2 lightColor2.x, lightColor2.y, lightColor2.z, lightColor2.w


//initialize static variables
int Game::Width = 0;
int Game::Height = 0;

bool Game::isRunning = false;
        
GLFWwindow* Game::window = nullptr;

Game::WhoISCamera Game::cameraViewState = Game::WhoISCamera::MAINCAMERA;

Shader *shaderProgram = nullptr;

Shader *geomShader = nullptr;


Shader  *lightShader = nullptr;

Shader  *lightShader2 = nullptr;


Shader  *bezierShader = nullptr;


ModelEntity *modelEntity  = nullptr;




MainCamera *mainCamera = nullptr;

GameObject *lightEntity = nullptr;

GameObject *lightEntity2 = nullptr;

GameObject *floorEntity = nullptr;

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

    
	if(firstFrame){
		currentTime = 0.0f;
		firstFrame = false;
	
	}else{
		currentTime += deltaTime;
	}
	

	BezierCurveComponent *bezier= &bezierEntity.getComponent<BezierCurveComponent>();
	bezier->setPosBezier(currentTime);

	// //get the current point of light
	// TransformComponent *lighTransform = &lightEntity->getComponent<TransformComponent>();
	
	

	// lighTransform->setPosition(bezier->getCurrentPos(currentTime,lighTransform->getPosition()));

	

	manager.refresh();
    manager.update(deltaTime);
	


}

void Game::display()
{

    glEnable(GL_DEPTH_TEST);

   
	//glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 0.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, Width, Height);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
   

	

	
	
	const CameraComponent camera = *mainCamera->getCameraComponent();

   
	setLights();
	
	
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
		l->draw(*lightShader2);
	}
	
	

	for(auto& c : camerasWorld){
        //c->draw(*geomShader);
        c->draw(*shaderProgram);
        c->draw(*lightShader2); 
        c->draw(*lightShader); 

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


	bezierShader = new Shader("bezier.vert","bezier.tcs","bezier.tes","bezier.frag");


	
	
	
	//add bezier for testing
	bezierEntity.addComponent<BezierCurveComponent>(glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),50,
	bezierControl1,2.0f,5.0f);
	bezierEntity.addGroup(Game::groupMeshes);
	
	
	geomShader = new Shader("normals.vert", "normals.geom","normals.frag");
	shaderProgram = new Shader("simple.vert", "simple.geom","simple.frag");
	

	
	
	floorEntity = dynamic_cast<GameObject*>(&manager.addEntityClass<GameObject>("planks.png","planksSpec.png",
	glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(5.0f,1.0f,5.0f)));

	lightShader = new Shader("light.vert", "light.frag");
	lightShader2 = new Shader("light.vert", "light.frag");
	
	
	lightEntity = dynamic_cast<GameObject*>(&manager.addEntityClass<GameObject>(glm::vec3(0.5f, 0.5f, 0.5f),glm::vec3(0.0f,0.0f,0.0f),
	glm::vec3(1.0f,1.0f,1.0f)));

	lightEntity->setUpBezier(bezierEntity.getComponent<BezierCurveComponent>());
	
	lightEntity2 = dynamic_cast<GameObject*>(&manager.addEntityClass<GameObject>(glm::vec3(0.0f, 2.5f, 4.5f),glm::vec3(0.0f,0.0f,0.0f),
	glm::vec3(1.0f,1.0f,1.0f)));
	
    



}

void Game::setUpEntities()
{

    


	//std::string modelPath = "models/map/scene.gltf";
	//std::string modelPath = "models/wolf_demon_low_poly/scene.gltf";
	//std::string modelPath = "models/spider/spider.obj";
	std::string modelPath = "models/airplane/scene.gltf";
	
	
	
	modelEntity = dynamic_cast<ModelEntity*>(&manager.addEntityClass<ModelEntity>((modelPath).c_str(),
	glm::vec3(0.0f,2.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.5f,0.5f,0.5f)));
	
	
	
	//purple
	//glm::vec4 lightColor = glm::vec4(1.0f, 0.4f, 0.8f, 0.3f);
	// glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	
	mainCamera = dynamic_cast<MainCamera*>(&manager.addEntityClass<MainCamera>());


	

}

void Game::drawFirstViewPort(float deltaTime)
{


}

void Game::setLights()
{

	shaderProgram->use();
	
	shaderProgram->set_light_color(LighColor1);
	
	shaderProgram->set_light_color2(LighColor2);
	
	
	
	lightShader->use();
	//for the light shader we dont have two differnt lights
	//is one per object in the shader
	lightShader->set_light_color(LighColor2);
	
	lightShader2->use();
	//for the light shader we dont have two differnt lights
	//is one per object in the shader
	lightShader2->set_light_color(LighColor1);
	
	

	shaderProgram->use();



	glm::vec3 lightPos1 = lightEntity->getTransform().getPosition();
	glm::vec3 lightPos2 = lightEntity2->getTransform().getPosition();
	
	
	shaderProgram->set_light_position(lightPos1.x,lightPos1.y,lightPos1.z);
	shaderProgram->set_light_position2(lightPos2.x,lightPos2.y,lightPos2.z);



}
