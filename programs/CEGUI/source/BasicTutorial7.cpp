/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial7.cpp
-----------------------------------------------------------------------------

This source file is part of the
___                 __    __ _ _    _ 
/___\__ _ _ __ ___  / / /\ \ (_) | _(_)
//  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
|___/                              
Tutorial Framework
http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "BasicTutorial7.h"
#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------------
BasicTutorial7::BasicTutorial7(void)
	: mRenderer(0)
{
}
//-------------------------------------------------------------------------------------
BasicTutorial7::~BasicTutorial7(void)
{
	CEGUI::OgreRenderer::destroySystem();
}

bool BasicTutorial7::Jump(const CEGUI::EventArgs& /*e*/){
	cout << "Jump!!" << endl;
	return true;
}

//-------------------------------------------------------------------------------------
void BasicTutorial7::createScene(void)
{
	// Ogre Native
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, -300));
	headNode->attachObject(ogreHead);

	Ogre::TexturePtr tex = mRoot->getTextureManager()->createManual(
		"RTT",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::TEX_TYPE_2D,
		512,
		512,
		0,
		Ogre::PF_R8G8B8,
		Ogre::TU_RENDERTARGET);
	Ogre::RenderTexture *rtex = tex->getBuffer()->getRenderTarget();

	Ogre::Camera *cam = mSceneMgr->createCamera("RTTCam");
	cam->setPosition(100, -100, -400);
	cam->lookAt(0, 0, -300);
	Ogre::Viewport *v = rtex->addViewport(cam);
	v->setOverlaysEnabled(false);
	v->setClearEveryFrame(true);
	v->setBackgroundColour(Ogre::ColourValue::Black);
	

	// CEGUI
	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
	// Resource
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	// Scehme
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	// Font
	//if(! CEGUI::FontManager::getSingleton().isDefined( "DejaVuSans-10" ) )
	//	CEGUI::FontManager::getSingleton().createFreeTypeFont( "DejaVuSans-10", 1, true, "DejaVuSerif.ttf", "Fonts" );
	//CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont( "DejaVuSans-10" );
	// Mouse
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	// Window Root
	CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().createWindow( "DefaultWindow", "_MasterRoot" );
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow( myRoot );
	// Generate console from layout
	GameConsoleWindow* ptr = new GameConsoleWindow();
	ptr->setVisible(true);

}

void BasicTutorial7::createFrameListener(void)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);
}

bool BasicTutorial7::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(mWindow->isClosed())
		return false;

	if(mShutDown)
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	return true;
}

bool BasicTutorial7::keyPressed( const OIS::KeyEvent &arg )
{
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	context.injectKeyDown((CEGUI::Key::Scan)arg.key);
	context.injectChar((CEGUI::Key::Scan)arg.text);

	if (arg.key == OIS::KC_ESCAPE)
	{
		mShutDown = true;
	}

	mCameraMan->injectKeyDown(arg);
	return true;
}

bool BasicTutorial7::keyReleased( const OIS::KeyEvent &arg )
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)arg.key);
	mCameraMan->injectKeyUp(arg);
	return true;
}

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
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

bool BasicTutorial7::mouseMoved( const OIS::MouseEvent &arg )
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
	return true;
	mCameraMan->injectMouseMove(arg);
	return true;
}

bool BasicTutorial7::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
	return true;
	mCameraMan->injectMouseDown(arg, id);
	return true;
}

bool BasicTutorial7::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
	return true;
	mCameraMan->injectMouseUp(arg, id);
	
}

bool BasicTutorial7::quit(const CEGUI::EventArgs &e)
{
	mShutDown = true;
	return true;
}