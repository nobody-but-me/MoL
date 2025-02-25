
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <cglm/call.h>

#include <resource_manager.h>
#include <object.h>
#include <molson.h>
#define MOLSON_IMPLEMENTATION
#include <core.h>
#include <data.h>

ENGINE_STATE _current_state;
GLFWwindow *_window;

int         _WIDTH  = 800;
int         _HEIGHT = 600;
const char *_TITLE  = "MoL  ̶g̶a̶m̶e̶(physics) engine";

// TODO: make these variables non-global;
Texture2D _texture;
SPRITE _sprite;
Shader _shader;

void _opengl_error_callback() {
    GLenum _error = glGetError();
    if (_error != GL_NO_ERROR) {
	printf("[ERROR] OpenGL Error");
	return;
    }
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
void Core(_init)() {
    if (!glfwInit()) {
	printf("[FAILED] GLFW library could not be loaded. \n");
	return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
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
    glEnable(GL_DEPTH_TEST);

    
    Molson(_init_shader)("./shaders/object.vert", "./shaders/object.frag", &_shader);
    
    mat4 _projection;
    glm_mat4_identity(_projection);
    glm_ortho(0.0f, _WIDTH, _HEIGHT, 0.0f, -1.0f, 1.0f, _projection);
    /* glm_perspective(0.0f, WIDTH / HEIGHT, 0.1f, 100.0f, _projection); */
    
    Molson(_set_matrix4)("_projection", &_projection, true, &_shader);
    Molson(_set_int)("_object_image", 0, true, &_shader);

    // _sprite = Object(_new_sprite)();
    // ResourceManager(_init_texture2d)(&_texture);
    // ResourceManager(_load_texture2d)("./assets/miranda69.png", true, &_texture);
    
    
    Core(_set_current_engine_state)(_EDITOR);
    printf("[INFO] Application initialized. \n");
    return;
}

void Core(_destroy)() {
    Object(_kill)(&_sprite._object);
    
    glfwDestroyWindow(_window);
    Molson(_destroy)(&_shader);
    glfwTerminate();
    printf("\n[INFO] Application destroyed. \n");
    return;
}

int Core(_ready)() {
    printf("[INFO] Hello, MoL! \n");
    return 0;
}

int Core(_loop)() {
    /* void Object(_render_sprite)(Texture2D *_texture, vec2 _position, vec2 _scale, float _rotation, vec3 _colour, Sprite *_sprite, Shader *_shader); */
    
    // Object(_render_sprite)(&_texture, (vec2){0.0f, 125.0f}, (vec2){1000.0f, 350.0f}, (float)glfwGetTime(), (vec3){1.0f, 1.0f, 1.0f}, &_sprite, &_shader);
    return 0;
}
