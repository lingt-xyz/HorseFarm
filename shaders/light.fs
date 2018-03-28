#version 330 core

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

in vec4 color;


uniform vec3 viewPos;
uniform Material material;
uniform Light light;

uniform vec4 externalColor;

uniform bool texture_status;

// texture sampler
uniform sampler2D texture1;

void main() 
{ 
	vec3 ambient, diffuse, specular;
	vec3 norm = normalize(fs_in.Normal);
	vec3 lightDir = normalize(light.position - fs_in.FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	if(texture_status){
		//FragColor = texture(texture1, fs_in.TexCoords);
		ambient = light.ambient * texture(material.diffuse, fs_in.TexCoords).rgb;
		diffuse = light.diffuse * diff * texture(material.diffuse, fs_in.TexCoords).rgb;
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		specular = light.specular * (spec * material.specular);  
	}else{
		float ambientStrength = 0.5;
		ambient = ambientStrength * light.specular * vec3(externalColor);

		// diffuse
		diffuse = diff * light.specular * vec3(externalColor);
	
		// specular
		float specularStrength = 0.5;
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		specular = specularStrength * spec * light.specular * vec3(externalColor);

	}	

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
} 

