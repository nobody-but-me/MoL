
#ifndef MOLUI_H
#define MOLUI_H

#include <stdbool.h>
#include <GLFW/glfw3.h>

typedef struct BUTTON {
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
    
    int _height;
    int _width;
    int _x;
    int _y;
    
    float _color[3];
    
    bool (*_mouse_over)(GLFWwindow *_window, struct BUTTON *_self);
} BUTTON;

void _render_button(BUTTON *_button, GLFWwindow *_window);
void _create_button(int _x, int _y, int _height, int _width, float _color[3], BUTTON *_button);

#endif//MOLUI_H
#ifdef MOLUI_IMPLEMENTATION

#include <stdbool.h>
#include <stdio.h>

// TODO: found a other way so user will not need these dependencies.
#include <glad.h>
#include <GLFW/glfw3.h>


static bool _button_mouse_over(GLFWwindow *_window, BUTTON *_self) {
    double _mouse_x, _mouse_y;
    int width, height;
    glfwGetCursorPos(_window, &_mouse_x, &_mouse_y);
    glfwGetWindowSize(_window, &width, &height);
    
    printf("[INFO]: mouse_position(%.1f, %.1f);\n", _mouse_x, _mouse_y);
    printf("[INFO]: square_position(%d, %d);\n", _self->_x, _self->_y);
    
    if (_mouse_x < _self->_x + _self->_width  &&
        _mouse_x > _self->_x                  &&
	_mouse_y < _self->_y + _self->_height &&
	_mouse_y > _self->_y
    ) {
	_self->_color[0] = 0.0f;
	_self->_color[1] = 1.0f;
	return true;
    }
    _self->_color[0] = 1.0f;
    _self->_color[1] = 0.0f;
    return false;
}

// TODO: inverted positions :: baked window height;
void _render_button(BUTTON *_button, GLFWwindow *_window) {
    glEnable(GL_SCISSOR_TEST);
    int width, height;
    glfwGetWindowSize(_window, &width, &height);
    glScissor(_button->_x, height -  _button->_y -_button->_height, _button->_width, _button->_height);
    glClearColor(_button->_color[0], _button->_color[1], _button->_color[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    return;
}
void _create_button(int _x, int _y, int _height, int _width, float _color[3], BUTTON *_button) {
    _button->_mouse_over = _button_mouse_over;
    _button->_height = _height;
    _button->_width = _width;
    _button->_x = _x;
    _button->_y = _y;
    
    _button->_color[0] = _color[0];
    _button->_color[1] = _color[1];
    _button->_color[2] = _color[2];
}


#endif//MOLUI_IMPLEMENTATION
