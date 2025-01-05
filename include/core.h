
#ifndef CORE_H
#define CORE_H

#include <glad.h>
#include <GLFW/glfw3.h>

#define Application(x) app##x

enum Application(_engine_state) {
    Application(_EDITOR),
    Application(_SETTINGS),
    Application(_IN_GAME),
};

void Application(_set_current_engine_state)(enum Application(_engine_state) _new_state);
void Application(_set_window_height)(int _new_height);
void Application(_set_window_width)(int _new_width);

enum Application(_engine_state) Application(_get_current_engine_state)();
GLFWwindow* Application(_get_window)();
int Application(_get_window_height)();
int Application(_get_window_width)();

void Application(_destroy)();
void Application(_init)();

void Application(_process_input)();
int Application(_ready)();
int Application(_loop)();
		       
#endif//CORE_H
