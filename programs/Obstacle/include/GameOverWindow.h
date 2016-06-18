#ifndef NCTU_GUI_GAME_OVER_WINDOW_h_
#define NCTU_GUI_GAME_OVER_WINDOW_h_

#include "NCTUGUIWindow.h"

namespace NCTU{
	/*! 
	\brief GUI window for Game Over
	*/
	class GameOverWindow : public GUIWindow
	{
	public:
		/*! 
		\brief constructor
		*/
		GameOverWindow();           
	protected:
		/*! 
		\brief register event handler
		*/
		virtual void registerHandlers();          
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
