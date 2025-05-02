
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <cglm/call.h>

#include <resource_manager.h>
#include <object.h>
#include <molson.h>
#include <cJSON.h>
#define MOLSON_IMPLEMENTATION
#include <core.h>
#include <data.h>
#include <keys.h>


ENGINE_STATE _current_state;
GLFWwindow *_window;

const char *_TITLE  = "MoL  ̶g̶a̶m̶e̶(physics) engine";
int         _WIDTH  = 800;
int         _HEIGHT = 600;

Shader _shader;

// TODO: perhaps there is a better way to this this.
bool _running = false;

void _opengl_error_callback() {
    GLenum _error = glGetError();
    if (_error != GL_NO_ERROR) {
	    printf("[ERROR] OpenGL Error");
	    return;
    }
}



bool Core(_get_key_state)(unsigned int _key, unsigned int _key_state) {
    int _state = glfwGetKey(_window, _key);
    
    if (_state == _key_state) {
	    return true;
    }
    return false;
}

bool Core(_is_window_running)() {
    return _running;
}

void Core(_set_current_engine_state)(ENGINE_STATE _new_state) {
    _current_state = _new_state;
    return;
}
void Core(_set_window_height)(int _new_height) {
    _HEIGHT = _new_height;
    return;
}
void Core(_set_window_width)(int _new_width) {
    _WIDTH = _new_width;
    return;
}

ENGINE_STATE Core(_get_current_engine_state)() {
    return _current_state;
}
GLFWwindow* Core(_get_window)() {
    return _window;
}
int Core(_get_window_height)() {
    return _HEIGHT;
}
int Core(_get_window_width)() {
    return _WIDTH;
}

static void _window_resized_callback(GLFWwindow *_window, int _w, int _h) {
    glfwGetFramebufferSize(_window, &_w, &_h);
    glViewport(0, 0, _w, _h);
    return;
}

static void _key_callback(GLFWwindow *_window, int _key, int scancode, int _action, int _mods) {
    if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS) {
	    _running = false;
	    return;
    }
    
}
void Core(_init)(PROJECT *_project) {
    if (!glfwInit()) {
	    printf("[FAILED] GLFW library could not be loaded. \n");
	    return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    _window = glfwCreateWindow(_WIDTH, _HEIGHT, _TITLE, NULL, NULL);
    
    if (_window == NULL) {
	    printf("[FAILED] Application window could not be created. \n");
	    return;
    }
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	    printf("[FAILED] Glad header library could not be loaded. \n");
	    return;
    }
    
    glfwSetFramebufferSizeCallback(_window, _window_resized_callback);
    glfwSetKeyCallback(_window, _key_callback);
    glEnable(GL_DEPTH_TEST);
    _running = true;
    
    Molson(_init_shader)("./shaders/object.vert", "./shaders/object.frag", &_shader);
    Molson(_init_shader)("./shaders/object.vert", "./shaders/object.frag", &_shader);
    
    mat4 _projection;
    mat4 _view;
    
    glm_mat4_identity(_projection);
    glm_mat4_identity(_view);
    
    glm_translate(_view, (vec3){0.0f, 0.0f, -0.5f});
    glm_ortho(0.0f, _WIDTH, _HEIGHT, 0.0f, -150.0f, 150.0f, _projection);
    // glm_perspective(45.0f, _WIDTH / _HEIGHT, 0.1f, 100.0f, _projection);
    
    Molson(_set_matrix4)("_projection", &_projection, true, &_shader);
    Molson(_set_matrix4)("_view", &_view, true, &_shader);
    Molson(_set_int)("_object_image", 0, true, &_shader);
    
    ResourceManager(_init_object_tree)();
    
    Core(_set_current_engine_state)(_EDITOR);
    printf("[INFO] Application initialized. \n");
    return;
}

void Core(_destroy)() {
    _running = false;
    
    ResourceManager(_destroy_object_tree)();
    glfwDestroyWindow(_window);
    Molson(_destroy)(&_shader);
    glfwTerminate();
    printf("\n[INFO] Application destroyed. \n");
    return;
}

int Core(_ready)() {
    printf("\n[INFO] Hello, MoL! \n\n");
    return 0;
}
int Core(_loop)() {
    ResourceManager(_render_object_tree)(&_shader);
    if (glfwWindowShouldClose(_window)) {
	    _running = false;
    }

    return 0;
}
