
#include <resource_manager.h>
#define MOLSON_IMPLEMENTATION
#include <molson.h>
#include <object.h>
#include <data.h>

#include <stdio.h>

#include <cJSON.h>
#include <glad.h>


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

void ResourceManager(_add_new_scene)(const char *_name) {
    return;
}

void ResourceManager(_add_new_sprite)(Sprite *_sprite) {
    
    return;
}

void ResourceManager(_init)() {
    return;
}

