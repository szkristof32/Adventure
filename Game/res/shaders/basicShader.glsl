#type vertex
#version 430 core

in vec3 in_position;
in vec2 in_textureCoord;

out vec2 pass_textureCoord;

void main() {
	gl_Position = vec4(in_position, 1.0);
	pass_textureCoord = in_textureCoord;
}

#type fragment
#version 430 core

in vec2 pass_textureCoord;

out vec4 out_colour;

void main() {
	out_colour = vec4(pass_textureCoord, 0.0, 1.0);
}