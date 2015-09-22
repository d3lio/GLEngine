#version 330 core

in vec2 UV;
in vec3 vertexPosition_ws;
in vec3 vertexNormal_cs;
in vec3 lightDirection_cs;
in vec3 eyeDirection_cs;

out vec3 color;

uniform sampler2D textureSampler;
uniform vec3 lightPosition_ws;
uniform vec3 lightColor;
uniform float lightPower;

void main ()
{
	vec3 n = normalize(vertexNormal_cs);
	vec3 l = normalize(lightDirection_cs);

    vec3 e = normalize(eyeDirection_cs);
    // Direction in which the triangle reflects the light
    vec3 r = reflect(-l, n);

    // Ambient : simulates indirect lighting
    // Diffuse : "color" of the object
    // Specular : reflective highlight, like a mirror
    vec3 materialDiffuseColor = texture2D(textureSampler, UV).rgb;
    vec3 materialAmbientColor = vec3(0.1, 0.1, 0.1) * materialDiffuseColor;
    vec3 materialSpecularColor = vec3(0.3, 0.3, 0.3);

    float vertexDistance = length(lightPosition_ws - vertexPosition_ws);

    // Cosine of the angle between the normal and the light direction,
    // clamped above 0
    //  - light is at the vertical of the triangle -> 1
    //  - light is perpendicular to the triangle -> 0
    //  - light is behind the triangle -> 0
    float cosTheta = clamp(dot(l,n), 0, 1);

    // Cosine of the angle between the Eye vector and the Reflect vector,
    // clamped to 0
    //  - Looking into the reflection -> 1
    //  - Looking elsewhere -> < 1
    float cosAlpha = clamp(dot(e,r), 0, 1);

	color =
        materialAmbientColor +
        materialDiffuseColor * lightColor * lightPower * cosTheta / (vertexDistance * vertexDistance) +
        materialSpecularColor * lightColor * lightPower * pow(cosAlpha, 5) / (vertexDistance * vertexDistance);
}
