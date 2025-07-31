#version 330 core

in vec3 normColor;

out vec4 FragColor;

uniform vec3 ourColor;

void main() {
    FragColor = vec4(abs(normColor.x), abs(normColor.y), abs(normColor.z), 1.0);
}