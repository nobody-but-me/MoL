#version 330 core

in vec2 _texture_coords;
out vec4 _object_colour;

uniform sampler2D _object_image;
uniform vec3 _colour;

void main() {
    _object_colour = vec4(_colour, 1.0f) * texture(_object_image, _texture_coords);
}