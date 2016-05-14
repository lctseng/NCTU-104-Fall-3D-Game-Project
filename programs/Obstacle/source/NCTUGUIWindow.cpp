#include "NCTUGUIWindow.h"
#include <iostream>

using namespace NCTU;

GUIWindow::GUIWindow(const CEGUI::String& layout):
mApp(nullptr),
mLayoutName(layout),
mWindow(nullptr)
{ 
}

GUIWindow::~GUIWindow(){
}

void GUIWindow::setup(){
	createCEGUIWindow();
	registerHandlers();
	setVisible(false);
}



void GUIWindow::createCEGUIWindow()
{
	// Get a local pointer to the CEGUI Window Manager, Purely for convenience to reduce typing
	CEGUI::WindowManager *pWindowManager = CEGUI::WindowManager::getSingletonPtr();
	mWindow = pWindowManager->loadLayoutFromFile(mLayoutName);
	if (mWindow)
	{
		// Lets add our new window to the Root GUI Window
		CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(mWindow);
		// Now register the handlers for the events (Clicking, typing, etc)
		mWindow->setUserData(this);  
	}
	else
	{
		// Something bad happened and we didn't successfully create the window lets output the information
		CEGUI::Logger::getSingleton().logEvent("Error: Unable to load the " + mLayoutName +  " from .layout");
	}
}
void GUIWindow::setVisible(bool visible)
{
    mWindow->setVisible(visible);
	if(!visible){
		mWindow->invalidate(true);
	}
	
}
 
bool GUIWindow::isVisible()
{
    return mWindow->isVisible();
}