#version 330 core

// _ms = model space
// model matrix
// _ws = world space
// view matrix
// _cs = camera space
// projection matrix
// _ps = homogeneous space

layout (location = 0) in vec3 vertexPosition_ms;
layout (location = 1) in vec2 vertexUV;
layout (location = 2) in vec3 vertexNormal_ms;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 mvpMatrix;
uniform vec3 lightPosition_ws;

out vec2 UV;
out vec3 vertexPosition_ws;
out vec3 vertexNormal_cs;
out vec3 lightDirection_cs;
out vec3 eyeDirection_cs;

void main ()
{
    gl_Position = mvpMatrix * vec4(vertexPosition_ms, 1);

	//vec3 vertexPosition_cs = (viewMatrix * modelMatrix * vec4(vertexPosition_ms, 1)).xyz;
	vertexPosition_ws = (modelMatrix * vec4(vertexPosition_ms, 1)).xyz;
	vec3 vertexPosition_cs = (viewMatrix * vec4(vertexPosition_ws, 1)).xyz;

	// Vector that goes from the vertex to the camera, in camera space.
	// Camera is always at (0,0,0) in camera space;
	eyeDirection_cs = vec3(0,0,0) - vertexPosition_cs; // can simply use -

	vec3 lightPosition_cs = (viewMatrix * vec4(lightPosition_ws, 1)).xyz;

	// Vector that goes from the vertex to the light, in camera space.
	lightDirection_cs = lightPosition_cs + eyeDirection_cs;

	// Only correct if ModelMatrix does not scale the model! Use its inverse transpose if not.
	vertexNormal_cs = (viewMatrix * modelMatrix * vec4(vertexNormal_ms, 0)).xyz;

    UV = vertexUV;
}
