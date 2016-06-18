#ifndef NCTU_GUI_WINDOW_h_
#define NCTU_GUI_WINDOW_h_

#include <CEGUI/CEGUI.h>
#include "NCTUPreRequisite.h"

namespace NCTU{
	/*! 
	\brief base class for all GUI window in this project
	*/
	class GUIWindow
	{
	public:
		/*! 
		\brief constructor
		*/
		GUIWindow(const CEGUI::String& layout);             
		/*! 
		\brief destructor
		*/
		virtual ~GUIWindow();
		/*! 
		\brief setup everything
		*/
		virtual void setup();
		/*! 
		\brief Hide or show the window
		*/
		virtual void setVisible(bool visible);         
		/*! 
		\brief return true if console is visible, false if is hidden
		*/
		virtual bool isVisible();                      
		/*! 
		\brief set up application pointer
		*/
		virtual void setApp(BasicTutorial_00* app){mApp = app;}
	protected:
		/*! The function which will load in the CEGUI Window and register event handlers
		\brief 
		*/
		virtual void createCEGUIWindow();                                  
		/*! 
		\brief Register our handler functions
		*/
		virtual void registerHandlers(){}                                   

		/*! 
		\brief This will be a pointer to the CEGUI window.
		*/
		CEGUI::Window *mWindow;                           
		/*! 
		\brief Store the layout name
		*/
		CEGUI::String mLayoutName;
		/*! 
		\brief pointer to the application
		*/
		BasicTutorial_00* mApp;
	};
};
#endif
