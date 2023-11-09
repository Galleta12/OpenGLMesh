# OpenGLMesh

OpenGL, this is my first time trying to write some code for loading meshes, and how to use the  tessellation and geometry shader. I also set up some bezier curves for some interpolations movements.

On this project, this are the main features:

-The camera, there are 3 cameras, the first camera is a free look camera. Holding left click and dragging you can look around with the camera, use WASD to move.
The second camera is a look camera, is located above the the plane and is always looking to one of the light sources.
The third camera is located on the airplane mesh, and always looking to the dog mesh.
You can change cameras, with 1,2,3 keyboard.
The fist camera is set by default, so you can start moving normally with this camera, or change to other cameras with the 1,2,3 keyboard.

-Mesh loading
I am using the library called Assimp, for loading meshes. You can load many 3D formats with Assimp, thus it will save the model in its own data structure. I wrote a code that will parse the data structure of Assimp into meshes objects 
for loading 3D models, the Assimp library stores the model data in a tree structure format. Hence I transverse each node and store the vertex position, normal and tex coordinates. This can still be improved, since
loading multiple meshes, doesn't work well with my current code.
It also doesn't support multiple textures, for now I am only storing the diffuse and specular texture. This will be used in the frag shader by the light model.

Assimp documentation https://github.com/assimp/assimp

-Shaders


pipeline
Vert-Tessellation-Geometry-Rest-Frag

I am using the tessellation shader, for rendering a bezier curve. This helped me  a lot, to visualize bezier curves, hence it was easier to set up objects, to follow this bezier curves.
I am also using the geometry shader, by default the geometry shader is not doing anything. However on the simple.geom file u can call the function explosionGeo() instead of normalGeo(), it will
generate new geometry from the vertex, thus it will have an effect of an explosion.

There is also the normal geometry shader files, that will render the normals of the meshes, thus it will create a new effect on the models. This shader is being used by default, on the dog model object.
To set up the normal dog shader, go to game.cpp on the function setUpEntities() on the modelEntity3 code, change it to this:
modelEntity3 = dynamic_cast<ModelEntity*>(&manager.addEntityClass<ModelEntity>((modelPath3).c_str(),
	glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,-90.0f,0.0f),glm::vec3(0.3f,0.3f,0.3f)));
	modelEntity3->setUpBezier(bezierEntity5.getComponent<BezierCurveComponent>());

 -Lights
 I am using a phong spotlight model. I have two spotlights that are represented as cubes on the world, it will move and generate a spotlights effects on the texture surface, depending on the camera and
 light source position. However this could be improved by adding more flexibility on the parameters of the frag shader.
 The lights sources are always moving along a bezier curve, hence the frag shader will generate a nice effect on the textures.

 Run the project.

 You can click on the .exe file and the project will run correctly, however dont't move the .exe file from the root directory to avoid any error. The other way is to open the solution file of visual studio and run it from there.
 The  last option is just to run premake5.exe vs"version" on the command promt, thus it will generate the visual studio solution files.

 Is important to know that this code is using OpenGL 4.0 version, since it is using the tessellation shader, that was introduced on the 4.0 version. If your computer doesn't support OpenGL 4.0 version, it will not run correctly.


 Is also important to note that this is not a finish version, there are  some code and functions that can be improved, when I use renderDoc for debuggin I realize that I peform
 multiple draw calls, this could be improved to get a better performance.
The project is still using a ECS system, however this ECS is  not the best, since you can run into memory leaks errors. That's why I am sometimes using simple classes instead of a component to avoid any memory leak error.
The shaders are on the src/shaders there is all the source code of the shaders that I am using



![image](https://github.com/Galleta12/OpenGLMesh/assets/79543944/3064b0c9-13e1-451e-890a-0f5699a090be)

 
 
