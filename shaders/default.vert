#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNorm;
layout (location=2) in vec3 aColor;
layout (location=3) in vec3 aOffset;
out vec3 normColor;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(aPos + aOffset, 1.0);
    normColor = aNorm;
}