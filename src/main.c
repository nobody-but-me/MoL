
#include <stdlib.h>
#include <stdio.h>

#include <object.h>
#include <core.h>


void _error_callback(int _err_num, const char *_err_description) {
  printf("[FAILED] GLFW %d ERROR: %s. \n", _err_num, _err_description);
  glfwTerminate();
  return;
}
int main(int argc, char **argv) {
  glfwSetErrorCallback(_error_callback);
  Application(_init)();
  
  /* Shader _shader = Molson(_init)("./shaders/object.vert", "./shaders/object.frag"); */
  /* Triangle _triangle = Object(_new_triangle)(); */
  
  Application(_ready)();
  while (!glfwWindowShouldClose(Application(_get_window)())) {
    
    glClearColor(0.024f, 0.024f, 0.024f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Object(_render_triangle)(&_triangle, &_shader); */
    Application(_loop)();
    
    glfwSwapBuffers(Application(_get_window)());
    glfwPollEvents();
  }
  /* Molson(_destroy)(&_shader); */
  /* Object(_kill)(_kill)(&_triangle._object); */
  Application(_destroy)();
  return 0;
}
