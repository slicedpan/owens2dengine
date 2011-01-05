/*
 * engine.cpp
 *
 *  Created on: 4 Jan 2011
 *      Author: owen
 */

#include "engine.h"
#include "gameinstance.h"
#include "defs.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "CEGUI.h"
#include "RendererModules/OpenGL/CEGUIOpenGLRenderer.h"


#include <cstdlib>

gameEngine * gameEngine::ge_ptr = 0;

gameEngine * gameEngine::GetSingleton()
{
	return ge_ptr;
}

gameEngine::gameEngine() : m_bQuit(true)
{
	if (GetSingleton() == 0) gameEngine::ge_ptr = this;
	else
	{

	}
	gi_ptr = 0;
}

gameEngine::~gameEngine()
{

}

void gameEngine::Init()
{

	atexit(SDL_Quit);

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		fprintf( stderr, "Unable to init SDL: %s\n", SDL_GetError() );
		exit( 1 );
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// Attempt to create a window with the specified height and width.
		// If we fail, return error.
	if (FULLSCREEN)
	{
		if (!SDL_SetVideoMode(SCRWIDTH, SCRHEIGHT, 32, SDL_OPENGL | SDL_FULLSCREEN))
		{
			fprintf(stderr, "Unable to set up video: %s\n", SDL_GetError());
			exit(1);
		}
	}
	else
	{
		if (!SDL_SetVideoMode(SCRWIDTH, SCRHEIGHT, 32, SDL_OPENGL))
		{
			fprintf(stderr, "Unable to set up video: %s\n", SDL_GetError());
			exit(1);
		}
	}

	glShadeModel(GL_SMOOTH);
	glClearColor(0.1, 0.1, 0.1, 1);
	glViewport(0,0,SCRWIDTH,SCRHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	CEGUI::OpenGLRenderer::bootstrapSystem(CEGUI::Size(800,600), CEGUI::OpenGLRenderer::TTT_AUTO);

	CEGUI::DefaultResourceProvider * rp = (CEGUI::DefaultResourceProvider *)CEGUI::System::getSingleton().getResourceProvider();

	rp->setResourceGroupDirectory("schemes", "/home/owen/Downloads/CEGUI-0.7.5/datafiles/schemes/");
	rp->setResourceGroupDirectory("imagesets", "/home/owen/Downloads/CEGUI-0.7.5/datafiles/imagesets/");
	rp->setResourceGroupDirectory("fonts", "/home/owen/Downloads/CEGUI-0.7.5/datafiles/fonts/");
	rp->setResourceGroupDirectory("layouts", "/home/owen/Downloads/CEGUI-0.7.5/datafiles/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "/home/owen/Downloads/CEGUI-0.7.5/datafiles/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "/home/owen/Downloads/CEGUI-0.7.5/datafiles/lua_scripts/");
	rp->setResourceGroupDirectory("schemas", "/home/owen/Downloads/CEGUI-0.7.5/datafiles/xml_schemas/");

	CEGUI::Imageset::setDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

	CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
	if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
	    parser->setProperty("SchemaDefaultResourceGroup", "schemas");


	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");

	CEGUI::System& sr = CEGUI::System::getSingleton();

	sr.setDefaultMouseCursor("TaharezLook", "MouseArrow");
	sr.setDefaultFont("DejaVuSans-10");
	sr.setDefaultTooltip("TaharezLook/Tooltip");

	SDL_ShowCursor(SDL_DISABLE);

	SDL_EnableUNICODE(1);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);

	m_bQuit = false;
}

void gameEngine::Start()
{
	while (!m_bQuit)
	{
		if (gi_ptr == 0)
		{
			m_bQuit = true;
			continue;
		}
		gi_ptr->Load();
		while(gi_ptr->Running())
		{
			HandleInput();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.1, 0.1, 0.1, 1);
			gi_ptr->Step();
			CEGUI::System::getSingleton().renderGUI();
			SDL_GL_SwapBuffers();
		}
		gi_ptr->Unload();
		delete gi_ptr;
		gi_ptr = 0;
		if (nextInstance != 0)
		{
			gi_ptr = nextInstance;
			nextInstance = 0;
		}
	}
}
/**loads a game instance into the engine
 @remark p_gi_ptr will be deleted after use
 **/
void gameEngine::loadInstance(gameInstance * p_gi_ptr)
{
	if(gi_ptr == 0) //this means no instance is loaded yet, so we can safely set the current instance
	{
		gi_ptr = p_gi_ptr;
		return;
	}
	nextInstance = p_gi_ptr;
}

void gameEngine::HandleInput()
{
	SDL_Event event;
		while ( SDL_PollEvent( &event ) )
		{
			switch ( event.type )
			{
			case SDL_KEYDOWN:
				gi_ptr->KeyDown( event.key.keysym.sym );
				break;

			case SDL_KEYUP:
				gi_ptr->KeyUp( event.key.keysym.sym );
				break;

			case SDL_QUIT:
				m_bQuit = true;
				break;

			case SDL_MOUSEMOTION:
				gi_ptr->MouseMoved(
					event.button.button,
					event.motion.x,
					event.motion.y,
					event.motion.xrel,
					event.motion.yrel);
				break;

			case SDL_MOUSEBUTTONUP:
				gi_ptr->MouseButtonUp(
					event.button.button,
					event.motion.x,
					event.motion.y,
					event.motion.xrel,
					event.motion.yrel);
				break;

			case SDL_MOUSEBUTTONDOWN:
				gi_ptr->MouseButtonDown(
					event.button.button,
					event.motion.x,
					event.motion.y,
					event.motion.xrel,
					event.motion.yrel);
				break;

			case SDL_ACTIVEEVENT:
				if ( event.active.state & SDL_APPACTIVE ) {
					if ( event.active.gain ) {
						m_bMinimized = false;
						gi_ptr->WindowActive();
					} else {
						m_bMinimized = true;
						gi_ptr->WindowInactive();
					}
				}
				break;
			} // switch
		} // while (handling input)
}
