
#include <resource_manager.h>
#define MOLSON_IMPLEMENTATION
#include <molson.h>
#include <object.h>
#include <data.h>

#include <stdio.h>

#include <cJSON.h>
#include <glad.h>
#include <GLFW/glfw3.h>

#include <cglm/call.h>

#define MAP_IMPLEMENTATION
#include <map.h>


TREE _object_tree;

TREE *ResourceManager(_get_current_object_tree)() {
    return &_object_tree;
}
void ResourceManager(_init_object_tree)() {
    // TODO: make this function get the objects inside the json configuration file
    SPRITE _sprite = Object(_new_sprite)();
    _object_tree._sprite_tree[0]  = _sprite;
    _object_tree._texture_tree[0] = "./assets/miranda69.png";
    
    // SPRITE _sprite2 = Object(_new_sprite)();
    // _object_tree._sprite_tree[1]  = _sprite2;
    // _object_tree._texture_tree[1] = "./assets/jameslee?.png";
    
    ResourceManager(_init_objects)();
    return;
}

// TODO: this sucks.
Texture2D _reusable_texture;
void ResourceManager(_render_objects)(Shader *_shader) {
    for (int i = 0; i < MAX_TREE_LENGTH; i++) {
	if (_object_tree._sprite_tree[i]._object._initialized == true) {
	    Object(_render_sprite)(&_reusable_texture, (vec2){5.0f * i, 5.0f * i}, (vec2){250.0f, 250.0f}, (float)glfwGetTime(), (vec3){1.0f, 1.0f, 1.0f}, &_object_tree._sprite_tree[i], _shader);
	}
    }
}
void ResourceManager(_init_objects)() {
    for (int i = 0; i < MAX_TREE_LENGTH; i++) {
	// initializing sprite objects
	if (_object_tree._sprite_tree[i]._object._initialized == true) {
	    _object_tree._sprite_tree[i] = Object(_new_sprite)();
	    ResourceManager(_init_texture2d)(&_reusable_texture);
	    ResourceManager(_load_texture2d)(_object_tree._texture_tree[i], true, &_reusable_texture);
	}
    }
}

void ResourceManager(_generate_texture2d)(unsigned int _width, unsigned int _height, unsigned char *_data, Texture2D *_texture) {
    _texture->_height = _height;
    _texture->_width = _width;

    glBindTexture(GL_TEXTURE_2D, _texture->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, _texture->_internal_format, _width, _height, 0, _texture->_image_format, GL_UNSIGNED_BYTE, _data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _texture->_wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _texture->_wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _texture->_filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _texture->_filter_max);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    printf("[INFO] Texture generated. \n");

    return;
}

void ResourceManager(_init_texture2d)(Texture2D *_texture) {
    _texture->_internal_format = GL_RGB;
    _texture->_filter_min = GL_LINEAR;
    _texture->_filter_max = GL_LINEAR;
    _texture->_image_format = GL_RGB;
    _texture->_wrap_s = GL_REPEAT;
    _texture->_wrap_t = GL_REPEAT;
    _texture->_height = 0;
    _texture->_width = 0;
    
    glGenTextures(1, _texture->ID);
    return;
}

void ResourceManager(_bind_texture2d)(Texture2D *_texture) {
    glBindTexture(GL_TEXTURE_2D, _texture->ID);
    return;
}

void ResourceManager(_load_texture2d)(const char *_file, bool _alpha, Texture2D *_texture) {
    if (_alpha) {
	_texture->_internal_format = GL_RGBA;
	_texture->_image_format = GL_RGBA;
    }
    int _channels;
    int _height;
    int _width;

    unsigned char *_data = stbi_load(_file, &_width, &_height, &_channels, 0);
    ResourceManager(_generate_texture2d)(_width, _height, _data, _texture);
    stbi_image_free(_data);
    
    printf("[INFO] Texture was loaded successfully. \n");
    return;
}

PROJECT *_current_project;
int ResourceManager(_set_current_project)(PROJECT *_new_project) {
    _current_project = _new_project;
    if (_current_project == NULL) {
	return -1;
    }
    return 0;
}
PROJECT *ResourceManager(_get_current_project)() {
    return _current_project;
}

void ResourceManager(_init)(cJSON *_configuration_json) {
    return;
}

void ResourceManager(_change_current_scene)(const char *_new_current_scene) {
    cJSON *_scene = cJSON_CreateString(_new_current_scene);
    if (_scene == NULL) {
	fprintf(stderr, "[FAILED] ResourceManager(_change_current_scene) :: Could not create new scene. \n");
	cJSON_Delete(_current_project->_json);
	return;
    }
    cJSON_AddItemToObject(_current_project->_json, "_current_scene", _scene);
    char *_string = NULL;
    _string = cJSON_Print(_current_project->_json);
    if (_string == NULL) {
	fprintf(stderr, "[FAILED] ResourceManager(_change_current_scene) :: Could not create JSON string. \n");
	cJSON_Delete(_current_project->_json);
	return;
    }
    // printf("[INFO] %s. \n", _string);
}
void ResourceManager(_add_new_scene)(const char *_name) {
    return;
}

// SPRITE ResourceManager(_add_sprite)(SPRITE *_sprite) {
//     return;
// }


