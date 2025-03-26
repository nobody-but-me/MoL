#version 330 core

layout (location = 0) in vec4 _object_vertex;

uniform mat4 _projection;
uniform mat4 _transform;
uniform mat4 _view;

out vec2 _texture_coords;

void main() {
     _texture_coords = _object_vertex.zw;
     gl_Position = _projection * _view * _transform * vec4(_object_vertex.xy, 0.0f, 1.0f);
}