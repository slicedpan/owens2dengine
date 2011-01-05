/*
 * main.cpp
 *
 *  Created on: 4 Jan 2011
 *      Author: owen
 */

#include "engine.h"
#include "menuinstance.h"
#include <cassert>

int main(int argc, char ** argv)
{
	gameEngine GE;
	gameInstance * GI = new menuInstance();
	GE.Init();
	GE.loadInstance(GI);
	GE.Start();
}
