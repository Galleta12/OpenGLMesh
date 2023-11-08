#version 400 core


layout (location = 0) in vec3 VertexPosition;


void main()
{
    //the postion expaint it to an homogenous system
    gl_Position = vec4(VertexPosition, 1.0);
}
