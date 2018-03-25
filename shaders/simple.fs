#version 330 core

out vec4 FragColor;

in vec4 fragmentColor;

uniform bool self_color;

void main()
{
	if(self_color){
		FragColor = fragmentColor;
	}else{
		FragColor = vec4(1.0);
	}
}
