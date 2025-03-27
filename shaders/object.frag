#version 330 core

in vec2 _texture_coords;
out vec4 _object_colour;

uniform sampler2D _object_image;
uniform vec3 _colour;
uniform bool _is_textured;

void main() {
     if (_is_textured) {
     	_object_colour = vec4(_colour, 1.0f) * texture(_object_image, _texture_coords);
     }
     else {
     	_object_colour = vec4(_colour, 1.0f);
     }
}