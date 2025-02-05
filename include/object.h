
#ifndef OBJECT_H
#define OBJECT_H

/* #include <cglm/gtc/matrix_transform.hpp> */
/* #include <cglm/gtc/type_ptr.hpp> */

#include <stdbool.h>

#include <cglm/call.h>
#include <molson.h>
#include "./data.h"

#define Object(x) object##x

typedef struct {
    const char *_name;
    Object _object;
} Triangle;

typedef struct {
    const char *_name;
    Object _object;
} Sprite;

void Object(_render_triangle)(Triangle *_triangle, Shader *_shader);
Triangle Object(_new_triangle)();

void Object(_render_sprite)(Texture2D *_texture, vec2 _position, vec2 _scale, float _rotation, vec3 _colour, Sprite *_sprite, Shader *_shader);
Sprite Object(_new_sprite)();

void Object(_kill)(Object *_self);

#endif//OBJECT_H
