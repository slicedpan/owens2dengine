/*
 * gameinstance.cpp
 *
 *  Created on: 4 Jan 2011
 *      Author: owen
 */

#include "gameinstance.h"
#include "SDL/SDL_opengl.h"
#include "defs.h"

gameInstance::gameInstance() : m_bRunning(true)
{

}

void gameInstance::Load()
{

}

void gameInstance::Unload()
{

}

void gameInstance::Step()
{


}

void gameInstance::KeyDown(const int& iKeyEnum)
{
	if (iKeyEnum == 27) //SDLK_ESCAPE
	{
		m_bRunning = false;
	}
}

void gameInstance::KeyUp(const int& iKeyEnum)
{

}

void gameInstance::MouseButtonUp (const int& iButton, const int& iX, const int& iY, const int& iRelX, const int& iRelY)
{

}

void gameInstance::MouseButtonDown(const int& iButton, const int& iX, const int& iY, const int& iRelX, const int& iRelY)
{

}

void gameInstance::MouseMoved(const int& iButton, const int& iX, const int& iY, const int& iRelX, const int& iRelY)
{

}
void gameInstance::WindowActive()
{

}

void gameInstance::WindowInactive()
{

}

