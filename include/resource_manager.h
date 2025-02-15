
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#define ResourceManager(x) resource_manager##x
#define GAME_TEST_CONFIG_PATH "../mol-test-game/config.json"

#include <object.h>
#include <molson.h>
#include <data.h>

void ResourceManager(_generate_texture2d)(unsigned int _width, unsigned int _height, unsigned char *_data, Texture2D *_texture);
void ResourceManager(_load_texture2d)(const char *_file, bool _alpha, Texture2D *_texture);
void ResourceManager(_init_texture2d)(Texture2D *_texture);
void ResourceManager(_bind_texture2d)(Texture2D *_texture);

void ResourceManager(_add_new_scene)(const char *_name);
void ResourceManager(_add_new_sprite)(Sprite *_sprite);
void ResourceManager(_init)();

#endif//RESOURCE_MANAGER_H

