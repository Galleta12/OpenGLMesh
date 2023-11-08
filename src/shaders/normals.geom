#version 400 core

layout (triangles) in;
//destroy and create new geometry, we not construct 6 vertices
layout (line_strip, max_vertices = 6) out;

in DATA
{
    vec3 Normal;
	vec3 color;
	vec2 uv_coordinates_tex;
    mat4 projection;
	vec3 position;
} data_in[];


void main()
{
    gl_Position = data_in[0].projection * gl_in[0].gl_Position;
    EmitVertex();
    //move to the next one will a littfle offset and point into the normal direction
    gl_Position = data_in[0].projection * (gl_in[0].gl_Position + 0.01f * vec4(data_in[0].Normal, 0.0f));
    EmitVertex();
    //to dont link all the lines together we end the current primitive
    EndPrimitive();

    gl_Position = data_in[1].projection * gl_in[1].gl_Position;
    EmitVertex();
    gl_Position = data_in[1].projection * (gl_in[1].gl_Position + 0.01f * vec4(data_in[1].Normal, 0.0f));
    EmitVertex();
    EndPrimitive();

    gl_Position = data_in[2].projection * gl_in[2].gl_Position;
    EmitVertex();
    gl_Position = data_in[2].projection * (gl_in[2].gl_Position + 0.01f * vec4(data_in[2].Normal, 0.0f));
    EmitVertex();
    EndPrimitive();
}

