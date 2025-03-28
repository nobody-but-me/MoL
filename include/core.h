
#ifndef CORE_H
#define CORE_H

#include <stdbool.h>

#include <glad.h>
#include <GLFW/glfw3.h>

#include "./cJSON.h"

#define Core(x) app##x

typedef enum _engine_state {
    _SETTINGS,
    _IN_GAME,
    _EDITOR,
} ENGINE_STATE;

void _opengl_error_callback();

bool Core(_get_key_state)(unsigned int _key, unsigned int _key_state);

bool Core(_is_window_running)();

void Core(_set_current_engine_state)(ENGINE_STATE _new_state);
void Core(_set_window_height)(int _new_height);
void Core(_set_window_width)(int _new_width);

ENGINE_STATE Core(_get_current_engine_state)();
int          Core(_get_window_height)();
int          Core(_get_window_width)();
GLFWwindow*  Core(_get_window)();

void Core(_destroy)();
void Core(_init)(PROJECT *_project);

void Core(_process_input)();
int  Core(_ready)();
int  Core(_loop)();

#endif//CORE_H
