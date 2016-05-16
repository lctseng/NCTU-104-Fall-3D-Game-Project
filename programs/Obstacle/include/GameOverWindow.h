#ifndef NCTU_GUI_GAME_OVER_WINDOW_h_
#define NCTU_GUI_GAME_OVER_WINDOW_h_

#include "NCTUGUIWindow.h"

namespace NCTU{
	class GameOverWindow : public GUIWindow
	{
	public:
		GameOverWindow();           
	protected:
		virtual void registerHandlers();          
		bool onPressExit(const CEGUI::EventArgs &e);
		bool onPressMainMenu(const CEGUI::EventArgs &e);
	};
};
#endif
