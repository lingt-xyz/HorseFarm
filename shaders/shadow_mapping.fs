#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform bool texture_on;
uniform bool shadow_on;

// for texture only
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

uniform Material material;
uniform Light light;

uniform vec4 shader_color;

uniform sampler2D texture1;
// end of for texture only

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 3.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{    
	if(shadow_on){
		vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
		vec3 normal = normalize(fs_in.Normal);
		vec3 lightColor = vec3(1.0);
		// ambient
		vec3 ambient = 0.3 * color;
		// diffuse
		vec3 lightDir = normalize(lightPos - fs_in.FragPos);
		float diff = max(dot(lightDir, normal), 0.0);
		vec3 diffuse = diff * lightColor;
		// specular
		vec3 viewDir = normalize(viewPos - fs_in.FragPos);
		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = 0.5;
		vec3 halfwayDir = normalize(lightDir + viewDir);  
		spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
		vec3 specular = spec * lightColor;    
		// calculate shadow
		float shadow = ShadowCalculation(fs_in.FragPosLightSpace);                      
		vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    

		FragColor = vec4(lighting, 1.0);
	}else{
		vec3 ambient, diffuse, specular;
		vec3 norm = normalize(fs_in.Normal);
		vec3 lightDir = normalize(light.position - fs_in.FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 viewDir = normalize(viewPos - fs_in.FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);

		if(texture_on){
			ambient = light.ambient * texture(material.diffuse, fs_in.TexCoords).rgb;
			diffuse = light.diffuse * diff * texture(material.diffuse, fs_in.TexCoords).rgb;
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
			specular = light.specular * (spec * material.specular);  
		}else{
			float ambientStrength = 0.5;
			ambient = ambientStrength * light.specular * vec3(shader_color);

			// diffuse
			diffuse = diff * light.specular * vec3(shader_color);
	
			// specular
			float specularStrength = 0.5;
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
			specular = specularStrength * spec * light.specular * vec3(shader_color);

		}	

		vec3 result = ambient + diffuse + specular;
		FragColor = vec4(result, 1.0);
	}     
    
}
