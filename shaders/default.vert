#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNorm;
layout (location=2) in vec3 aColor;
layout (location=3) in vec3 aOffset;
layout (location=4) in vec2 vertexUV;

out vec2 uvCoords;
out vec3 normColor;

uniform mat4 transform;
uniform float scrollOffset;

void main() {
    gl_Position = transform * vec4(aPos + (aOffset * scrollOffset), 1.0);
    normColor = aNorm;
    uvCoords = vertexUV;
}