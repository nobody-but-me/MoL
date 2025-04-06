
#ifndef COLLISION_H
#define COLLISION_H

#define Collision(x) coll##x

#include "../object.h"
#include <stdbool.h>

bool _is_rectangle_colliding(SHAPE *_rect1, SHAPE *_rect2);

#endif//COLLISION_H
#ifdef COLLISION_IMPLEMENTATION

#include "../object.h"
#include <stdbool.h>

bool _is_rectangle_colliding(SHAPE * _rect1, SHAPE * _rect2) {
    if (_rect1->_object._position[0] < _rect2->_object._position[0] + _rect2->_object._scale[0] &&
        _rect1->_object._position[0] + _rect1->_object._scale[0] > _rect2->_object._position[0] && 
	_rect1->_object._position[1] < _rect2->_object._position[1] + _rect2->_object._scale[1] &&
	_rect1->_object._position[1] + _rect1->_object._scale[1] > _rect2->_object._position[1]
    ) {
	return true;
    }
    return false;
}

#endif//COLLISION_IMPLEMENTATION
