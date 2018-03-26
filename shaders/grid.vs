#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColors;
layout(location = 2) in vec2 aTexCoords;

out vec3 fragColor;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	fragColor = aColors;
	texCoords = aTexCoords;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	//gl_Position = vec4(aPos, 1.0);
}
