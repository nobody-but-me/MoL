
#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <glad.h>
#include <GLFW/glfw3.h>

#define Application(x) app##x

typedef struct {
  
  GLFWwindow *_window;
  int _height;
  int _width;
  
  bool _running;
  
  GLFWwindow* (*_get_window)();
  int (*_get_window_height)();
  int (*_get_window_width)();
  
} App;

void Application(_destroy)(GLFWwindow *_window);
App Application(_init)();
		       
		       
#endif//CORE_H
