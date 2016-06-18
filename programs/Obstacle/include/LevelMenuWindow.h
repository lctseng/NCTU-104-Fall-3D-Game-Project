#ifndef NCTU_GUI_LEVEL_MENU_WINDOW_h_
#define NCTU_GUI_LEVEL_MENU_WINDOW_h_

#include "NCTUGUIWindow.h"

namespace NCTU{
	/*! 
	\brief GUI window for selecting level
	*/
	class LevelMenuWindow : public GUIWindow
	{
	public:
		/*! 
		\brief constructor
		*/
		LevelMenuWindow();           
		/*! 
		\brief refresh disable state for button
		*/
		void updateDisableState();
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
		\brief process when pressing level 1
		*/
		bool onPressLevel1(const CEGUI::EventArgs &e);
		/*! 
		\brief process when pressing level 2
		*/
		bool onPressLevel2(const CEGUI::EventArgs &e);
		/*! 
		\brief process when pressing level 3
		*/
		bool onPressLevel3(const CEGUI::EventArgs &e);
		/*! 
		\brief process when pressing cancel button 
		*/
		bool onPressCancel(const CEGUI::EventArgs &e);
	};
};
#endif
