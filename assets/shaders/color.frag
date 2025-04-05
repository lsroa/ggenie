#version 330 core

in vec3 Color;
in vec2 Coord;
in float Time;

layout(location = 0) out vec4 FragColor;

uniform sampler2D texture_1;

void main() {
    vec4 col1 = texture(texture_1, vec2(Coord.x, Coord.y));
    FragColor = col1;
}
