#version 330 core

in vec4 fragColor;

out vec4 color;

uniform vec4 aColor;

void main()
{
	color = aColor;
}
