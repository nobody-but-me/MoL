
#ifndef MOLSON_H
#define MOLSON_H
#define Molson(x) molson##x

#include <stdbool.h>

typedef struct {
  unsigned int _fragment_shader;
  unsigned int _vertex_shader;
  unsigned int ID;
} Shader;

Shader Molson(_init)(const char *_vertex_path, const char *_fragment_path);
void Molson(_set_float)(const char *_name, float _value);
void Molson(_set_bool)(const char *_name, bool _value);
void Molson(_set_int)(const char *_name, bool _value);
void Molson(_destroy)(Shader *_shader);
void Molson(_use)(Shader *_shader);

#endif//MOLSON_H
#ifdef MOLSON_IMPLEMENTATION

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "./glad.h"


Shader Molson(_init)(const char *_vertex_path, const char *_fragment_path) {

  long _buffer_length = 0;
  FILE *_fragment_code;
  FILE *_vertex_code;
  Shader _shader;

  char *_fragment_buffer;
  char *_vertex_buffer;

  _fragment_code = fopen(_fragment_path, "r");
  if (_fragment_code == NULL) {
    printf("[FAILED] Fragment shader file could not be loaded. \n");
    fclose(_fragment_code);
    _shader.ID = -1;
    return _shader;
  }
  if (fseek(_fragment_code, 0, SEEK_END) < 0) goto BLANK;
  
  _buffer_length = ftell(_fragment_code);
  _fragment_buffer = malloc(_buffer_length + 1);
  if (_fragment_buffer == NULL) {
    printf("[FAILED] Fragment shader variable could not be allocated. \n");
    fclose(_fragment_code);
    _shader.ID = -1;
    return _shader;
  }
  
  if (fseek(_fragment_code, 0, SEEK_SET) < 0) goto BLANK;
  fread(_fragment_buffer, 1, _buffer_length, _fragment_code);
  if (ferror(_fragment_code)) {
    printf("[FAILED] Fragment shader file could not be read. \n");
    fclose(_fragment_code);
    _shader.ID = -1;
    return _shader;
  }
  _fragment_buffer[_buffer_length] = '\0';

  
  _vertex_code = fopen(_vertex_path, "r");
  if (_vertex_code == NULL) {
    printf("[FAILED] Vertex shader file could not be loaded. \n");
    fclose(_vertex_code);
    _shader.ID = -1;
    return _shader;
  }
  if (fseek(_vertex_code, 0, SEEK_END) < 0) goto BLANK;
  
  _buffer_length = ftell(_vertex_code);
  _vertex_buffer = malloc(_buffer_length + 1);
  if (_vertex_buffer == NULL) {
    printf("[FAILED] Vertex shader variable could not be allocated. \n");
    fclose(_vertex_code);
    _shader.ID = -1;
    return _shader;
  }
  
  if (fseek(_vertex_code, 0, SEEK_SET < 0)) goto BLANK;
  fread(_vertex_buffer, 1, _buffer_length, _vertex_code);
  if (ferror(_vertex_code)) {
    printf("[FAILED] Fragment shader file could not be read. \n");
    fclose(_vertex_code);
    _shader.ID = -1;
    return _shader;
  }
  _vertex_buffer[_buffer_length] = '\0';
  
  if /*yet*/(_fragment_code) {
    fclose(_fragment_code);
  }
  if /*yet*/(_vertex_code) {
    fclose(_vertex_code);
  }
  
  /* _fragment_code = fopen(_fragment_path, "rb"); */
  /* if (_fragment_code == NULL) { */
  /*   printf("[FAILED] Fragment shader could not be loaded. \n"); */
  /*   _shader.ID = -1; */
  /*   return _shader; */
  /* } */
  /* fseek(_fragment_code, 0, SEEK_END); */
  /* _buffer_length = ftell(_fragment_code) + 1; */
  /* fclose(_fragment_code); */
  /* _fragment_code = fopen(_fragment_path, "r"); */
  /* _fragment_buffer = memset(malloc(_buffer_length), '\0', _buffer_length); */
  /* fread(_fragment_buffer, 1, _buffer_length - 1, _fragment_code); */
  /* fclose(_fragment_code);  */
  
  /* _vertex_code = fopen(_vertex_path, "rb"); */
  /* if (_vertex_code == NULL) { */
  /*   printf("[FAILED] Fragment shader could not be loaded. \n"); */
  /*   _shader.ID = -1; */
  /*   return _shader; */
  /* } */
  /* fseek(_vertex_code, 0, SEEK_END); */
  /* _buffer_length = ftell(_vertex_code) + 1; */
  /* fclose(_vertex_code); */
  /* _vertex_code = fopen(_fragment_path, "r"); */
  /* _vertex_buffer = memset(malloc(_buffer_length), '\0', _buffer_length); */
  /* fread(_vertex_buffer, 1, _buffer_length - 1, _vertex_code); */
  /* fclose(_vertex_code); */

  /* printf("[INFO] Fragment Buffer: \n\n%s \n\n", _fragment_buffer); */
  /* printf("[INFO] Vertex Buffer: \n\n%s \n\n", _vertex_buffer); */
  
  char _info_log[512];
  int _success;
  
  _shader._vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(_shader._vertex_shader, 1, (GLchar const * const *)&_vertex_buffer, NULL);
  glCompileShader(_shader._vertex_shader);
  glGetShaderiv(_shader._vertex_shader, GL_COMPILE_STATUS, &_success);
  if (!_success) {
    glGetShaderInfoLog(_shader._vertex_shader, 512, NULL, _info_log);
    printf("[FAILED] Vertex shader compilation failed. \n");
    printf("[INFO_LOG] %s. \n", _info_log);
    return _shader;
  }
  printf("[INFO] Vertex shader compiled successfully. \n");
  
  _shader._fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(_shader._fragment_shader, 1, (GLchar const * const *)&_fragment_buffer, NULL);
  glCompileShader(_shader._fragment_shader);
  glGetShaderiv(_shader._fragment_shader, GL_COMPILE_STATUS, &_success);
  if (!_success) {
    glGetShaderInfoLog(_shader._fragment_shader, 512, NULL, _info_log);
    printf("[FAILED] Fragment shader compilation failed. \n");
    printf("[INFO_LOG] %s. \n", _info_log);
    return _shader;
  }
  printf("[INFO] Fragment shader compiled successfully. \n");
  
  _shader.ID = glCreateProgram();
  glAttachShader(_shader.ID, _shader._fragment_shader);
  glAttachShader(_shader.ID, _shader._vertex_shader);
  glLinkProgram(_shader.ID);
  glGetProgramiv(_shader.ID, GL_LINK_STATUS, &_success);
  if (!_success) {
    glGetProgramInfoLog(_shader.ID, 512, NULL, _info_log);
    printf("[FAILED] Shader program linking failed. \n");
    printf("[INFO_LOG] %s. \n", _info_log);
    return _shader;
  }
  printf("[INFO] Shader program had been linked successfully. \n");
  return _shader;
  
 BLANK:
  printf("[INFO] Shader file is blank. \n");
  if (_fragment_code) {
    fclose(_fragment_code);
  }
  else if (_vertex_code) {
    fclose(_vertex_code);
  }
  _shader.ID = -1;
  return _shader;
}

void Molson(_destroy)(Shader *_shader) {
  glDeleteShader(_shader->_fragment_shader);
  glDeleteShader(_shader->_vertex_shader);
  glDeleteProgram(_shader->ID);
  printf("[INFO] Shaders deleted successfully. \n");
  return;
}

void Molson(_use)(Shader *_shader) {
  glUseProgram(_shader->ID);
  return;
}

#endif

