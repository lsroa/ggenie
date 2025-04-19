#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 texture_coordinates;

out vec2 Coord;
out float Time;

uniform float iTime;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    Coord = texture_coordinates;
    Time = iTime;

    gl_Position = projection *
            view * model * vec4(pos, 0.0, 1.0);
}
