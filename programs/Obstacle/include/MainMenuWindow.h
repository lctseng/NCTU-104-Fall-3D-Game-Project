#ifndef NCTU_GUI_MAIN_MENU_WINDOW_h_
#define NCTU_GUI_MAIN_MENU_WINDOW_h_

#include "NCTUGUIWindow.h"

namespace NCTU{
	class MainMenuWindow : public GUIWindow
	{
	public:
		MainMenuWindow();           
		virtual void setVisible(bool visible);
	protected:
		virtual void registerHandlers();          
		bool onPressPlay(const CEGUI::EventArgs &e);
		bool onPressLevel(const CEGUI::EventArgs &e);
		bool onPressExit(const CEGUI::EventArgs &e);
	};
};
#endif
