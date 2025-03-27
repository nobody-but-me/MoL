
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <cglm/call.h>

#include <resource_manager.h>
#include <object.h>
#include <molson.h>
#include <data.h>


void Object(_kill)(Object *_self) {
    glDeleteVertexArrays(1, &_self->_vao);
    glDeleteBuffers(1, &_self->_vbo);
    glDeleteBuffers(1, &_self->_ebo);
    
    printf("[INFO] Object had been killed successfully. \n");
}

void Object(_render_rectangle)(SHAPE *_rect, Shader *_shader) {
    Molson(_use)(_shader);
    
    mat4 _transform;
    glm_mat4_identity(_transform);
    glm_translate(_transform, (vec3){_rect->_object._position[0], _rect->_object._position[1], _rect->_object._position[2]});
    
    glm_translate(_transform, (vec3){0.5f * _rect->_object._scale[0], 0.5f *_rect->_object._scale[1], 0.0f});
    glm_rotate(_transform, _rect->_object._rotation[0], (vec3){1.0f, 0.0f, 0.0f});
    glm_rotate(_transform, _rect->_object._rotation[1], (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate(_transform, _rect->_object._rotation[2], (vec3){0.0f, 0.0f, 1.0f});
    glm_translate(_transform, (vec3){-0.5f * _rect->_object._scale[0], -0.5f *_rect->_object._scale[1], 0.0f});
    
    glm_scale(_transform, (vec3){_rect->_object._scale[0], _rect->_object._scale[1], 1.0f});
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    Molson(_set_vector3_f)("_colour", _rect->_object._colour, false, _shader);
    Molson(_set_matrix4)("_transform", &_transform, false, _shader);
    Molson(_set_bool)("_is_textured", false, _shader);
    
    glBindVertexArray(_rect->_object._vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    
    return;
}
SHAPE Object(_new_rectangle)(const char *_name, vec2 _initial_position, vec2 _initial_scale, vec3 _initial_rotation, vec3 _initial_colour) {
    SHAPE _rect;
    _rect._name = _name;
    
    float _vertices[] = {
	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	
	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &_rect._object._vao);
    glGenBuffers(1, &_rect._object._vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, _rect._object._vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(_rect._object._vao);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    _rect._object._position[0] = _initial_position[0];
    _rect._object._position[1] = _initial_position[1];
    
    _rect._object._colour[0]   = _initial_colour[0];
    _rect._object._colour[1]   = _initial_colour[1];
    _rect._object._colour[2]   = _initial_colour[2];
    
    _rect._object._scale[0]    = _initial_scale[0];
    _rect._object._scale[1]    = _initial_scale[1];
    
    _rect._object._rotation[0]    = _initial_rotation[0];
    _rect._object._rotation[1]    = _initial_rotation[1];
    _rect._object._rotation[2]    = _initial_rotation[2];
    
    _rect._initialized = 1;
    printf("[INFO] Rectangle '%s' had been created. \n", _rect._name);
    return _rect;
}

void Object(_render_sprite)(SPRITE *_sprite, Texture *_texture, Shader *_shader) {
    Molson(_use)(_shader);
    
    mat4 _transform;
    glm_mat4_identity(_transform);
    glm_translate(_transform, (vec3){_sprite->_object._position[0], _sprite->_object._position[1], _sprite->_object._position[2]});
    
    glm_translate(_transform, (vec3){0.5f * _sprite->_object._scale[0], 0.5f *_sprite->_object._scale[1], 0.0f});
    glm_rotate(_transform, _sprite->_object._rotation[0], (vec3){1.0f, 0.0f, 0.0f});
    glm_rotate(_transform, _sprite->_object._rotation[1], (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate(_transform, _sprite->_object._rotation[2], (vec3){0.0f, 0.0f, 1.0f});
    glm_translate(_transform, (vec3){-0.5f * _sprite->_object._scale[0], -0.5f *_sprite->_object._scale[1], 0.0f});
    
    glm_scale(_transform, (vec3){_sprite->_object._scale[0], _sprite->_object._scale[1], 1.0f});
    
    Molson(_set_vector3_f)("_colour", _sprite->_object._colour, false, _shader);
    Molson(_set_matrix4)("_transform", &_transform, false, _shader);
    Molson(_set_bool)("_is_textured", true, _shader);
    
    glActiveTexture(GL_TEXTURE0);
    ResourceManager(_bind_texture)(_texture);
    
    glBindVertexArray(_sprite->_object._vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    
    return;
}

SPRITE Object(_new_sprite)(const char *_name, vec2 _initial_position, vec2 _initial_scale, vec3 _initial_rotation, vec3 _initial_colour) {
    SPRITE _sprite;
    _sprite._name = _name;
    
    // _sprite._texture = *_texture;
    // _sprite._texture.ID = 0;
    // ResourceManager(_init_texture2d)(&_sprite._texture);
    // ResourceManager(_load_texture2d)(_texture_path, _texture_alpha, &_sprite._texture);
    
    float _vertices[] = {
    
	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 
	
	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 0.0f
	
    };
    glGenVertexArrays(1, &_sprite._object._vao);
    glGenBuffers(1, &_sprite._object._vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, _sprite._object._vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(_sprite._object._vao);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    _sprite._object._position[0] = _initial_position[0];
    _sprite._object._position[1] = _initial_position[1];

    _sprite._object._colour[0]   = _initial_colour[0];
    _sprite._object._colour[1]   = _initial_colour[1];
    _sprite._object._colour[2]   = _initial_colour[2];
    
    _sprite._object._scale[0]    = _initial_scale[0];
    _sprite._object._scale[1]    = _initial_scale[1];
    
    _sprite._object._rotation[0]    = _initial_rotation[0];
    _sprite._object._rotation[1]    = _initial_rotation[1];
    _sprite._object._rotation[2]    = _initial_rotation[2];
    
    _sprite._initialized = 1;
    printf("[INFO] Sprite '%s' had been created. \n", _sprite._name);
    return _sprite;
}
