#version 460 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

// Gets the Texture Unit from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;


void main()
{
	FragColor = texture(diffuse0, texCoord) + texture(specular0, texCoord);
}