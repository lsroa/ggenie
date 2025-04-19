#version 330 core

in vec2 Coord;
in float Time;

layout(location = 0) out vec4 FragColor;

uniform sampler2D texture_1;

void main() {
    vec4 col1 = texture(texture_1, Coord);
    FragColor = col1;
}
