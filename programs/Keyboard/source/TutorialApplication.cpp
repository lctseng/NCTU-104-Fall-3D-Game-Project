//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"

using namespace Ogre;
BasicTutorial_00::BasicTutorial_00(void) {

	mousetest = new MouseHandler();
}

void BasicTutorial_00::createScene(void) 
{
	mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) ); //bright
	//mSceneMgr->setAmbientLight( ColourValue( 0, 0, 0 ) );  //dark
	mEntity 
		= mSceneMgr
		->createEntity( "Robot", "robot.mesh" ); 

	SceneNode *sNode 
		= mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		"RobotNode", Vector3( 50, 0, 0 ) ); 

	sNode->attachObject( mEntity ); 


	mAnimationState = mEntity->getAnimationState( "Idle" );
	mAnimationState->setLoop( true );
	mAnimationState->setEnabled( true );
}
bool BasicTutorial_00::frameStarted(const FrameEvent &evt)
{
	mAnimationState->addTime(evt.timeSinceLastFrame);
	if ( mKeyboard->isKeyDown(OIS::KC_S) ) {
		mAnimationState = mEntity->getAnimationState( "Walk" );
		mAnimationState->setLoop( true );
		mAnimationState->setEnabled( true );
	}

	mousetest->updateData();
	return true;
}
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg ){

	mousetest->keyPressed(arg);

	return BaseApplication::keyPressed(arg);
}

bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg ){

	mousetest->keyReleased(arg);

	return BaseApplication::keyReleased(arg);
}
