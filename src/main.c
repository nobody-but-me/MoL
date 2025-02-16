
#include <stdlib.h>
#include <stdio.h>

#include <object.h>
#include <core.h>
#include <data.h>

#include <cJSON.h>


void _error_callback(int _err_num, const char *_err_description) {
    printf("[FAILED] GLFW %d ERROR: %s. \n", _err_num, _err_description);
    glfwTerminate();
    return;
}

int main(int argc, char **argv) {
    glfwSetErrorCallback(_error_callback);
    Application(_init)();
    
    const char *_test_file = Molson(_file_to_string)("../mol-test-game/config.json");
    cJSON *_test_json = cJSON_Parse(_test_file);
    if (_test_json == NULL) {
        const char *_error_ptr = cJSON_GetErrorPtr();
	
        if (_error_ptr != NULL) {
            fprintf(stderr, "[INFO] Error before: %s. \n", _error_ptr);
	    cJSON_Delete(_test_json);
	    return -1;
        }
    }
    cJSON *_project_name = cJSON_GetObjectItemCaseSensitive(_test_json, "_project_name");
    if (cJSON_IsString(_project_name) && (_project_name->valuestring != NULL)) {
        printf("[INFO] _project_name: \"%s\". \n", _project_name->valuestring);
    }
    
    Application(_ready)();
    while (!glfwWindowShouldClose(Application(_get_window)())) {
	
	glClearColor(0.024f, 0.024f, 0.024f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Application(_loop)();
	
	glfwSwapBuffers(Application(_get_window)());
	glfwPollEvents();
    }
    cJSON_Delete(_test_json);
    Application(_destroy)();
    return 0;
}


