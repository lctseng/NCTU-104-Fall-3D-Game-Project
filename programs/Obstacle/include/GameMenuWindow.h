#ifndef NCTU_GUI_GAME_MENU_WINDOW_h_
#define NCTU_GUI_GAME_MENU_WINDOW_h_

#include "NCTUGUIWindow.h"

namespace NCTU{
	class GameMenuWindow : public GUIWindow
	{
	public:
		GameMenuWindow();           
	protected:
		virtual void registerHandlers();          
		bool onPressResume(const CEGUI::EventArgs &e);
		bool onPressExit(const CEGUI::EventArgs &e);
		bool onPressMainMenu(const CEGUI::EventArgs &e);
	};
};
#endif
