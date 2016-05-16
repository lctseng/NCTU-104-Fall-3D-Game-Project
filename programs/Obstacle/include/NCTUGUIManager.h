#ifndef NCTU_GUI_MANAGER_h_
#define NCTU_GUI_MANAGER_h_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "OIS.h"


#include "NCTUPreRequisite.h"
#include "GameConsoleWindow.h"
#include "MainMenuWindow.h"
#include "GameMenuWindow.h"
#include "ScoreBarWindow.h"

namespace NCTU{
	class GUIManager{
	public:
		GUIManager();
		~GUIManager();
		void setup(BasicTutorial_00* app);

		void createAllWindow();

		void createConsole();
		void createMainMenu();
		void createGameMenu();
		void createScoreBar();

		void update(double timestep);

		// OIS::KeyListener
		bool keyPressed( const OIS::KeyEvent &arg );
		bool keyReleased( const OIS::KeyEvent &arg );
		// OIS::MouseListener
		bool mouseMoved( const OIS::MouseEvent &arg );
		bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

		MainMenuWindow* getMainMenu(){return mMainMenu;}
		GameMenuWindow* getGameMenu(){return mGameMenu;}
		ScoreBarWindow* getScoreBar(){return mScoreBar;}

	protected:
		CEGUI::OgreRenderer* mRenderer;

		// Test Console
		GameConsoleWindow* mConsole;
		MainMenuWindow*  mMainMenu;
		GameMenuWindow*  mGameMenu;
		ScoreBarWindow* mScoreBar;
		// 
		
		CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
		BasicTutorial_00* mApp;
	};
};

#endif