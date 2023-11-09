#version 400 core

//type of primitive
layout (triangles) in;
//output primitive
layout (triangle_strip, max_vertices = 3) out;


uniform bool isExplosion;

//output to the fragment shader
//vert -geom-frag
out vec3 Normal;

out vec3 color;

out vec2 uv_coordinates_tex;

out vec3 position;
//import data geometry shader
in DATA
{
    vec3 Normal;
	vec3 color;
	vec2 uv_coordinates_tex;
    mat4 projection;
    vec3 position;
} data_in[];



void normalGeo(){
    gl_Position = data_in[0].projection * gl_in[0].gl_Position;
    Normal = data_in[0].Normal;
    color = data_in[0].color;
    uv_coordinates_tex = data_in[0].uv_coordinates_tex;
    
    position = data_in[0].position;
    //declare we are done proccessing the current vertex
    EmitVertex();

    //we do the same for the other 3 vertices of the triangle.
    gl_Position = data_in[1].projection * gl_in[1].gl_Position;
    Normal = data_in[1].Normal;
    color = data_in[1].color;
    uv_coordinates_tex = data_in[1].uv_coordinates_tex;
    position = data_in[1].position;
    //declare we are done proccessing the current vertex
    EmitVertex();
    
    
    //we do the same for the other 3 vertices of the triangle.
    gl_Position = data_in[2].projection * gl_in[2].gl_Position;
    Normal = data_in[2].Normal;
    color = data_in[2].color;
    uv_coordinates_tex = data_in[2].uv_coordinates_tex;
    position = data_in[2].position;
    //declare we are done proccessing the current vertex
    EmitVertex();



    //when we are done using the primitives
    EndPrimitive();
}

//cross product effect with explosion
void explosionGeo(){
    //this calculates the surface normal
    vec3 vector0 = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position);

    vec3 vector1 = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
    vec4 surfaceNormal = vec4(normalize(cross(vector0, vector1)), 0.0f);

    gl_Position = data_in[0].projection * (gl_in[0].gl_Position + surfaceNormal);
    Normal = data_in[0].Normal;
    color = data_in[0].color;
    uv_coordinates_tex = data_in[0].uv_coordinates_tex;
    position = data_in[0].position;
    EmitVertex();

    gl_Position = data_in[1].projection * (gl_in[1].gl_Position + surfaceNormal);
    Normal = data_in[1].Normal;
    color = data_in[1].color;
    uv_coordinates_tex = data_in[1].uv_coordinates_tex;
    position = data_in[1].position;
    EmitVertex();

    gl_Position = data_in[2].projection * (gl_in[2].gl_Position + surfaceNormal);
    Normal = data_in[2].Normal;
    color = data_in[2].color;
    uv_coordinates_tex = data_in[2].uv_coordinates_tex;
    position = data_in[2].position;
    EmitVertex();

    EndPrimitive();
}

//cross product effect with explosion

// void main()
// {
    //this calculates the surface normal
//    vec3 vector0 = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position);

//    vec3 vector1 = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
//    vec4 surfaceNormal = vec4(normalize(cross(vector0, vector1)), 0.0f);

//    gl_Position = data_in[0].projection * (gl_in[0].gl_Position + surfaceNormal);
//    Normal = data_in[0].Normal;
//    color = data_in[0].color;
//    uv_coordinates_tex = data_in[0].uv_coordinates_tex;
//    position = data_in[0].position;
//    EmitVertex();

//    gl_Position = data_in[1].projection * (gl_in[1].gl_Position + surfaceNormal);
//    Normal = data_in[1].Normal;
//    color = data_in[1].color;
//    uv_coordinates_tex = data_in[1].uv_coordinates_tex;
//    position = data_in[1].position;
//    EmitVertex();

//    gl_Position = data_in[2].projection * (gl_in[2].gl_Position + surfaceNormal);
//    Normal = data_in[2].Normal;
//    color = data_in[2].color;
//    uv_coordinates_tex = data_in[2].uv_coordinates_tex;
//    position = data_in[2].position;
//    EmitVertex();

//    EndPrimitive();
// }

void main()
{

    //use the explosion if u want to have other shader
    normalGeo();
    //explosionGeo();

}
