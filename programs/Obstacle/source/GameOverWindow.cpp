#include "GameOverWindow.h"
#include "TutorialApplication.h"

using namespace NCTU;

GameOverWindow::GameOverWindow():
GUIWindow("GameOver.layout")
{
	
}
void GameOverWindow::registerHandlers()
{
	// MainMenu Button
	mWindow->getChild("MainMenuButton")->subscribeEvent(
		CEGUI::PushButton::EventClicked,   
		CEGUI::Event::Subscriber(    
			&GameOverWindow::onPressMainMenu,
			this));    
	// Exit Button
	mWindow->getChild("ExitButton")->subscribeEvent(
		CEGUI::PushButton::EventClicked,   
		CEGUI::Event::Subscriber(    
			&GameOverWindow::onPressExit,
			this));       
}
bool GameOverWindow::onPressMainMenu(const CEGUI::EventArgs &e)
{
	mApp->backToMainMenu();
	return true;
}
bool GameOverWindow::onPressExit(const CEGUI::EventArgs &e)
{
	mApp->exitGame();
	return true;
}