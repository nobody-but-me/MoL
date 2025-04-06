
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

// NOTE: just for tests purposes -- this will be changed in the soon future;
SHAPE *_paddle_1;
SHAPE *_paddle_2;
SHAPE *_ball;

// SPRITE *_jameslee;
// SHAPE *_rectangle;

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
    _paddle_1 = ResourceManager(_get_shape_object)("Paddle1");
    _paddle_2 = ResourceManager(_get_shape_object)("Paddle2");
    _ball = ResourceManager(_get_shape_object)("Ball");
    // _jameslee = ResourceManager(_get_sprite_object)("JamesLee");
    // _rectangle = ResourceManager(_get_shape_object)("Rectangle");
    
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

// TODO: temporary code since, in the future, Lua will be embeeded as scripting language.

bool _is_rectangles_colliding(SHAPE * _rect1, SHAPE * _rect2) {
    if (_rect1->_object._position[0] < _rect2->_object._position[0] + _rect2->_object._scale[0] &&
        _rect1->_object._position[0] + _rect1->_object._scale[0] > _rect2->_object._position[0] && 
	_rect1->_object._position[1] < _rect2->_object._position[1] + _rect2->_object._scale[1] &&
	_rect1->_object._position[1] + _rect1->_object._scale[1] > _rect2->_object._position[1]
    ) {
	return true;
    }
    return false;
}

const float _ball_speed = 1;
vec4 _screen;
vec2 _ball_velocity;

void _ball_movement() {
    if (_is_rectangles_colliding(_ball, _paddle_2)) {
	_ball_velocity[0] = -_ball_velocity[0];
	_ball_velocity[0] *= 1.05;
	_ball_velocity[1] *= 1.05;
    }
    else if (_is_rectangles_colliding(_ball, _paddle_1)) {
	_ball_velocity[0] = -_ball_velocity[0];
	_ball_velocity[0] *=  1.05;
	_ball_velocity[1] *= -1.05;
    }
    
    _ball->_object._position[0] += _ball_velocity[0] * _ball_speed;
    _ball->_object._position[1] += _ball_velocity[1] * _ball_speed;
}

int Core(_ready)() {
    printf("\n[INFO] Hello, MoL! \n\n");
    
    _ball_velocity[0] = 3;
    _ball_velocity[1] = -0.6;
    
    _screen[0] = 0.0f;
    _screen[1] = 0.0f;
    _screen[2] = _WIDTH;
    _screen[3] = _HEIGHT;
    return 0;
}
int Core(_loop)() {
    
    // _sprite1._object._rotation = (float)glfwGetTime() * 
    
    ResourceManager(_render_object_tree)(&_shader);
    if (glfwWindowShouldClose(_window)) {
	_running = false;
    }
    
    // _rectangle->_object._rotation[0] = (float)glfwGetTime();
    // _rectangle->_object._rotation[1] = (float)glfwGetTime();
    
    // if (Core(_get_key_state)(GLFW_KEY_D, GLFW_PRESS)) {
    // 	_jameslee->_object._position[0] += 10;
    // }
    // if (Core(_get_key_state)(_MOL_KEY_A, GLFW_PRESS)) {
    // 	_jameslee->_object._position[0] -= 10;
    // }
    if (Core(_get_key_state)(GLFW_KEY_W, GLFW_PRESS)) {
	_paddle_1->_object._position[1] -= 5;
    }
    if (Core(_get_key_state)(GLFW_KEY_S, GLFW_PRESS)) {
	_paddle_1->_object._position[1] += 5;
    }
    _paddle_2->_object._position[1] = _ball->_object._position[1] - (_paddle_2->_object._scale[1] / 2 - _ball->_object._scale[1] / 2);
    
   _ball_movement();
    return 0;
}
