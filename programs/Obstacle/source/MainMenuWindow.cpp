#include "MainMenuWindow.h"
#include "TutorialApplication.h"

using namespace NCTU;

MainMenuWindow::MainMenuWindow():
GUIWindow("MainMenu.layout")
{
	
}
void MainMenuWindow::registerHandlers()
{
	// Play Button
	mWindow->getChild("PlayButton")->subscribeEvent(
		CEGUI::PushButton::EventClicked,    // If we recall our button was of type CEGUI::PushButton in the .scheme
		// and we want to acknowledge the EventClicked action.
		CEGUI::Event::Subscriber(           // What function to call when this is clicked.  Remember, all functions 
		// are contained within (this) class.
			&MainMenuWindow::onPressPlay,  // Call Handle_SendButtonPressed member of MainMenuWindow
			this));                             // Using (this) instance we're in right now
	// Exit Button
	mWindow->getChild("ExitButton")->subscribeEvent(
		CEGUI::PushButton::EventClicked,   
		CEGUI::Event::Subscriber(    
			&MainMenuWindow::onPressExit,
			this));                  
}
bool MainMenuWindow::onPressPlay(const CEGUI::EventArgs &e)
{
	mApp->startGame();
	return true;
}
bool MainMenuWindow::onPressExit(const CEGUI::EventArgs &e)
{
	mApp->exitGame();
	return true;
}