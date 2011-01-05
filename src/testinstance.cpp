/*
 * testinstance.cpp
 *
 *  Created on: 4 Jan 2011
 *      Author: owen
 */

#include "SDL/SDL_opengl.h"
#include "testinstance.h"
#include "defs.h"

void testInstance::Step()
{
	glPushMatrix();
	gluOrtho2D(0,SCRWIDTH, 0, SCRHEIGHT);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(100, 0);
		glVertex2i(100, 100);
		glVertex2i(0, 100);
	glPopMatrix();
}

void testInstance::Load()
{

}
