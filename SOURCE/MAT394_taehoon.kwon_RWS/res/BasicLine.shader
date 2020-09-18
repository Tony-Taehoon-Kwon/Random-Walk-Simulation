#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;    // the position variable has attribute position 0

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}  

#shader fragment
#version 330 core
out vec4 FragColor;

uniform int sphere_index;

void main()
{ 
	// Send it to FragColor
	switch (sphere_index) {
	case 0:	  FragColor = vec4(0.97647f, 0.341176f, 0.356862f, 1.f);	break;
	case 1:   FragColor = vec4(0.349019f, 0.533333f, 0.968627f, 1.f);	break;
	case 2:   FragColor = vec4(0.349019f, 0.968627f, 0.443137f, 1.f);	break;
	case 3:   FragColor = vec4(0.984313f, 0.949019f, 0.333333f, 1.f);	break;
	case 4:   FragColor = vec4(0.505882f, 0.317647f, 1.0f, 1.f);		break;
	case 5:   FragColor = vec4(0.980392f, 0.623529f, 0.337254f, 1.f);	break;
	case 6:   FragColor = vec4(1.0f, 0.0f, 0.764f, 1.f);				break;
	case 7:   FragColor = vec4(0.066666f, 0.549019f, 0.807843f, 1.f);	break;
	case 8:   FragColor = vec4(0.925781f, 0.796875f, 0.492187f, 1.f);	break;
	case 9:   FragColor = vec4(0.0f, 1.0f, 0.784f, 1.f);				break;
	case 10:  FragColor = vec4(0.85098f, 0.85098f, 0.85098f, 1.f);		break;
	default:  FragColor = vec4(0.0f, 0.0f, 0.0f, 1.f);					break;
	}
}