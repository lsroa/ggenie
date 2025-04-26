#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 texture_coordinates;

out vec2 Coord;
out float Time;
out vec2 TextureSize;
out vec2 SpriteSize;
out vec2 SpriteOffset;

uniform float iTime;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 sprite_size;
uniform vec2 sprite_offset;
uniform vec2 texture_size;

void main() {
    Coord = texture_coordinates;
    Time = iTime;
    TextureSize = texture_size;
    SpriteSize = sprite_size;
    SpriteOffset = sprite_offset;

    gl_Position = projection *
            view * model * vec4(pos, 0.0, 1.0);
}
