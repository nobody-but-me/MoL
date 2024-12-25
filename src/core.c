
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <core.h>

/* const char *TITLE = "MoL  ̶g̶a̶m̶e̶(physics) engine"; */
/* const int HEIGHT  =  640; */
/* const int WIDTH   = 1024; */
#define TITLE "MoL  ̶g̶a̶m̶e̶(physics) engine"
#define HEIGHT 640
#define WIDTH 1024


App Application(_init)() {
  App _application;
  if (!glfwInit()) {
    printf("[FAILED] GLFW library could not be loaded.");
    return _application;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  _application._window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

  if (_application._window == NULL) {
    printf("[FAILED] Application window could not be created.");
    return _application;
  }
  glfwMakeContextCurrent(_application._window);
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("[FAILED] Glad header library could not be loaded");
    return _application;
  }
  /* glfwSetFramebufferSizeCallback(_application._window, _window_resized_callback); */
  /* _application._running = true; */
  glEnable(GL_DEPTH_TEST);
  
  printf("[INFO] Application initialized. \n");
  return _application;
}

void Application(_destroy)(GLFWwindow *_window) {
  glfwDestroyWindow(_window);
  glfwTerminate();
  printf("[INFO] Application destroyed. \n");
  return;
}
