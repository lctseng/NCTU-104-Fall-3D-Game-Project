#ifndef NCTU_GUI_MANAGER_h_
#define NCTU_GUI_MANAGER_h_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "OIS.h"


#include "NCTUPreRequisite.h"
#include "GameConsoleWindow.h"
#include "MainMenuWindow.h"
#include "LevelMenuWindow.h"
#include "GameMenuWindow.h"
#include "GameOverWindow.h"
#include "ScoreBarWindow.h"


namespace NCTU{
	/*! 
	\brief manager class for GUI windows
	*/
	class GUIManager{
	public:
		/*! 
		\brief constructor
		*/
		GUIManager();
		/*! 
		\brief destructor
		*/
		~GUIManager();
		/*! 
		\brief bind application in the manager
		*/
		void setup(BasicTutorial_00* app);
		/*! 
		\brief create all window
		*/
		void createAllWindow();
		/*! 
		\brief create console window
		*/
		void createConsole();
		/*! 
		\brief create main menu window
		*/
		void createMainMenu();
		/*! 
		\brief create level selection window
		*/
		void createLevelMenu();
		/*! 
		\brief create game menu for playing game window
		*/
		void createGameMenu();
		/*! 
		\brief create score bar window
		*/
		void createScoreBar();
		/*! 
		\brief create game over menu window
		*/
		void createGameOver();
		/*! 
		\brief update the manager
		*/
		void update(double timestep);
		// OIS::KeyListener
		bool keyPressed( const OIS::KeyEvent &arg );
		bool keyReleased( const OIS::KeyEvent &arg );
		// OIS::MouseListener
		bool mouseMoved( const OIS::MouseEvent &arg );
		bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		/*! 
		\brief get pointer of main menu
		*/
		MainMenuWindow* getMainMenu(){return mMainMenu;}
		/*! 
		\brief get pointer of level menu
		*/
		LevelMenuWindow* getLevelMenu(){return mLevelMenu;}
		/*! 
		\brief get pointer of game menu
		*/
		GameMenuWindow* getGameMenu(){return mGameMenu;}
		/*! 
		\brief get pointer of score bar
		*/
		ScoreBarWindow* getScoreBar(){return mScoreBar;}
		/*! 
		\brief get pointer of game over menu
		*/
		GameOverWindow* getGameOver(){return mGameOver;}
	protected:
		/*! 
		\brief the pointer to the CEGUI-Ogre renderer
		*/
		CEGUI::OgreRenderer* mRenderer;
		/*! 
		\brief the demo console window
		*/
		GameConsoleWindow* mConsole;
		/*! 
		\brief the main menu window
		*/
		MainMenuWindow*  mMainMenu;
		/*! 
		\brief the level selection menu window
		*/
		LevelMenuWindow*  mLevelMenu;
		/*! 
		\brief the game menu window
		*/
		GameMenuWindow*  mGameMenu;
		/*! 
		\brief the game over window
		*/
		GameOverWindow*  mGameOver;
		/*! 
		\brief the score bar window
		*/
		ScoreBarWindow* mScoreBar;
		/*! 
		\brief convert OIS button data into CEGUI's
		*/
		CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
		/*! 
		\brief pointer to the Application
		*/
		BasicTutorial_00* mApp;
	};
};

#endif