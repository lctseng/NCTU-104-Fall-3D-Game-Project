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
	// Level Button
	mWindow->getChild("LevelButton")->subscribeEvent(
		CEGUI::PushButton::EventClicked,   
		CEGUI::Event::Subscriber(    
		&MainMenuWindow::onPressLevel,
		this));    
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
bool MainMenuWindow::onPressLevel(const CEGUI::EventArgs &e)
{
	mApp->enterLevelMenu();
	return true;
}
bool MainMenuWindow::onPressExit(const CEGUI::EventArgs &e)
{
	mApp->exitGame();
	return true;
}
void MainMenuWindow::setVisible(bool visible){
	GUIWindow::setVisible(visible);
	if(visible){
		String levelName = "No Level Selected";
		String bgName = "";
		String currentName = mApp->getCurrentLevelName();
		if(currentName == "level1.scene"){
			levelName = "Level 1";
			bgName = "TaharezLook/Level1MenuBackground";
		}
		else if(currentName == "level2.scene"){
			levelName = "Level 2";
			bgName = "TaharezLook/Level2MenuBackground";
		}
		else if(currentName == "level3.scene"){
			levelName = "Level 3";
			bgName = "TaharezLook/Level3MenuBackground";
		}
		mWindow->getChild("MenuTitle")->setText(levelName);
		mWindow->getChild("Background")->setProperty("Image",bgName);
	}
}