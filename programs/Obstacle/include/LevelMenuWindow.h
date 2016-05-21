#ifndef NCTU_GUI_LEVEL_MENU_WINDOW_h_
#define NCTU_GUI_LEVEL_MENU_WINDOW_h_

#include "NCTUGUIWindow.h"

namespace NCTU{
	class LevelMenuWindow : public GUIWindow
	{
	public:
		LevelMenuWindow();           
		void updateDisableState();
		virtual void setVisible(bool visible);
	protected:
		virtual void registerHandlers();          
		bool onPressLevel1(const CEGUI::EventArgs &e);
		bool onPressLevel2(const CEGUI::EventArgs &e);
		bool onPressLevel3(const CEGUI::EventArgs &e);
		bool onPressCancel(const CEGUI::EventArgs &e);
	};
};
#endif
