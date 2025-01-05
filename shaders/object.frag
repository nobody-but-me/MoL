#version 330 core

out vec4 _fragment_colour;
in vec3 _obj_colour;

void main() {
    _fragment_colour = vec4(_obj_colour, 1.0f);
}