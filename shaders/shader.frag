#version 450 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

const int amountOfTextures = 2;
uniform sampler2D textures[amountOfTextures];

void main()
{
    vec4 oTexture = mix(texture(textures[0], TexCoord), texture(textures[1], TexCoord), 0.5f);
    FragColor = oTexture;
}
