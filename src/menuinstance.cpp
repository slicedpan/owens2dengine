/*
 * mainmenu.cpp
 *
 *  Created on: 4 Jan 2011
 *      Author: owen
 */

#include "menuinstance.h"
#include "CEGUI.h"

using namespace CEGUI;

void menuInstance::Load()
{
	WindowManager& wmgr = WindowManager::getSingleton();
	Window* myRoot = wmgr.createWindow( "DefaultWindow", "root" );
	System::getSingleton().setGUISheet( myRoot );
	FrameWindow* fWnd = (FrameWindow*)wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" );
	myRoot->addChildWindow( fWnd );

	// position a quarter of the way in from the top-left of parent.
	fWnd->setPosition( UVector2( UDim( 0.25f, 0 ), UDim( 0.25f, 0 ) ) );

	// set size to be half the size of the parent
	fWnd->setSize( UVector2( UDim( 0.5f, 0 ), UDim( 0.5f, 0 ) ) );

	fWnd->setText( "Hello World!" );
}
