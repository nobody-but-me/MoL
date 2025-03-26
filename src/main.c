
#include <stdlib.h>
#include <stdio.h>

#include <resource_manager.h>
#include <object.h>
#include <core.h>
#include <data.h>

#include <cJSON.h>

// #define TEST_PROJECT_PATH "./mol-test-game/"


void _error_callback(int _err_num, const char *_err_description) {
    printf("[FAILED] GLFW %d ERROR: %s. \n", _err_num, _err_description);
    glfwTerminate();
    return;
}

static int _check_json(cJSON *_json) {
    if (_json == NULL) {
        const char *_error_ptr = cJSON_GetErrorPtr();
        if (_error_ptr != NULL) {
            fprintf(stderr, "[INFO] Json error before the follow line: %s. \n", _error_ptr);
	    cJSON_Delete(_json);
	    return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    glfwSetErrorCallback(_error_callback);
    
    const char *_config_file = Molson(_file_to_string)(TEST_PROJECT_PATH"config.json");
    if (_config_file == NULL) {
	fprintf(stderr, "[INFO] Config file could not be read or found. \n");
	return -1;
    }
    cJSON *_config_json = cJSON_Parse(_config_file);
    if (_check_json(_config_json) == -1) {
	return -1;
    }
    PROJECT _game_project;
    ResourceManager(_init)(_config_json, &_game_project);
    
    Core(_init)(&_game_project);
    
    Core(_ready)();
    while(Core(_is_window_running)()) {
	cJSON *_current_scene = cJSON_GetObjectItemCaseSensitive(_config_json, "_current_scene");
	if (cJSON_IsString(_current_scene) && _current_scene->valuestring != NULL) {
	    cJSON *_scenes		= cJSON_GetObjectItemCaseSensitive(_config_json, "_scenes");
	    cJSON *_scene		= cJSON_GetObjectItemCaseSensitive(_scenes, _current_scene->valuestring);
	    cJSON *_background_color	= cJSON_GetObjectItemCaseSensitive(_scene, "_background_color");
	    
	    cJSON *_r = cJSON_GetObjectItemCaseSensitive(_background_color, "r");
	    cJSON *_g = cJSON_GetObjectItemCaseSensitive(_background_color, "g");
	    cJSON *_b = cJSON_GetObjectItemCaseSensitive(_background_color, "b");
	    cJSON *_a = cJSON_GetObjectItemCaseSensitive(_background_color, "a");
	    
	    glClearColor(_r->valuedouble, _g->valuedouble, _b->valuedouble, _a->valuedouble);
	    
	} else {
	    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Core(_loop)();
	
	glfwSwapBuffers(Core(_get_window)());
	glfwPollEvents();
    }
    cJSON_Delete(_config_json);
    Core(_destroy)();
    return 0;
}


