#include "GameMenuWindow.h"
#include "TutorialApplication.h"

using namespace NCTU;

GameMenuWindow::GameMenuWindow():
GUIWindow("GameMenu.layout")
{
	
}
void GameMenuWindow::registerHandlers()
{
	// Play Button
	mWindow->getChild("ResumeButton")->subscribeEvent(
		CEGUI::PushButton::EventClicked,    // If we recall our button was of type CEGUI::PushButton in the .scheme
		// and we want to acknowledge the EventClicked action.
		CEGUI::Event::Subscriber(           // What function to call when this is clicked.  Remember, all functions 
		// are contained within (this) class.
			&GameMenuWindow::onPressResume,  // Call Handle_SendButtonPressed member of GameMenuWindow
			this));                             // Using (this) instance we're in right now
	// MainMenu Button
	mWindow->getChild("MainMenuButton")->subscribeEvent(
		CEGUI::PushButton::EventClicked,   
		CEGUI::Event::Subscriber(    
			&GameMenuWindow::onPressMainMenu,
			this));    
	// Exit Button
	mWindow->getChild("ExitButton")->subscribeEvent(
		CEGUI::PushButton::EventClicked,   
		CEGUI::Event::Subscriber(    
			&GameMenuWindow::onPressExit,
			this));       
}
bool GameMenuWindow::onPressResume(const CEGUI::EventArgs &e)
{
	mApp->resumeGame();
	return true;
}
bool GameMenuWindow::onPressMainMenu(const CEGUI::EventArgs &e)
{
	mApp->backToMainMenu();
	return true;
}
bool GameMenuWindow::onPressExit(const CEGUI::EventArgs &e)
{
	mApp->exitGame();
	return true;
}