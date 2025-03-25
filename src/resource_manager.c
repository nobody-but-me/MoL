
#include <resource_manager.h>
#define MOLSON_IMPLEMENTATION
#include <molson.h>
#include <object.h>
#include <data.h>

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <cJSON.h>
#include <cglm/call.h>

#define MAP_IMPLEMENTATION
#include <map.h>


PROJECT *_current_project;
TREE _object_tree;

void ResourceManager(_init_object_tree)() {
    cJSON *_current_scene = cJSON_GetObjectItemCaseSensitive(_current_project->_json, "_current_scene");
    if (_current_scene == NULL) {printf("[FAILED] Current scene variable could not be found inside your game's configuration file. \n"); return;}
    cJSON *_scenes = cJSON_GetObjectItemCaseSensitive(_current_project->_json, "_scenes");
    if (_scenes == NULL) {printf("[FAILED] Scenes array could not be found inside your game's configuration file. \n"); return;}
    cJSON *_scene = cJSON_GetObjectItemCaseSensitive(_scenes, _current_scene->valuestring);
    if (_scene == NULL) {printf("[FAILED] Scene array could not be found inside your game's configuration file. \n"); return;}
    cJSON *_objects = cJSON_GetObjectItemCaseSensitive(_scene, "_objects");
    if (_objects == NULL) {printf("[FAILED] Objects array could not be found inside your game's configuration file. \n"); return;}
    
    const cJSON *_object = NULL;
    cJSON_ArrayForEach(_object, _objects) 
    {
	cJSON *_type = cJSON_GetObjectItemCaseSensitive(_object, "_type");
	if (_type == NULL) return;
	if (cJSON_IsString(_type)) {
	    if (strcmp(_type->valuestring, "SPRITE") == 0) {
		// TODO: hard-coded: rewrite this later.
		cJSON *_x		= cJSON_GetObjectItemCaseSensitive(_object, "x");
		cJSON *_y		= cJSON_GetObjectItemCaseSensitive(_object, "y");
		cJSON *_height		= cJSON_GetObjectItemCaseSensitive(_object, "_height");
		cJSON *_width		= cJSON_GetObjectItemCaseSensitive(_object, "_width");
		cJSON *_rotation	= cJSON_GetObjectItemCaseSensitive(_object, "_rotation");

		cJSON *_r		= cJSON_GetObjectItemCaseSensitive(_object, "r");
		cJSON *_g		= cJSON_GetObjectItemCaseSensitive(_object, "g");
		cJSON *_b		= cJSON_GetObjectItemCaseSensitive(_object, "b");
		
		// cJSON *_texture_path	= cJSON_GetObjectItemCaseSensitive(_object, "_texture");
		// cJSON *_texture_alpha	= cJSON_GetObjectItemCaseSensitive(_object, "_alpha");
		
		// bool _alpha;
		// if (cJSON_IsFalse(_texture_alpha) == true) {
		//     _alpha = false;
		// } else {
		//     _alpha = true;
		// }
		
		SPRITE _new_sprite;
		Texture _texture;
		_new_sprite = Object(_new_sprite)((vec2){_x->valuedouble, _y->valuedouble}, (vec2){_width->valuedouble, _height->valuedouble}, _rotation->valuedouble, (vec3){_r->valuedouble, _g->valuedouble, _b->valuedouble});
		
		size_t _tree_length = sizeof(_object_tree._sprite_tree) / sizeof(_object_tree._sprite_tree[0]);
		for (int i = 0; i < _tree_length; i++) {
		    if (_object_tree._sprite_tree[i]._initialized == 0) {
			_object_tree._sprite_tree[i] = _new_sprite;
			printf("[INFO] Sprite had been initialized succesfully. \n");
			break;
		    }
		    continue;
		}
	    }
	}
    }
    return;
}
TREE *ResourceManager(_get_current_object_tree)() {
    return &_object_tree;
}


void ResourceManager(_generate_texture)(unsigned int _width, unsigned int _height, unsigned char *_data, Texture *_texture) {
    _texture->_height = _height;
    _texture->_width = _width;
    
    glBindTexture(GL_TEXTURE_2D, _texture->_id);
    glTexImage2D(GL_TEXTURE_2D, 0, _texture->_internal_format, _width, _height, 0, _texture->_image_format, GL_UNSIGNED_BYTE, _data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _texture->_wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _texture->_wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _texture->_filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _texture->_filter_max);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
}

void ResourceManager(_init_texture)(Texture *_texture) {
    _texture->_height = 0;
    _texture->_width = 0;
    _texture->_image_format = GL_RGB;
    _texture->_wrap_s = GL_REPEAT;
    _texture->_wrap_t = GL_REPEAT;
    _texture->_filter_min = GL_LINEAR;
    _texture->_filter_max = GL_LINEAR;
    
    glGenTextures(1, &_texture->_id);
    return;
}

void ResourceManager(_bind_texture)(Texture *_texture) {
    glBindTexture(GL_TEXTURE_2D, _texture->_id);
    return;
}



// void ResourceManager(_generate_texture2d)(unsigned int _width, unsigned int _height, unsigned char *_data, Texture2D *_texture) {
//     _texture->_height = _height;
//     _texture->_width = _width;
    
//     // glBindTexture(GL_TEXTURE_2D, _texture->ID);
//     glTexImage2D(GL_TEXTURE_2D, 0, _texture->_internal_format, _width, _height, 0, _texture->_image_format, GL_UNSIGNED_BYTE, _data);
    
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _texture->_wrap_s);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _texture->_wrap_t);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _texture->_filter_min);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _texture->_filter_max);
    
//     glBindTexture(GL_TEXTURE_2D, 0);
//     printf("[INFO] Texture generated. \n");
//     return;
// }

// void ResourceManager(_init_texture2d)(Texture2D *_texture) {
//     _texture->_internal_format	= GL_RGB;
//     _texture->_filter_min	= GL_LINEAR;
//     _texture->_filter_max	= GL_LINEAR;
//     _texture->_image_format	= GL_RGB;
//     _texture->_wrap_s		= GL_REPEAT;
//     _texture->_wrap_t		= GL_REPEAT;
//     _texture->_height		= 0;
//     _texture->_width		= 0;
    
//     glGenTextures(1, _texture->ID);
//     return;
// }

// void ResourceManager(_bind_texture2d)(Texture2D *_texture) {
//     glBindTexture(GL_TEXTURE_2D, _texture->ID);
//     return;
// }

// void ResourceManager(_load_texture2d)(const char *_file, bool _alpha, Texture2D *_texture) {
//     ResourceManager(_init_texture2d)(_texture);
    
//     if (_alpha) {
// 	_texture->_internal_format = GL_RGBA;
// 	_texture->_image_format = GL_RGBA;
//     }
//     int _channels;
//     int _height;
//     int _width;

//     unsigned char *_data = stbi_load(_file, &_width, &_height, &_channels, 0);
//     ResourceManager(_generate_texture2d)(_width, _height, _data, _texture);
//     stbi_image_free(_data);
    
//     printf("[INFO] Texture was loaded successfully. \n");
//     return;
// }

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


