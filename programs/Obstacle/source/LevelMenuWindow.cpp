#include "LevelMenuWindow.h"
#include "TutorialApplication.h"

using namespace NCTU;

LevelMenuWindow::LevelMenuWindow():
GUIWindow("LevelMenu.layout")
{
	
}
void LevelMenuWindow::registerHandlers()
{
	mWindow->getChild("Level1Button")->subscribeEvent(
		CEGUI::PushButton::EventClicked,   
		CEGUI::Event::Subscriber(    
			&LevelMenuWindow::onPressLevel1,
			this));    
	mWindow->getChild("Level2Button")->subscribeEvent(
		CEGUI::PushButton::EventClicked,   
		CEGUI::Event::Subscriber(    
			&LevelMenuWindow::onPressLevel2,
			this));          
	mWindow->getChild("Level3Button")->subscribeEvent(
		CEGUI::PushButton::EventClicked,   
		CEGUI::Event::Subscriber(    
			&LevelMenuWindow::onPressLevel3,
			this));          
	mWindow->getChild("CancelButton")->subscribeEvent(
		CEGUI::PushButton::EventClicked,   
		CEGUI::Event::Subscriber(    
			&LevelMenuWindow::onPressCancel,
			this));          
}
bool LevelMenuWindow::onPressLevel1(const CEGUI::EventArgs &e)
{
	mApp->setCurrentLevelName("level1.scene");
	return true;
}
bool LevelMenuWindow::onPressLevel2(const CEGUI::EventArgs &e)
{
	mApp->setCurrentLevelName("level2.scene");
	return true;
}
bool LevelMenuWindow::onPressLevel3(const CEGUI::EventArgs &e)
{
	mApp->setCurrentLevelName("level3.scene");
	return true;
}
bool LevelMenuWindow::onPressCancel(const CEGUI::EventArgs &e)
{
	mApp->exitLevelMenu();
	return true;
}
void LevelMenuWindow::updateDisableState(){
	String currentName = mApp->getCurrentLevelName();
	if(currentName == "level1.scene"){
		mWindow->getChild("Level1Button")->disable();
		mWindow->getChild("Level2Button")->enable();
		mWindow->getChild("Level3Button")->enable();
		mWindow->getChild("CancelButton")->show();
	}
	else if(currentName == "level2.scene"){
		mWindow->getChild("Level1Button")->enable();
		mWindow->getChild("Level2Button")->disable();
		mWindow->getChild("Level3Button")->enable();
		mWindow->getChild("CancelButton")->show();
	}
	else if(currentName == "level3.scene"){
		mWindow->getChild("Level1Button")->enable();
		mWindow->getChild("Level2Button")->enable();
		mWindow->getChild("Level3Button")->disable();
		mWindow->getChild("CancelButton")->show();
	}
	else{
		mWindow->getChild("Level1Button")->enable();
		mWindow->getChild("Level2Button")->enable();
		mWindow->getChild("Level3Button")->enable();
		mWindow->getChild("CancelButton")->hide();
	}
}
void LevelMenuWindow::setVisible(bool visible){
	GUIWindow::setVisible(visible);
	if(visible){
		updateDisableState();
	}
}