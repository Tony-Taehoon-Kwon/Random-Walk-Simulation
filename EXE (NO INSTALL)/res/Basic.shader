#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;    // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal; // the normal variable has attribute position 1
  
out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	FragPos = vec3(model *vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
	LightPos = lightPos;
}  

#shader fragment
#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;

uniform vec3 objectColor;
uniform vec3 viewPos;
uniform vec3 I_a;
uniform vec3 I_d;
uniform float k_a;
uniform float k_d;

void main()
{  
	// Calculate light direction
	vec3 lightDir = normalize(LightPos - FragPos);

	// Calculate view direction
	vec3 viewDir = normalize(viewPos - FragPos);
		
	// Normalize vector3 Normal
	vec3 norm = normalize(Normal);

	// Calculate diffuse value using norm and light direction
	float diff = max(dot(norm, lightDir), 0.0);
	
	// Calculate each ambient, diffuse, specular 
	vec3 ambient = I_a * 0.8;//k_a * I_a;
	vec3 diffuse = (k_d * diff) * I_d;
	
	// Add all those three and multiply by color of object
	vec3 local = (ambient + diffuse) * objectColor;
	//vec3 local = (ambient) * objectColor;
	
	// Send it to FragColor
	FragColor = vec4(local, 1.f);
}