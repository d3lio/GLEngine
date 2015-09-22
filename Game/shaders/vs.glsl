#version 330 core

// _ms = modelspace
// _vs = viewspace
// _ps = projspace

layout (location = 0) in vec3 vertexPosition_ms;
layout (location = 1) in vec2 vertexUV;

uniform mat4 mvpMatrix;

out vec2 UV;

void main ()
{
    gl_Position = mvpMatrix * vec4 (vertexPosition_ms, 1);

    UV = vertexUV;
}
