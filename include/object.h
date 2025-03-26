
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
} TRIANGLE;

typedef struct {
    const char *_name;
    Object _object;
    
    const char *_texture_path;
    bool _texture_alpha;
    Texture _texture;
    // unsigned int _texture;
    bool _texture_flip;
    
    int _initialized;
} SPRITE;

void Object(_render_triangle)(TRIANGLE *_triangle, Shader *_shader);
TRIANGLE Object(_new_triangle)();

void Object(_render_sprite)(SPRITE *_sprite, Texture *_texture, Shader *_shader);
SPRITE Object(_new_sprite)(const char *_name, vec2 _initial_position, vec2 _initial_scale, vec3 _initial_rotation, vec3 _initial_colour);

void Object(_kill)(Object *_self);

#endif//OBJECT_H
