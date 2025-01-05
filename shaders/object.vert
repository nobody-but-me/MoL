#version 330 core

layout (location = 1) in vec3 _object_colour;
layout (location = 0) in vec3 _object_pos;

out vec3 _obj_colour;

void main() {
     gl_Position = vec4(_object_pos, 1.0);
     _obj_colour = _object_colour;
}