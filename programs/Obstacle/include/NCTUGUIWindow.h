#ifndef NCTU_GUI_WINDOW_h_
#define NCTU_GUI_WINDOW_h_

#include <CEGUI/CEGUI.h>
#include "NCTUPreRequisite.h"

namespace NCTU{
	class GUIWindow
	{
	public:
		GUIWindow(const CEGUI::String& layout);                   // Constructor
		virtual ~GUIWindow();
		virtual void setup();
		virtual void setVisible(bool visible);         // Hide or show the console
		virtual bool isVisible();                      // return true if console is visible, false if is hidden

		virtual void setApp(BasicTutorial_00* app){mApp = app;}

	protected:
		virtual void createCEGUIWindow();                                  // The function which will load in the CEGUI Window and register event handlers
		virtual void registerHandlers(){}                                   // Register our handler functions

		CEGUI::Window *mWindow;                            // This will be a pointer to the CEGUI window.
		CEGUI::String mLayoutName;
		BasicTutorial_00* mApp;
	};
};
#endif
