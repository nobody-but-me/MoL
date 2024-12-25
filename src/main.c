
#include <stdlib.h>
#include <stdio.h>

#include <core.h>

int main(int argc, char **argv) {
  App Engine = Application(_init)();
  
  printf("[MOL] Hello, MoL! \n");
  while (!glfwWindowShouldClose(Engine._window)) {
    
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glfwSwapBuffers(Engine._window);
    glfwPollEvents();
  }
  Application(_destroy)(Engine._window);
  return 0;
}
