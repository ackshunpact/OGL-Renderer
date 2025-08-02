#version 330 core

in vec2 uvCoords;
in vec3 normColor;

uniform sampler2D myTextureSampler;

out vec4 FragColor;

uniform vec3 ourColor;

void main() {
    FragColor = texture(myTextureSampler, uvCoords);
}