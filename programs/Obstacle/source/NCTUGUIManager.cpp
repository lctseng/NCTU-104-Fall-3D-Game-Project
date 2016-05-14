#include "NCTUGUIManager.h"


using namespace NCTU;

GUIManager::GUIManager()
:mRenderer(nullptr),
mConsole(nullptr)
{
	
}
GUIManager::~GUIManager()
{
	if(mConsole){
		delete mConsole;
		mConsole = nullptr;
	}
	if(mMainMenu){
		delete mMainMenu;
		mMainMenu = nullptr;
	}
	if(mGameMenu){
		delete mGameMenu;
		mGameMenu = nullptr;
	}
	CEGUI::WindowManager::getSingleton().destroyAllWindows();
	CEGUI::OgreRenderer::destroySystem();
	
}


void GUIManager::setup(BasicTutorial_00* appPtr){
	mApp = appPtr;
	// Renderer
	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
	// Resource
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	// Scehme
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	// Mouse
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	// Window Root
	CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().createWindow( "DefaultWindow", "_MasterRoot" );
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow( myRoot );
}

void GUIManager::createConsole(){
	mConsole = new GameConsoleWindow();
	mConsole->setApp(mApp);
	mConsole->setup();
}

void GUIManager::createMainMenu(){
	mMainMenu = new MainMenuWindow();
	mMainMenu->setApp(mApp);
	mMainMenu->setup();
}
void GUIManager::createGameMenu(){
	mGameMenu = new GameMenuWindow();
	mGameMenu->setApp(mApp);
	mGameMenu->setup();
}

void GUIManager::createAllWindow(){
	createMainMenu();
	createGameMenu();
	mMainMenu->setVisible(true);
}



bool GUIManager::keyPressed( const OIS::KeyEvent &arg )
{
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	context.injectKeyDown((CEGUI::Key::Scan)arg.key);
	context.injectChar((CEGUI::Key::Scan)arg.text);
	return true;
}

bool GUIManager::keyReleased( const OIS::KeyEvent &arg )
{
	return CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)arg.key);
}

CEGUI::MouseButton GUIManager::convertButton(OIS::MouseButtonID buttonID)
{
	switch (buttonID)
	{
	case OIS::MB_Left:
		return CEGUI::LeftButton;
		break;

	case OIS::MB_Right:
		return CEGUI::RightButton;
		break;

	case OIS::MB_Middle:
		return CEGUI::MiddleButton;
		break;

	default:
		return CEGUI::LeftButton;
		break;
	}
}

bool GUIManager::mouseMoved( const OIS::MouseEvent &arg )
{
	return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
}

bool GUIManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
}

bool GUIManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
}

void GUIManager::update(double timestep){
	CEGUI::System::getSingleton().injectTimePulse(timestep);
}