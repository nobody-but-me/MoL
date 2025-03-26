
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


TREE *ResourceManager(_get_current_object_tree)() {
    return &_object_tree;
}

SPRITE *ResourceManager(_get_sprite_object)(const char *_object_name) {
    SPRITE *_output_sprite;
    for (int i = 0; i < MAX_TREE_LENGTH; i++) {
	if (_object_tree._sprite_tree[i]._initialized == 0) {
	    break;
	}
	const char *_name = _object_tree._sprite_tree[i]._name;
	if (_name == _object_name) {
	    _output_sprite = &_object_tree._sprite_tree[i];
	    break;
	}
    }
    return _output_sprite;
}

void ResourceManager(_destroy_object_tree)() {
    for (int i = 0; i < MAX_TREE_LENGTH; i++) {
	if (_object_tree._sprite_tree[i]._initialized == 1) {
	    Object(_kill)(&_object_tree._sprite_tree[i]._object);
	}
    }
    return;
}

void ResourceManager(_render_object_tree)(Shader *_shader) {
    for (int i = 0; i < MAX_TREE_LENGTH; i++) {
	if (_object_tree._sprite_tree[i]._initialized == 1) {
	    // _object_tree._sprite_tree[i]._object._rotation = (float)glfwGetTime();
	    Object(_render_sprite)(&_object_tree._sprite_tree[i], &_object_tree._texture_tree[i], _shader);
	}
	continue;
    }
}

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
		cJSON *_name		= cJSON_GetObjectItemCaseSensitive(_object, "_name");
		cJSON *_x		= cJSON_GetObjectItemCaseSensitive(_object, "x");
		cJSON *_y		= cJSON_GetObjectItemCaseSensitive(_object, "y");
		cJSON *_height		= cJSON_GetObjectItemCaseSensitive(_object, "_height");
		cJSON *_width		= cJSON_GetObjectItemCaseSensitive(_object, "_width");
		
		cJSON *_rot_x		= cJSON_GetObjectItemCaseSensitive(_object, "_rot_x");
		cJSON *_rot_y		= cJSON_GetObjectItemCaseSensitive(_object, "_rot_y");
		cJSON *_rot_z		= cJSON_GetObjectItemCaseSensitive(_object, "_rot_z");

		cJSON *_r		= cJSON_GetObjectItemCaseSensitive(_object, "r");
		cJSON *_g		= cJSON_GetObjectItemCaseSensitive(_object, "g");
		cJSON *_b		= cJSON_GetObjectItemCaseSensitive(_object, "b");
		
		cJSON *_texture_path	= cJSON_GetObjectItemCaseSensitive(_object, "_texture");
		cJSON *_texture_alpha	= cJSON_GetObjectItemCaseSensitive(_object, "_alpha");
		
		bool _alpha;
		if (cJSON_IsFalse(_texture_alpha) == true) {
		    _alpha = false;
		} else {
		    _alpha = true;
		}
		Texture _new_texture;
		SPRITE _new_sprite;

		_new_texture = Molson(_load_texture)(_texture_path->valuestring, _alpha);
		_new_sprite = Object(_new_sprite)(_name->valuestring, (vec2){_x->valuedouble, _y->valuedouble}, (vec2){_width->valuedouble, _height->valuedouble}, (vec3){_rot_x->valuedouble, _rot_y->valuedouble, _rot_z->valuedouble}, (vec3){_r->valuedouble, _g->valuedouble, _b->valuedouble});
		
		for (int i = 0; i < MAX_TREE_LENGTH; i++) {
		    if (_object_tree._sprite_tree[i]._initialized == 0) {
			_object_tree._texture_tree[i] = _new_texture;
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

void ResourceManager(_init)(cJSON *_configuration_json, PROJECT *_game_project) {
    cJSON *_project_version = cJSON_GetObjectItemCaseSensitive(_configuration_json, "_project_version");
    cJSON *_project_name = cJSON_GetObjectItemCaseSensitive(_configuration_json, "_project_name");
    
    if (cJSON_IsString(_project_name) == false && (_project_name->valuestring == NULL)) {
	fprintf(stderr, "[INFO] Configuration file :: project name had not been defined or found. \n");
	return;
    }
    if (cJSON_IsString(_project_version) == false && (_project_version->valuestring == NULL)) {
	fprintf(stderr, "[INFO] Configuration file :: project version had not been defined or found. \n");
    }
    
    _game_project->_project_version = _project_version->valuestring;
    _game_project->_project_path = TEST_PROJECT_PATH;
    _game_project->_project_name = _project_name->valuestring;
    _game_project->_json = _configuration_json;
    
    ResourceManager(_set_current_project)(_game_project);
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
}
void ResourceManager(_add_new_scene)(const char *_name) {
    return;
}

