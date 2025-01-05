
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <object.h>
#include <molson.h>


void Object(_render_triangle)(Triangle *_triangle, Shader *_shader) {
  Molson(_use)(_shader);
  /* glUseProgram(_shader->ID); */
  glBindVertexArray(_triangle->_object._vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  return;
}

void Object(_kill)(Object *_self) {
  glDeleteVertexArrays(1, &_self->_vao);
  glDeleteBuffers(1, &_self->_vbo);
  glDeleteBuffers(1, &_self->_ebo);
}

Triangle Object(_new_triangle)() {
  Triangle _triangle;
  _triangle._name = "triangle name just to initialize this shit";

  float _vertices[] = {
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // left
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // right
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
  };
  glGenVertexArrays(1, &_triangle._object._vao);
  glGenBuffers(1, &_triangle._object._vbo);

  glBindVertexArray(_triangle._object._vao);

  glBindBuffer(GL_ARRAY_BUFFER, _triangle._object._vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    /* std::cerr << "OpenGL Error: " << error << std::endl; */
    printf("[INFO] OpenGL Error");
  }
  return _triangle;
}



