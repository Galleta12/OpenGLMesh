#include "Game.h"
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>



#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "Components.h"
#include "MainCamera.h"

#include"Camera.h"



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};


GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
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



//initialize static variables
int Game::Width = 0;
int Game::Height = 0;

bool Game::isRunning = false;
        
GLFWwindow* Game::window = nullptr;

Game::WhoISCamera Game::cameraViewState = Game::WhoISCamera::MAINCAMERA;

Shader *shaderProgram = nullptr;

Shader  *lightShader = nullptr;



//Texture *brickTex = nullptr;

Texture *planksTex = nullptr;

Texture *planksSpec = nullptr;
//Camera *mainCamera = nullptr;

MainCamera *mainCamera = nullptr;


VAO *VAO1 = nullptr;


VAO *lightVAO = nullptr;


Manager manager;

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


    shaderProgram->use();
	


    glm::vec3 currentPosCamera = mainCamera->getCameraComponent()->Position;

	shaderProgram->set_eye_position(currentPosCamera.x,currentPosCamera.y, currentPosCamera.z);


    //mainCamera->Matrix(*shaderProgram, "camMatrix");

    for(auto& c : camerasWorld){
       c->draw(*shaderProgram); 
    }
	


	//brickTex->Bind();
	planksTex->Bind();
	planksSpec->Bind();

    VAO1->Bind();

	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

    lightShader->use();
	// Export the camMatrix to the Vertex Shader of the light cube
	
	
	
	//mainCamera->Matrix(*lightShader, "camMatrix");
	for(auto& c : camerasWorld){
        c->draw(*lightShader); 
    }
	
	
	


	// Bind the VAO so OpenGL knows to use it
	
	lightVAO->Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
		// Take care of all GLFW events
	glfwPollEvents();

}

void Game::clean()
{


    VAO1->Delete();
    lightVAO->Delete();
    //brickTex->Delete();
	planksTex->Delete();
	planksSpec->Delete();
	
	shaderProgram->Delete();
    lightShader->Delete();

    
	glfwDestroyWindow(window);
	window = NULL;
    // Terminate GLFW before ending the program
	
    glfwTerminate();
     std::cout << "Game closed" << std::endl;
}

void Game::setUpShaderAndBuffers()
{

    // Generates Shader object using shaders default.vert and default.frag
	shaderProgram = new Shader("default.vert", "default.frag");
	// Generates Vertex Array Object and binds it
	VAO1 = new VAO();
	VAO1->Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1->LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1->LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1->LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1->LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1->Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


    // Shader for light cube
	lightShader = new Shader("light.vert", "light.frag");
	// Generates Vertex Array Object and binds it
	lightVAO = new VAO();
	lightVAO->Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO->LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO->Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

    // brickTex = new Texture("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	// brickTex->texUnit(*shaderProgram, "tex0", 0);


	planksTex = new Texture("planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	planksTex->texUnit(*shaderProgram, "tex0", 0);

	planksSpec = new Texture("planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	planksSpec->texUnit(*shaderProgram, "tex1", 1);




}

void Game::setUpEntities()
{

    

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
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
