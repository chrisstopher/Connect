#ifndef _COLOR_H_
#define _COLOR_H_

#include "SDL_opengl.h"

class Color {
public:
	Color(GLubyte nr = 0, GLubyte ng = 0, GLubyte nb = 0, GLubyte na = 255);
	GLubyte r, g, b, a;
};

#endif