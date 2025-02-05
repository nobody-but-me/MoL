
#ifndef DATA_H
#define DATA_H

#include <stdbool.h>

typedef struct {
    unsigned int _vbo;
    unsigned int _vao;
    unsigned int _ebo;
    
    mat4  _transform;
    float _rotation;
    vec3 _position;
    vec3 _scale;
    
    unsigned int _texture;
    bool _texture_flip;
} Object;

typedef struct {
    unsigned int _fragment_shader;
    unsigned int _vertex_shader;
    unsigned int ID;
} Shader;

typedef struct {
    unsigned int _internal_format;
    unsigned int _image_format;
    unsigned int _filter_min;
    unsigned int _filter_max;
    unsigned int _wrap_s;
    unsigned int _wrap_t;
    unsigned int _height;
    unsigned int _width;
    unsigned int ID;
} Texture2D;


#endif//DATA_H
