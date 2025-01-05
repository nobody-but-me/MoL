
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <object.h>
#define MOLSON_IMPLEMENTATION
#include <molson.h>
#include <core.h>

#define TITLE "MoL  ̶g̶a̶m̶e̶(physics) engine"
#define HEIGHT 600
#define WIDTH 800

enum Application(_engine_state) Application(_current_state);
GLFWwindow *Application(_window);
int Application(_height);
int Application(_width);

void Application(_set_current_engine_state)(enum Application(_engine_state) _new_state) {
  Application(_current_state) = _new_state;
  return;
}
void Application(_set_window_height)(int _new_height) {
  Application(_height) = _new_height;
  return;
}
void Application(_set_window_width)(int _new_width) {
  Application(_width) = _new_width;
  return;
}

enum Application(_engine_state) Application(_get_current_engine_state)() {
  return Application(_current_state);
}
GLFWwindow* Application(_get_window)() {
  return Application(_window);
}
int Application(_get_window_height)() {
  return Application(_height);
}
int Application(_get_window_width)() {
  return Application(_width);
}

static void _window_resized_callback(GLFWwindow *_window, int _width, int _height) {
  glfwGetFramebufferSize(_window, &_width, &_height);
  glViewport(0, 0, _width, _height);
  return;
}
void Application(_init)() {
  if (!glfwInit()) {
    printf("[FAILED] GLFW library could not be loaded. \n");
    return;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  Application(_window) = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
  
  if (Application(_window) == NULL) {
    printf("[FAILED] Application window could not be created. \n");
    return;
  }
  glfwMakeContextCurrent(Application(_window));
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("[FAILED] Glad header library could not be loaded. \n");
    return;
  }
  glfwSetFramebufferSizeCallback(Application(_window), _window_resized_callback);
  glEnable(GL_DEPTH_TEST);
  
  Application(_set_current_engine_state)(Application(_EDITOR));
  printf("[INFO] Application initialized. \n");
  return;
}

Triangle _triangle;
Shader _shader;
void Application(_destroy)() {
  glfwDestroyWindow(Application(_window));
  Molson(_destroy)(&_shader);
  glfwTerminate();
  printf("\n[INFO] Application destroyed. \n");
  return;
}

int Application(_ready)() {
  printf("[INFO] Hello, MoL! \n");
  _shader = Molson(_init)("./shaders/object.vert", "./shaders/object.frag");
  _triangle = Object(_new_triangle)();
  return 0;
}

int Application(_loop)() {
  Object(_render_triangle)(&_triangle, &_shader);
  return 0;
}
