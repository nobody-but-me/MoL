
#ifndef CORE_H
#define CORE_H

#include <glad.h>
#include <GLFW/glfw3.h>

#define Application(x) app##x

typedef enum _engine_state {
    _SETTINGS,
    _IN_GAME,
    _EDITOR,
} ENGINE_STATE;

void _opengl_error_callback();

void Application(_set_current_engine_state)(ENGINE_STATE _new_state);
void Application(_set_window_height)(int _new_height);
void Application(_set_window_width)(int _new_width);

ENGINE_STATE Application(_get_current_engine_state)();
GLFWwindow* Application(_get_window)();
int Application(_get_window_height)();
int Application(_get_window_width)();

void Application(_destroy)();
void Application(_init)();

void Application(_process_input)();
int Application(_ready)();
int Application(_loop)();

#endif//CORE_H
