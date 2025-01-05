
#ifndef OBJECT_H
#define OBJECT_H

/* #include <cglm/gtc/matrix_transform.hpp> */
/* #include <cglm/gtc/type_ptr.hpp> */

#include <stdbool.h>

#include <cglm/call.h>
#include <molson.h>

#define Object(x) object##x

typedef struct {

  unsigned int _vbo;
  unsigned int _vao;
  unsigned int _ebo;
  
  mat3  _transform;
  float _rotation;
  vec2  _position;
  vec2 _scale;
  
  unsigned int _texture;
  bool _texture_flip;
  
} Object;

typedef struct {

  const char *_name;
  
  Object _object;
  
} Triangle;

/* Rectangle Object(_new_rectangle)(float _width, float _heigth, float x, float y, const char *_texture_path, bool _texture_flip); */
/* void Object(_render_rectangle)(Rectangle *_self, Shader *_shader); */
/* void Object(_kill)(Object _self, Shader *_shader); */
void Object(_render_triangle)(Triangle *_triangle, Shader *_shader);
void Object(_kill)(Object *_self);
Triangle Object(_new_triangle)();

#endif//OBJECT_H
