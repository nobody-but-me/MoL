
#include <stdlib.h>
#include <stdio.h>

#include <object.h>
#include <core.h>
#include <data.h>

#define MOLANG_IMPLEMENTATION
#include <molang.h>


void _error_callback(int _err_num, const char *_err_description) {
    printf("[FAILED] GLFW %d ERROR: %s. \n", _err_num, _err_description);
    glfwTerminate();
    return;
}

int main(int argc, char **argv) {
    glfwSetErrorCallback(_error_callback);
    Application(_init)();
    
    const char *_test_file = Molson(_file_to_string)("./assets/test");
    MAP _test_map = Molang(_lexer)(_test_file);
    float *_idk = _map_namespace_get("a", "Float", &_test_map);
    printf("[INFO] IDK value: %.1ff. \n", *_idk);
    
    Application(_ready)();
    while (!glfwWindowShouldClose(Application(_get_window)())) {
	
	glClearColor(0.024f, 0.024f, 0.024f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Application(_loop)();
	
	glfwSwapBuffers(Application(_get_window)());
	glfwPollEvents();
    }
    Application(_destroy)();
    return 0;
}


