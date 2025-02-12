
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
    _FLOAT		= 5,
    _SPACE		= 6,
    _COLON		= 7,
    _FALSE		= 8,
    _TRUE		= 9,
    _NULL		= 10,
};
typedef struct {
    const char *_value;
    int _type;
} TOKEN;

TOKEN Molang(_create_token)(int _type, const char *_value);
MAP Molang(_lexer)(const char *_file);
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

static char *_num_to_ascii(int _number) {
    
    char *_string = malloc(1);
    if (!_string) {
	printf("[INFO] _num_to_ascii() :: _string memory allocation failed. \n");
	return 0;
    }
    _string = _number;
    _string[1] = 0;
    
    return _string;
}

MAP Molang(_lexer)(const char *_file) {
    TOKEN *_tokens = (TOKEN *)malloc(strlen(_file) * sizeof(TOKEN));
    int _current_position = 0;
    
    // MAP _test;
    // // void _map_insert(char _key[], void *_value, MAP *_map);
    // _map_insert("Test", "Daniel", &_test);
    // const char *_name = _map_get("Test", &_test);
    // printf("\n[INFO] %s. \n\n", _name);
    
    printf("\n--------------------------------------------------\n\n");
    printf("[INFO] Lexing... \n");
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
	    const int _previous_current_position = _current_position;
	    bool _float = false;
	    char *_value = "";
	    char *_new_value;
	    
	    size_t _length;
	    _token = _file[_current_position];
	    while (isdigit(_token) || _token == '.') {
		
		if (_token == '.') {
		    _float = true;
		}
		
		_length = strlen(_value);
		_new_value = malloc(_length + 2);
		strcpy(_new_value, _value);
		_new_value[_length] = (char)_token;
		_new_value[_length + 1] = '\0';
		_value = malloc(strlen(_new_value) + 1);
		strcpy(_value, _new_value);
		
		_current_position += 1;
		_token = _file[_current_position];
	    }
	    // printf("[INFO] _value = %s. \n", _value);
	    _token = _file[_current_position];
	    
	    const int _amount_to_back = _current_position - _previous_current_position;
	    if (_float == false) {
		_tokens[_current_position - _amount_to_back] = Molang(_create_token)(_NUMBER, _value);
		free(_new_value);
		continue;
	    }
	    _tokens[_current_position - _amount_to_back] = Molang(_create_token)(_FLOAT, _value);
	    free(_new_value);
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
    printf("[INFO] Lexing process had been finished. Starting parsering process. \n");
    MAP _final_map = Molang(_parser)(_tokens, strlen(_file));
    free(_tokens);
    printf("[INFO] Parsering process had been finished. \n");
    printf("\n--------------------------------------------------\n\n");
    return _final_map;
}

static char *_concatenate_strings(char *_string_1, char *_string_2) {
    
    char *_result = malloc(strlen(_string_1) + strlen(_string_2) + 1);
    if (_result  == NULL) {
	fprintf(stderr, "[FAILED] _concatenate_strings :: Failed at concatenating strings. \n");
	return "";
    }
    strcpy(_result, _string_1);
    strcat(_result, _string_2);
    _result[strlen(_string_1) + strlen(_string_2)] = '\0';
    
    return _result;
}

MAP Molang(_parser)(TOKEN _tokens[], size_t _array_size) {
    char *_namespace_name = "";
    int _current_position = 0;
    MAP _output_map;
    
    while (_current_position < _array_size) {
	// TODO: Code a better namespace system. This sucks;
	if (_tokens[_current_position]._type == _OPEN_BRACKET &&
	    _tokens[_current_position + 1]._type == _STRING
	) {
	    _current_position++;
	    // printf("[INFO] Current string: %s. \n", _tokens[_current_position]._value);
	    char *_variable_name  = (char *)_tokens[_current_position]._value;
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

		// --------------------------------------------------
		printf("[INFO] Current token type being 'lexed': %d. \n", _tokens[_current_position]._type);
		if (_tokens[_current_position]._type == _OPEN_BRACKET) {
		    
		    _namespace_name = malloc(strlen(_variable_name) + 1);
		    if (_namespace_name == NULL) {
			fprintf(stderr, "[FAILED] Failed at concatenating proper namespace string. \n");
			break;
		    }
		    strcpy(_namespace_name, _variable_name);
		    _namespace_name[strlen(_variable_name)] = '\0';
		    
		    printf("[INFO] Namespace %s had been found. \n", _namespace_name);
		}
		else if (_tokens[_current_position]._type == _STRING) {
		    
		    if (strlen(_namespace_name) > 0) {
			char *_namespace_variable_name = _concatenate_strings(_namespace_name, _variable_name);
			
			_map_insert(_namespace_variable_name, (char *)_tokens[_current_position]._value, &_output_map);
			free(_namespace_variable_name);
			continue;
		    }
		    else {
			_map_insert(_variable_name, (char *)_tokens[_current_position]._value, &_output_map);
		    }
		}
		else if (_tokens[_current_position]._type == _NUMBER) {
		    
		    int _value = atoll(_tokens[_current_position]._value);
		    if (strlen(_namespace_name) > 0) {
			char *_namespace_variable_name = _concatenate_strings(_namespace_name, _variable_name);
			
			_map_insert(_namespace_variable_name, &_value, &_output_map);
			free(_namespace_variable_name);
			continue;
		    }
		    else {
			_map_insert(_variable_name, &_value, &_output_map);
		    }
		}
		else if (_tokens[_current_position]._type == _FLOAT) {
		    float _value = atof(_tokens[_current_position]._value);
		    if (strlen(_namespace_name) > 0) {
			char *_namespace_variable_name = _concatenate_strings(_namespace_name, _variable_name);
			
			_map_insert(_namespace_variable_name, &_value, &_output_map);
			free(_namespace_variable_name);
			continue;
		    }
		    else {
			_map_insert(_variable_name, &_value, &_output_map);
		    }
		}
		else if (_tokens[_current_position]._type == _NULL) {
		    
		    if (strlen(_namespace_name) > 0) {
			char *_namespace_variable_name = _concatenate_strings(_namespace_name, _variable_name);
			
			_map_insert(_namespace_variable_name, NULL, &_output_map);
			free(_namespace_variable_name);
			continue;
		    }
		    else {
			_map_insert(_variable_name, NULL, &_output_map);
		    }
		}
		else if (_tokens[_current_position]._type == _FALSE) {
		    
		    if (strlen(_namespace_name) > 0) {
			char *_namespace_variable_name = _concatenate_strings(_namespace_name, _variable_name);
			
			_map_insert(_namespace_variable_name, false, &_output_map);
			free(_namespace_variable_name);
			continue;
		    }
		    else {
			_map_insert(_variable_name, false, &_output_map);
		    }
		}
		else if (_tokens[_current_position]._type == _TRUE) {
		    if (strlen(_namespace_name) > 0) {
			char *_namespace_variable_name = _concatenate_strings(_namespace_name, _variable_name);
			
			_map_insert(_namespace_variable_name, true, &_output_map);
			free(_namespace_variable_name);
			continue;
		    }
		    else {
			_map_insert(_variable_name, true, &_output_map);
		    }
		}
	    }
	    else if (_tokens[_current_position]._type == _CLOSE_BRACKET &&
	        _tokens[_current_position + 1]._type == _SEMICOLON
	    ) {
		// TODO here
	    }
	    free(_variable_name);
	}
	
	_current_position++;
    }
    // _map_printf(&_output_map);
    return _output_map;
}


#endif//MOLANG_IMPLEMENTATION
