
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <cglm/call.h>

#include <resource_manager.h>
#include <object.h>
#include <molson.h>
#include <data.h>


void Object(_render_triangle)(TRIANGLE *_triangle, Shader *_shader) {
    glm_mat4_identity(_triangle->_object._transform);
    glm_translate(_triangle->_object._transform, (vec3){1.0f, 1.0f, 1.0f});
    glm_rotate(_triangle->_object._transform, (float)glfwGetTime(), (vec3){ 1.0f, 1.0f, 0.0f });
    
    Molson(_use)(_shader);
    unsigned int _transform_loc = glGetUniformLocation(_shader->ID, "_transform");
    glUniformMatrix4fv(_transform_loc, 1, GL_FALSE, (float *)_triangle->_object._transform);
    
    glBindVertexArray(_triangle->_object._vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    return;
}

void Object(_kill)(Object *_self) {
    glDeleteVertexArrays(1, &_self->_vao);
    glDeleteBuffers(1, &_self->_vbo);
    glDeleteBuffers(1, &_self->_ebo);
    
    printf("[INFO] Object had been killed successfully. \n");
}

TRIANGLE Object(_new_triangle)() {
    TRIANGLE _triangle;
    _triangle._name = "triangle name just to initialize this shit";
    
    float _vertices[] = {
	-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };
    glGenVertexArrays(1, &_triangle._object._vao);
    glGenBuffers(1, &_triangle._object._vbo);
    
    glBindVertexArray(_triangle._object._vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, _triangle._object._vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
	printf("[INFO] OpenGL Error");
    }
    
    return _triangle;
}

void Object(_render_sprite)(SPRITE *_sprite, Texture *_texture, Shader *_shader) {
    Molson(_use)(_shader);
    
    mat4 _transform;
    glm_mat4_identity(_transform);
    glm_translate(_transform, (vec3){_sprite->_object._position[0], _sprite->_object._position[1], 0.0f});
    
    glm_translate(_transform, (vec3){0.5f * _sprite->_object._scale[0], 0.5f *_sprite->_object._scale[1], 0.0f});
    glm_rotate(_transform, _sprite->_object._rotation, (vec3){0.0f, 0.0f, 1.0f});
    glm_translate(_transform, (vec3){-0.5f * _sprite->_object._scale[0], -0.5f *_sprite->_object._scale[1], 0.0f});
    
    glm_scale(_transform, (vec3){_sprite->_object._scale[0], _sprite->_object._scale[1], 1.0f});
    
    Molson(_set_vector3_f)("_colour", _sprite->_object._colour, false, _shader);
    Molson(_set_matrix4)("_transform", &_transform, false, _shader);
    
    glActiveTexture(GL_TEXTURE0);
    ResourceManager(_bind_texture)(_texture);
    
    glBindVertexArray(_sprite->_object._vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    
    return;
}

SPRITE Object(_new_sprite)(vec2 _initial_position, vec2 _initial_scale, float _initial_rotation, vec3 _initial_colour) {
    SPRITE _sprite;
    _sprite._name = "a name to initialize this shit";
    
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
    
    _sprite._object._rotation    = _initial_rotation;
    
    _sprite._initialized = 1;
    return _sprite;
}
