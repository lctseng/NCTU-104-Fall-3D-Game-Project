#ifndef NCTU_GUI_MAIN_MENU_WINDOW_h_
#define NCTU_GUI_MAIN_MENU_WINDOW_h_

#include "NCTUGUIWindow.h"

namespace NCTU{
	/*! 
	\brief GHI window for main menu
	*/
	class MainMenuWindow : public GUIWindow
	{
	public:
		/*! 
		\brief constructor
		*/
		MainMenuWindow(); 
		/*! 
		\brief set visibility for this window
		*/
		virtual void setVisible(bool visible);
	protected:
		/*! 
		\brief register event handler
		*/
		virtual void registerHandlers();          
		/*! 
		\brief process when press play button
		*/
		bool onPressPlay(const CEGUI::EventArgs &e);
		/*! 
		\brief process when press level select button
		*/
		bool onPressLevel(const CEGUI::EventArgs &e);
		/*! 
		\brief process when press exit button
		*/
		bool onPressExit(const CEGUI::EventArgs &e);
	};
};
#endif
