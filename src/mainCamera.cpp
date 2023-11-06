#include "MainCamera.h"

MainCamera::MainCamera(Manager &mManager)
:Entity(mManager)
{

    Entity::addComponent<CameraComponent>(glm::vec3(0.0f, 0.0f, 2.0f));
    //needs to be on this group
    Entity::addGroup(Game::groupCameras);
    saveComponents();

}

MainCamera::~MainCamera()
{

    
 

}

void MainCamera::update(float deltaTime)
{

    Entity::update(deltaTime);
    //for this type of movement we want to use the look to constantly
    //look to the  place where the mouse is facing

    Inputs(deltaTime);
    RotationCamera(deltaTime);
    ZoomCamera(deltaTime);
    ApplyNewPosition(deltaTime);


}

void MainCamera::draw(Shader &shader)
{

    Entity::draw(shader);
}

void MainCamera::saveComponents()
{

    mCameraComponent = &Entity::getComponent<CameraComponent>();
    //we want to draw at the beginning
    mCameraComponent->shouldDraw = true;

    glm::vec3 initialCenter = mCameraComponent->Position + mCameraComponent->Orientation;
    
    mCameraComponent->setLooKViewCamera(mCameraComponent->Position,initialCenter,mCameraComponent->Up);
    //for the shaders they are done on the draw using this data

    //for now the aspct ration is
    float aspect =  static_cast<float>(Game::Width / Game::Height);
    
    
    
    mCameraComponent->zoom = glm::radians(90.0f);
    
    mCameraComponent->setPerspectiveProjection(mCameraComponent->zoom,aspect, 0.1f,100.0f);


}

void MainCamera::RotationCamera(float deltaTime)
{

    // Handles mouse inputs
	if (glfwGetMouseButton(Game::window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(Game::window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(Game::window, (Game::Width / 2), (Game::Height / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(Game::window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (Game::Height / 2)) / Game::Height;
		float rotY = sensitivity * (float)(mouseX - (Game::Width / 2)) / Game::Width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(mCameraComponent->Orientation, glm::radians(-rotX), glm::normalize(glm::cross(mCameraComponent->Orientation, mCameraComponent->Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation,  mCameraComponent->Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			mCameraComponent->Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		mCameraComponent->Orientation = glm::rotate(mCameraComponent->Orientation, glm::radians(-rotY),  mCameraComponent->Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(Game::window, (Game::Width / 2), (Game::Height / 2));
	}
	else if (glfwGetMouseButton(Game::window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(Game::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}

}

void MainCamera::ZoomCamera(float deltaTime)
{

    if (glfwGetKey(Game::window, GLFW_KEY_Z) == GLFW_PRESS){
        mCameraComponent->zoom -= 0.25f * deltaTime;    
    }
     
    if (glfwGetKey(Game::window, GLFW_KEY_X) == GLFW_PRESS){
        mCameraComponent->zoom += 0.25f * deltaTime;
    }

}

void MainCamera::ApplyNewPosition(float deltaTime)
{
    glm::vec3 newCenter = mCameraComponent->Position + mCameraComponent->Orientation;
    mCameraComponent->setLooKViewCamera(mCameraComponent->Position,newCenter,mCameraComponent->Up);
    float aspect =  static_cast<float>(Game::Width / Game::Height);
    
    //mCameraComponent->setPerspectiveProjection(RadToDegree::ToRadians(45.0f),aspect, 0.1f,100.0f);
    mCameraComponent->setPerspectiveProjection(mCameraComponent->zoom,aspect, 0.1f,100.0f);

}

void MainCamera::Inputs(float deltaTime)
{

    // Adjust speed based on delta time (for smoother movement)
    float adjustedSpeed = cameraSpeed * deltaTime;

    if (glfwGetKey(Game::window, GLFW_KEY_W) == GLFW_PRESS)
    {
        mCameraComponent->Position += adjustedSpeed * mCameraComponent->Orientation;
    }
    if (glfwGetKey(Game::window, GLFW_KEY_A) == GLFW_PRESS)
    {
        mCameraComponent->Position += adjustedSpeed * -glm::normalize(glm::cross(mCameraComponent->Orientation, mCameraComponent->Up));
    }
    if (glfwGetKey(Game::window, GLFW_KEY_S) == GLFW_PRESS)
    {
        mCameraComponent->Position += adjustedSpeed * -mCameraComponent->Orientation;
    }
    if (glfwGetKey(Game::window, GLFW_KEY_D) == GLFW_PRESS)
    {
        mCameraComponent->Position += adjustedSpeed * glm::normalize(glm::cross(mCameraComponent->Orientation, mCameraComponent->Up));
    }
    if (glfwGetKey(Game::window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        mCameraComponent->Position += adjustedSpeed * mCameraComponent->Up;
    }
    if (glfwGetKey(Game::window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        mCameraComponent->Position += adjustedSpeed * -mCameraComponent->Up;
    }
    if (glfwGetKey(Game::window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        adjustedSpeed = 0.4f;
    }
    else if (glfwGetKey(Game::window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        adjustedSpeed = 0.1f;
    }

}
