#version 460 core
layout (location = 0) in vec3 aPos; // The position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord;


out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}