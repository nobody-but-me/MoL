
#ifndef MOLANG_H
#define MOLANG_H
#define Molang(x) molang##x

#include "./map.h"
#define _MAX_ARRAY_SIZE 255

enum TOKENS {
    _CLOSE_BRACKET	= 0,
    _OPEN_BRACKET	= 1,
    _SEMICOLON		= 2,
    _NUMBER		= 3,
    _STRING		= 4,
    _SPACE		= 5,
    _COLON		= 6,
    _FALSE		= 7,
    _TRUE		= 8,
    _NULL		= 9,
};
typedef struct {
    const char *_value;
    int _type;
} TOKEN;

TOKEN Molang(_create_token)(int _type, const char *_value);
void Molang(_lexer)(const char *_file);
MAP Molang(_parser)(TOKEN _tokens[], size_t _array_size);

#endif//MOLANG_H
#ifdef MOLANG_IMPLEMENTATION

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAP_IMPLEMENTATION
#include "./map.h"


TOKEN Molang(_create_token)(int _type, const char *_value) {
    TOKEN _token = {
	._value = _value,
	._type = _type
    };
    return _token;
}

void Molang(_lexer)(const char *_file) {
    TOKEN *_tokens = (TOKEN *)malloc(strlen(_file) * sizeof(TOKEN));
    int _current_position = 0;
    
    // MAP _test;
    // // void _map_insert(char _key[], void *_value, MAP *_map);
    // _map_insert("Test", "Daniel", &_test);
    // const char *_name = _map_get("Test", &_test);
    // printf("\n[INFO] %s. \n\n", _name);
    
    printf("\n--------------------------------------------------\n\n");
    while (_current_position < strlen(_file)) {
	char _token = _file[_current_position];
	
	if (_token == ' ') {
	    _tokens[_current_position] = Molang(_create_token)(_SPACE, " ");
	    _current_position += 1;
	    // printf("[SPACE] \n");
	    continue;
	}
	else if (_token == ']') {
	    _tokens[_current_position] = Molang(_create_token)(_CLOSE_BRACKET, "]");
	    _current_position += 1;
	    // printf("[CLOSE_BRACKET] \n");
	    continue;
	}
	else if (_token == '[') {
	    _tokens[_current_position] = Molang(_create_token)(_OPEN_BRACKET, "[");
	    _current_position += 1;
	    // printf("[OPEN_BRACKET] \n");
	    continue;
	}
	else if (_token == ';') {
	    _tokens[_current_position] = Molang(_create_token)(_SEMICOLON, ";");
	    _current_position += 1;
	    // printf("[SEMICOLON] \n");
	    continue;
	}
	else if (isdigit(_token)) {
	    printf("[INFO] Token value: %d. \n", _token);
	    const int _previous_current_position = _current_position;
	    char *_value = "";
	    
	    size_t _length;
	    while (isdigit(_token)) {
		// printf("[INFO]    Number: %c. \n", _token);
		// _value += sprintf(_token);
		
		_length = strlen(_value);
		_value = malloc(_length + sizeof(_token));
		sprintf(_value, "%d", _token);
		printf("[INFO] Value value: %s. \n", _value);
		
		_current_position += 1;
		_token = _file[_current_position];
	    }
	    _tokens[_current_position] = Molang(_create_token)(_NUMBER, _value);
	    continue;
	}
	else if (_token == '"') {
	    const int _previous_current_position = _current_position;
	    char *_string_value;
	    char *_value = "";
	    
	    _current_position += 1;
	    _token = _file[_current_position];
	    size_t _length;
	    
	    while (_token != '"') {
		// printf("    [INFO] String: %c. \n", _token);
		
		_length = strlen(_value);
		_string_value = malloc(_length + 1 + 1);
		strcpy(_string_value, _value);
		_string_value[_length] = _token;
		_string_value[_length + 1] = '\0';
		_value = malloc(strlen(_string_value) + 1);
		strcpy(_value, _string_value);
		
		_current_position += 1;
		_token = _file[_current_position];
	    }
	    // _current_position += 1;
	    _token = _file[_current_position];
	    
	    const int _amount_to_back = _current_position - _previous_current_position;
	    _tokens[_current_position - _amount_to_back] = Molang(_create_token)(_STRING, _value);
	    free(_string_value);
	}
	else if (_token == ':') {
	    _tokens[_current_position] = Molang(_create_token)(_COLON, ":");
	    _current_position += 1;
	    // printf("[COLON] \n");
	    continue;
	}
	else if (_token == 't' &&
	         _file[_current_position + 1] == 'r' &&
		 _file[_current_position + 2] == 'u' &&
		 _file[_current_position + 3] == 'e'
	) {
	    _tokens[_current_position] = Molang(_create_token)(_TRUE, "true");
	    _current_position += 4;
	    // printf("[TRUE] \n");
	}
	else if (_token == 'f' &&
	         _file[_current_position + 1] == 'a' &&
		 _file[_current_position + 2] == 'l' &&
		 _file[_current_position + 3] == 's' &&
		 _file[_current_position + 4] == 'e'
	) {
	    _tokens[_current_position] = Molang(_create_token)(_FALSE, "false");
	    _current_position += 5;
	    // printf("[FALSE] \n");
	}
	else if (_token == 'N' &&
	         _file[_current_position + 1] == 'U' &&
		 _file[_current_position + 2] == 'L' &&
		 _file[_current_position + 3] == 'L'
	) {
	    _tokens[_current_position] = Molang(_create_token)(_NULL, "NULL");
	    _current_position += 4;
	    // printf("[NULL] \n");
	}
	else {
	    _current_position += 1;
	    // printf("[BLANK] \n");
	    continue;
	}
	_current_position++;
    }
    Molang(_parser)(_tokens, strlen(_file));
    free(_tokens);
    printf("\n--------------------------------------------------\n\n");
    return;
}

MAP Molang(_parser)(TOKEN _tokens[], size_t _array_size) {
    int _current_position = 0;
    MAP _output_map;
    
    while (_current_position < _array_size) {
	
	if (_tokens[_current_position]._type == _OPEN_BRACKET &&
	    _tokens[_current_position + 1]._type == _STRING
	) {
	    _current_position++;
	    // printf("[INFO] Current string: %s. \n", _tokens[_current_position]._value);
	    while (_tokens[_current_position]._type != _CLOSE_BRACKET) {
		_current_position++;
	    }
	    
	    if (_tokens[_current_position]._type == _CLOSE_BRACKET &&
	        _tokens[_current_position + 1]._type == _COLON
	    ) {
		_current_position += 2;
		while(_tokens[_current_position]._type == _SPACE) {
		    _current_position++;
		}
		if (_tokens[_current_position]._type == _OPEN_BRACKET) {
		    printf("[INFO] Object had been found. \n");
		    continue;
		}
		else if (_tokens[_current_position]._type == _STRING) {
		    printf("[INFO] String had been found. \n");
		}
		else if (_tokens[_current_position]._type == _NUMBER) {
		    printf("[INFO] Number had been found. \n");
		    printf("    Number: %s. \n", _tokens[_current_position]._value);
		}
		
	    }
	}
	
	_current_position++;
    }
    
    _map_insert("shit", "shit just to initialize it", &_output_map);
    return _output_map;
}


#endif//MOLANG_IMPLEMENTATION
