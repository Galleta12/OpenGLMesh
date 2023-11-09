#pragma once
#pragma once
#include <memory>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


class Game{

    public:

        //for adding groups labels, all entities and components will have acces to this
        enum GroupLabels : std::size_t
        {
           
            groupCameras,
            groupMeshes,
            groupMeshesNormal,
            groupLights,
            groupBezier
        };


        static enum WhoISCamera{
            MAINCAMERA,
            LOOKCAM,
            FOLLOWCAM
        };

        static WhoISCamera cameraViewState;
        
        static int Width, Height;
        static bool isRunning;
        static GLFWwindow* window;
   
        Game();
        ~Game();

        void init(const char* title, int posX, int posY, int width, int height, bool fullscreen);
          
        void handleEvents();

        void update(float deltaTime);

          //display of the boxes
        void display();
    
        void clean();
        //check if the game is running
        bool running() { return isRunning; }

    private:

        
        

        float currentTime = 0.0f;
        bool firstFrame = true;


        void setUpShaderAndBuffers();
        void setUpEntities();
        void drawFirstViewPort(float deltaTime);
        
        void setLights();
        void setSecondCam();
        void setThirCam();

        void updateCams();

        void updateFolloCam();


};
