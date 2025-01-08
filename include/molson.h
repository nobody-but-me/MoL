
#ifndef MOLSON_H
#define MOLSON_H
#define Molson(x) molson##x

#include <cglm/call.h>
#include <stdbool.h>

typedef struct {
  unsigned int _fragment_shader;
  unsigned int _vertex_shader;
  unsigned int ID;
} Shader;
void Molson(_init_shader)(const char *_vertex_path, const char *_fragment_path, Shader *_shader);
void Molson(_set_float)(const char *_name, float _value);
void Molson(_set_bool)(const char *_name, bool _value);
void Molson(_destroy)(Shader *_shader);
void Molson(_use)(Shader *_shader);

void Molson(_set_matrix4)(const char *_name, const mat4 *_value, bool _use_shader, Shader *_shader);
void Molson(_set_vector3_f)(const char *_name, vec3 _value, bool _use_shader, Shader *_shader);
void Molson(_set_int)(const char *_name, int _value, bool _use_shader, Shader *_shader);

// --------------------------------------------------

typedef struct {
  unsigned int _internal_format;
  unsigned int _image_format;
  unsigned int _filter_min;
  unsigned int _filter_max;
  unsigned int _wrap_s;
  unsigned int _wrap_t;
  unsigned int _height;
  unsigned int _width;
  unsigned int ID;
} Texture2D;
void Molson(_generate_texture2d)(unsigned int _width, unsigned int _height, unsigned char *_data, Texture2D *_texture);
void Molson(_init_texture2d)(Texture2D *_texture);
void Molson(_bind_texture2d)(Texture2D *_texture);

void Molson(_load_texture2d)(const char *_file, bool _alpha, Texture2D *_texture);


#endif//MOLSON_H
#ifdef MOLSON_IMPLEMENTATION

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <cglm/call.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "./glad.h"


void Molson(_init_shader)(const char *_vertex_path, const char *_fragment_path, Shader *_shader) {

  long _buffer_length = 0;
  FILE *_fragment_code;
  FILE *_vertex_code;

  char *_fragment_buffer;
  char *_vertex_buffer;

  _fragment_code = fopen(_fragment_path, "r");
  if (_fragment_code == NULL) {
    printf("[FAILED] Fragment shader file could not be loaded. \n");
    fclose(_fragment_code);
    _shader->ID = -1;
    return;
  }
  if (fseek(_fragment_code, 0, SEEK_END) < 0) goto BLANK;
  
  _buffer_length = ftell(_fragment_code);
  _fragment_buffer = malloc(_buffer_length + 1);
  if (_fragment_buffer == NULL) {
    printf("[FAILED] Fragment shader variable could not be allocated. \n");
    fclose(_fragment_code);
    _shader->ID = -1;
    return;
  }
  
  if (fseek(_fragment_code, 0, SEEK_SET) < 0) goto BLANK;
  fread(_fragment_buffer, 1, _buffer_length, _fragment_code);
  if (ferror(_fragment_code)) {
    printf("[FAILED] Fragment shader file could not be read. \n");
    fclose(_fragment_code);
    _shader->ID = -1;
    return;
  }
  _fragment_buffer[_buffer_length] = '\0';

  
  _vertex_code = fopen(_vertex_path, "r");
  if (_vertex_code == NULL) {
    printf("[FAILED] Vertex shader file could not be loaded. \n");
    fclose(_vertex_code);
    _shader->ID = -1;
    return;
  }
  if (fseek(_vertex_code, 0, SEEK_END) < 0) goto BLANK;
  
  _buffer_length = ftell(_vertex_code);
  _vertex_buffer = malloc(_buffer_length + 1);
  if (_vertex_buffer == NULL) {
    printf("[FAILED] Vertex shader variable could not be allocated. \n");
    fclose(_vertex_code);
    _shader->ID = -1;
    return;
  }
  
  if (fseek(_vertex_code, 0, SEEK_SET < 0)) goto BLANK;
  fread(_vertex_buffer, 1, _buffer_length, _vertex_code);
  if (ferror(_vertex_code)) {
    printf("[FAILED] Fragment shader file could not be read. \n");
    fclose(_vertex_code);
    _shader->ID = -1;
    return;
  }
  _vertex_buffer[_buffer_length] = '\0';
  
  if /*yet*/(_fragment_code) {
    fclose(_fragment_code);
  }
  if /*yet*/(_vertex_code) {
    fclose(_vertex_code);
  }
  
  char _info_log[512];
  int _success;
  
  _shader->_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(_shader->_vertex_shader, 1, (GLchar const * const *)&_vertex_buffer, NULL);
  glCompileShader(_shader->_vertex_shader);
  glGetShaderiv(_shader->_vertex_shader, GL_COMPILE_STATUS, &_success);
  if (!_success) {
    glGetShaderInfoLog(_shader->_vertex_shader, 512, NULL, _info_log);
    printf("[FAILED] Vertex shader compilation failed. \n");
    printf("[INFO_LOG] %s. \n", _info_log);
    return;
  }
  printf("[INFO] Vertex shader compiled successfully. \n");
  
  _shader->_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(_shader->_fragment_shader, 1, (GLchar const * const *)&_fragment_buffer, NULL);
  glCompileShader(_shader->_fragment_shader);
  glGetShaderiv(_shader->_fragment_shader, GL_COMPILE_STATUS, &_success);
  if (!_success) {
    glGetShaderInfoLog(_shader->_fragment_shader, 512, NULL, _info_log);
    printf("[FAILED] Fragment shader compilation failed. \n");
    printf("[INFO_LOG] %s. \n", _info_log);
    return;
  }
  printf("[INFO] Fragment shader compiled successfully. \n");
  
  _shader->ID = glCreateProgram();
  glAttachShader(_shader->ID, _shader->_fragment_shader);
  glAttachShader(_shader->ID, _shader->_vertex_shader);
  glLinkProgram(_shader->ID);
  glGetProgramiv(_shader->ID, GL_LINK_STATUS, &_success);
  if (!_success) {
    glGetProgramInfoLog(_shader->ID, 512, NULL, _info_log);
    printf("[FAILED] Shader program linking failed. \n");
    printf("[INFO_LOG] %s. \n", _info_log);
    return;
  }
  printf("[INFO] Shader program had been linked successfully. \n");
  return;
  
 BLANK:
  printf("[INFO] Shader file is blank. \n");
  if (_fragment_code) {
    fclose(_fragment_code);
  }
  else if (_vertex_code) {
    fclose(_vertex_code);
  }
  _shader->ID = -1;
  return;
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

void Molson(_set_matrix4)(const char *_name, const mat4 *_value, bool _use_shader, Shader *_shader) {
  if (_use_shader) {
    glUseProgram(_shader->ID);
  }
  glUniformMatrix4fv(glGetUniformLocation(_shader->ID, _name), 1, false, (float *)_value);
  return;
}

void Molson(_set_vector3_f)(const char *_name, vec3 _value, bool _use_shader, Shader *_shader) {
  if (_use_shader) {
    glUseProgram(_shader->ID);
  }
  glUniform3f(glGetUniformLocation(_shader->ID, _name), _value[0], _value[1], _value[2]);
  return;
}

void Molson(_set_int)(const char *_name, int _value, bool _use_shader, Shader *_shader) {
  if (_use_shader) {
    glUseProgram(_shader->ID);
  }
  glUniform1i(glGetUniformLocation(_shader->ID, _name), _value);
  return;
}


// --------------------------------------------------


void Molson(_generate_texture2d)(unsigned int _width, unsigned int _height, unsigned char *_data, Texture2D *_texture) {
  _texture->_height = _height;
  _texture->_width = _width;

  glBindTexture(GL_TEXTURE_2D, _texture->ID);
  glTexImage2D(GL_TEXTURE_2D, 0, _texture->_internal_format, _width, _height, 0, _texture->_image_format, GL_UNSIGNED_BYTE, _data);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _texture->_wrap_s);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _texture->_wrap_t);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _texture->_filter_min);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _texture->_filter_max);
  
  glBindTexture(GL_TEXTURE_2D, 0);
  printf("[INFO] Texture generated. \n");

  return;
}

void Molson(_init_texture2d)(Texture2D *_texture) {
  _texture->_internal_format = GL_RGB;
  _texture->_filter_min = GL_LINEAR;
  _texture->_filter_max = GL_LINEAR;
  _texture->_image_format = GL_RGB;
  _texture->_wrap_s = GL_REPEAT;
  _texture->_wrap_t = GL_REPEAT;
  _texture->_height = 0;
  _texture->_width = 0;
  
  glGenTextures(1, _texture->ID);
  return;
}

void Molson(_bind_texture2d)(Texture2D *_texture) {
  glBindTexture(GL_TEXTURE_2D, _texture->ID);
  return;
}

void Molson(_load_texture2d)(const char *_file, bool _alpha, Texture2D *_texture) {
  if (_alpha) {
    _texture->_internal_format = GL_RGBA;
    _texture->_image_format = GL_RGBA;
  }
  int _channels;
  int _height;
  int _width;

  unsigned char *_data = stbi_load(_file, &_width, &_height, &_channels, 0);
  Molson(_generate_texture2d)(_width, _height, _data, _texture);
  stbi_image_free(_data);
  
  printf("[INFO] Texture was loaded successfully. \n");
  return;
}

#endif




