
#include <stdlib.h>
#include <stdio.h>

#include <object.h>
#include <core.h>
#include <data.h>

#include <cJSON.h>

#define TEST_PROJECT_PATH "../mol-test-game/"


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
    
    const char *_config_file = Molson(_file_to_string)("../mol-test-game/config.json");
    if (_config_file == NULL) {
	fprintf(stderr, "[INFO] Config file could not be read or found. \n");
	return -1;
    }
    cJSON *_config_json = cJSON_Parse(_config_file);
    if (_check_json(_config_json) == -1) {
	return -1;
    }
    // printf("[INFO] _test_json: %s. \n", cJSON_Print(_config_json));
    cJSON *_project_version = cJSON_GetObjectItemCaseSensitive(_config_json, "_project_version");
    cJSON *_project_name = cJSON_GetObjectItemCaseSensitive(_config_json, "_project_name");
    
    if (cJSON_IsString(_project_name) == false && (_project_name->valuestring == NULL)) {
	fprintf(stderr, "[INFO] Config file :: project name was not defined or found. \n");
	return -1;
    }
    if (cJSON_IsString(_project_version) == false && (_project_version->valuestring == NULL)) {
	fprintf(stderr, "[INFO] Config file :: project version was not defined or found. \n");
	return -1;
    }
    Project _game_project = {
	._project_version = _project_version->valuestring,
	._project_path = TEST_PROJECT_PATH,
	._project_name = _project_name->valuestring,
	._json = _config_json
    };
    Application(_set_current_project)(&_game_project);
    
    Application(_init)();
    Application(_ready)();
    while (!glfwWindowShouldClose(Application(_get_window)())) {
	
	glClearColor(0.024f, 0.024f, 0.024f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Application(_loop)();
	
	glfwSwapBuffers(Application(_get_window)());
	glfwPollEvents();
    }
    cJSON_Delete(_config_json);
    Application(_destroy)();
    return 0;
}


