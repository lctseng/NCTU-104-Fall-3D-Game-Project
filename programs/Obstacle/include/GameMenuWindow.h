#ifndef NCTU_GUI_GAME_MENU_WINDOW_h_
#define NCTU_GUI_GAME_MENU_WINDOW_h_

#include "NCTUGUIWindow.h"

namespace NCTU{
	/*! 
	\brief Menu window
	*/
	class GameMenuWindow : public GUIWindow
	{
	public:
		/*! 
		\brief constructor
		*/
		GameMenuWindow();           
	protected:
		/*! 
		\brief register event handlers
		*/
		virtual void registerHandlers();          
		/*! 
		\brief process when press resume botton
		*/
		bool onPressResume(const CEGUI::EventArgs &e);
		/*! 
		\brief process when press exit botton
		*/
		bool onPressExit(const CEGUI::EventArgs &e);
		/*! 
		\brief process when press MainMenu botton
		*/
		bool onPressMainMenu(const CEGUI::EventArgs &e);
	};
};
#endif
