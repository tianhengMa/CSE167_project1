#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
//in float sampleExtraOutput;
in vec3 posOutput;
in vec3 normalOutput;

uniform vec3 color;

// Point Light fields
uniform vec3 in_lightColor;
uniform vec3 lightPos;
uniform vec3 lightAtten;

uniform vec3 viewPos;

// switch between rendering models
uniform int modelSwitch;
//uniform int lightSwitch;

// Materials
uniform vec3 in_ambient;
uniform vec3 in_diffuse;
uniform vec3 in_specular;
uniform float in_shininess;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 fragColor;

void main()
{
    float dist = distance(lightPos, posOutput); 
    vec3 lightColor = lightAtten.y * in_lightColor / dist;
    
    //vec3 lightPos = vec3(1);
    vec3 viewPos = vec3(0,0,20);
    
    // ambient
    vec3 ambient = lightColor * in_ambient;
      
    // diffuse
    vec3 norm = normalize(normalOutput);
    vec3 lightDir = normalize(lightPos - posOutput);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * (diff * in_diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - posOutput);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), in_shininess);
    vec3 specular = lightColor * (spec * in_specular);
        
    vec3 result = ambient + diffuse + specular;
    
    if (modelSwitch == 1){
        fragColor = vec4(normalOutput, 1.0);
    } else {
        fragColor = vec4(result, 1.0);
        
    }
    
    // Use the color passed in. An alpha of 1.0f means it is not transparent.
    //fragColor = vec4(normalOutput, sampleExtraOutput);
    vec3 temp = posOutput;
}
