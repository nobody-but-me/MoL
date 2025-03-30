
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#define ResourceManager(x) resource_manager##x
#define GAME_TEST_CONFIG_PATH "../mol-test-game/config.json"

#include <object.h>
#include <molson.h>
#include <data.h>

#include "./cJSON.h"
#include "./map.h"

#define TEST_PROJECT_PATH "./examples/mol-test-game/"
#define PONG_EXAMPLE      "./examples/pong-example/"

typedef struct _project {
    const char *_project_version;
    const char *_project_path;
    const char *_project_name;
    
    cJSON *_json;
} PROJECT;

#define MAX_TREE_LENGTH 100
typedef struct {
    Texture _texture_tree[MAX_TREE_LENGTH];
    SPRITE  _sprite_tree [MAX_TREE_LENGTH];
    SHAPE   _shape_tree  [MAX_TREE_LENGTH];
} TREE;

SPRITE *ResourceManager(_get_sprite_object)(const char *_object_name);
SHAPE *ResourceManager(_get_shape_object)(const char *_object_name);
TREE *ResourceManager(_get_current_object_tree)();

void ResourceManager(_render_object_tree)(Shader *_shader);
void ResourceManager(_destroy_object_tree)();
void ResourceManager(_init_object_tree)();

void ResourceManager(_generate_texture)(unsigned int _width, unsigned int _height, unsigned char *_data, Texture *_texture);
void ResourceManager(_init_texture)(Texture *_texture);
void ResourceManager(_bind_texture)(Texture *_texture);

int      ResourceManager(_set_current_project)(PROJECT *_new_project);
PROJECT *ResourceManager(_get_current_project)();

void ResourceManager(_init)(cJSON *_configuration_json, PROJECT *_game_project);

void ResourceManager(_change_current_scene)(const char *_new_current_scene);
void ResourceManager(_add_new_scene)(const char *_name);

// SPRITE ResourceManager(_add_sprite)(SPRITE *_sprite);
// void ResourceManager(_kill_object)(Object *_object);

#endif//RESOURCE_MANAGER_H

