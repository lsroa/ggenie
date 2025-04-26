#version 330 core

in vec2 Coord;
in float Time;
in vec2 TextureSize;
in vec2 SpriteSize;
in vec2 SpriteOffset;

layout(location = 0) out vec4 FragColor;

uniform sampler2D texture_1;

void main() {
    vec2 spriteOffset = SpriteOffset / TextureSize;
    vec2 spriteUVSize = SpriteSize / TextureSize;

    vec2 sampleUV = spriteOffset + Coord * spriteUVSize;

    vec4 col1 = texture(texture_1, sampleUV);
    FragColor = col1;
}
