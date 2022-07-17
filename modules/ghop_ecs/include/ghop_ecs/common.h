#pragma once

#define GROW(_DATA, _SIZE, _COUNT, _CAPACITY)                                  \
    {                                                                          \
	if (_DATA == NULL) {                                                   \
	    _CAPACITY = 16;                                                    \
	    _DATA = malloc(_SIZE * _CAPACITY);                                 \
	} else if (_COUNT == _CAPACITY) {                                      \
	    _CAPACITY *= 2;                                                    \
	    _DATA = realloc(_DATA, _SIZE * _CAPACITY);                         \
	}                                                                      \
    }