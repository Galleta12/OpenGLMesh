#include "BezierCurveComponent.h"

BezierCurveComponent::BezierCurveComponent(glm::vec4 color, int numSegments)
{

    
    
    
    mColor = color;
    m_numSegments = numSegments;

    //set it up as exist
    mExist = true;    

    
    Vertex vertices[] =
    { //               COORDINATES          
        Vertex{glm::vec3(-0.95f, -0.95f,  0.0f)},
        Vertex{glm::vec3(-0.95f, -0.95f, 0.0f)},
        Vertex{glm::vec3(-0.95f, -0.95f, 0.0f)},
        Vertex{glm::vec3(-0.95f, -0.95f,  0.0f)}
    };
    
  
    
    
    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    //vao
    mVAO.Bind();
    //generate vertex buffer
    VBO VBO(verts);




	mVAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);

    mVAO.Unbind();
    VBO.Unbind();
    //for the path

    glPatchParameteri(GL_PATCH_VERTICES, 4);


}



//link attribute
void BezierCurveComponent::update(float deltaTime)
{


}
//it will have its own drawCall
void BezierCurveComponent::drawBezier(Shader& shader,const CameraComponent &cameraComponent)
{

    
    
    
    shader.use();
    mVAO.Bind();

    ///remember to set the shaders for the model matrix
    setWorldViewProj(shader,cameraComponent);
    //the num segments
    setNumSegments(shader);
    //the line color
    setLineColor(shader);

    //set the render
    renderPointTS(GL_PATCHES);

    

}

void BezierCurveComponent::renderPointTS(int topology_type)
{

     if ((topology_type != GL_POINTS) && (topology_type != GL_PATCHES)) {
            printf("Invalid topology type 0x%x\n", topology_type);
            //exit(1);
    }

    glDrawArrays(topology_type, 0, 4);


}

void BezierCurveComponent::setNumSegments(Shader& shader)
{

    shader.set_num_segments_Tesallator(m_numSegments);    
}

void BezierCurveComponent::setLineColor(Shader& shader)
{
    shader.set_line_color_Tesallator(mColor);    

}

void BezierCurveComponent::setWorldViewProj(Shader& shader,const CameraComponent &cameraComponent)
{
    
    
    glm::mat4 scalor = glm::scale(model,glm::vec3(100.0f,100.0f,100.0f));

    shader.set_model_matrix(scalor);    
    
    shader.set_view_matrix(cameraComponent.viewMatrix);
    
    shader.set_projection_matrix(cameraComponent.projectionMatrix);

}
