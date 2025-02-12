
#ifndef MAP_H
#define MAP_H
#define MAX_SIZE 1000

typedef struct {
    char _keys[MAX_SIZE][MAX_SIZE];
    void *_values[MAX_SIZE];
} MAP;

void *_map_namespace_get_index(char *_namespace, char *_key, MAP *_map);
void *_map_namespace_get(char *_namespace, char *_key, MAP *_map);
void _map_insert(char _key[], void *_value, MAP *_map);
void *_map_get_index(char _key[], MAP *_map);
void *_map_get(char _key[], MAP *_map);
void _map_printf(MAP *_map);

#endif//MAP_H
#ifdef MAP_IMPLEMENTATION

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int _current_size = 0;

void _map_insert(char _key[], void *_value, MAP *_map) {
    int _index = _map_get_index(_key, _map);
    if (_index == -1) {
	strcpy(_map->_keys[_current_size], _key);
	_map->_values[_current_size] = _value;
	_current_size++;
    }
    else {
	_map->_values[_index] = _value;
    }
}

void *_map_namespace_get_index(char *_namespace, char *_key, MAP *_map) {
    char *_value = malloc(strlen(_namespace) + strlen(_key) + 1);
    strcpy(_value, _namespace);
    strcat(_value, _key);
    _value[strlen(_namespace) + strlen(_key)] = '\0';

    for (int i = 0; i < _current_size; i++) {
	if (strcmp(_map->_keys[i], _value) == 0) {
	    return i;
	}
    }
    return -1;
}

void *_map_namespace_get(char *_namespace, char *_key, MAP *_map) {
    char *_value = malloc(strlen(_namespace) + strlen(_key) + 1);
    strcpy(_value, _namespace);
    strcat(_value, _key);
    _value[strlen(_namespace) + strlen(_key)] = '\0';
    
    int _index = _map_get_index(_value, _map);
    if (_index == -1) {
	return -1;
    }
    else {
	return _map->_values[_index];
    }
}

void *_map_get_index(char _key[], MAP *_map) {
    for (int i = 0; i < _current_size; i++) {
	if (strcmp(_map->_keys[i], _key) == 0) {
	    return i;
	}
    }
    return -1;
}

void *_map_get(char _key[], MAP *_map) {
    int _index = _map_get_index(_key, _map);
    if (_index == -1) {
	return -1;
    }
    else {
	return _map->_values[_index];
    }
}

void _map_printf(MAP *_map) {
    for (int i = 0; i < _current_size; i++) {
	printf("    [INFO_MAP] %s: VALUE. \n", _map->_keys[i]);
    }
}

#endif
