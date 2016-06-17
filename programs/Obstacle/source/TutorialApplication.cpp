//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"
#include <iostream>

using namespace Ogre;
using namespace NCTU;
using namespace std;
using namespace OgreBulletCollisions;


void onBulletHit(BulletObstacle* bullet,Obstacle* object)
{
	if(object->canBeShoot()){ // works for non-bullet
		if(object->getHpType() == typeBoth  || bullet->getBulletType() == typeBoth || bullet->getBulletType() == object->getHpType()){
			int finalHp = object->decreaseHp();
			if(finalHp > 0){
				switch(object->getHpType()){
				case typeRed:
					Audio::playSE("HitRed.wav");
					bullet->initParticleSystem("Examples/RedFountain",1);
					break;
				case typeBlue:
					Audio::playSE("HitBlue.wav");
					bullet->initParticleSystem("Examples/BlueFountain",1);
					break;
				case typeBoth:
					bullet->initParticleSystem("Examples/PurpleFountain",1);
					Audio::playSE("HitGeneral.wav");
					break;
				}
			}
			else if(finalHp == 0){
				switch(object->getHpType()){
				case typeRed:
					//Audio::playSE("HitRed.wav");
					bullet->initParticleSystem("Examples/SmokeRed",1);
					break;
				case typeBlue:
					//Audio::playSE("HitBlue.wav");
					bullet->initParticleSystem("Examples/SmokeBlue",1);
					break;
				case typeBoth:
					//Audio::playSE("HitGeneral.wav");
					bullet->initParticleSystem("Examples/SmokePurple",1);
					break;
				}
			}
			bullet->setOffParticleSystem(1);

			
		}		
		else{
			// error hit
			bullet->getManager()->getApp()->changeScore(-10);
			cout << "Error bullet color! bullet: "<< bullet->getBulletType() << ", obstacle: " << object->getHpType() << endl;
		}
	}
}

BasicTutorial_00::BasicTutorial_00(void) {
	// [NEW]
	mObstacleMgr = new NCTU::ObstacleManager();
	mInitVelocity = Vector3(700,0,0);
	mInitPosition = Vector3( -1000, 50, 0 );
	mEnableCollision = true;
	mEnableFreeMode = false;
	mDisableLose = false;
	mGameStarted = false;
	mGameOvered = false;

	mBulletSpeedFactor = 1000.0f;
	mBulletLifeTime = 1.0f;
	mAirJumpSpeed = 800.0f;
	mAirJumpMax = 5;
	mAirJumpLeft = mAirJumpMax;
	mGamePaused = true;
	mSpeedRate = 40.0f;
	mPauseTimeIntervalMax = 0.5f;
	mPauseTimeInterval = 0.0f;
	mScore = 0;
	mTimeScoreTemp = 0.0f;
	mTimeElapsed = 0.0;
	currentDirection = DIRECTION_FRONT;
	mCurrentBGM = "Level.wav";
	// ------
	//[KEYBOARD]
	keyboardhandler = new KeyBoardHandler();
	// [Bullet]
	NCTU::BulletObstacle::setHandlerBulletHit(onBulletHit);
	// [GUI]
	mGUI = new NCTU::GUIManager();
	// [Camera]
	mCameraCtrl = new NCTUCamera();
}

BasicTutorial_00::~BasicTutorial_00(void) {
	// [NEW]
	delete keyboardhandler;
	delete mObstacleMgr;
	delete mGUI;
	delete mCameraCtrl;
}

void BasicTutorial_00::createCamera(void){
	BaseApplication::createCamera();
}


void BasicTutorial_00::loadLevelFromScene(const String& sceneName){
	mDotScene.parseDotScene(sceneName,ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,mSceneMgr,mObstacleMgr);
	// player setup
	mPlayerObstacle = mObstacleMgr->getPlayer();
	// apply general props
	propMap<String,GeneralProperty>& props = mDotScene.mGeneralProps;
	// setup init velocity
	if(props.hasKey("InitVelocityX")){
		mInitVelocity.x = props["InitVelocityX"].valFloat;
	}
	if(props.hasKey("InitVelocityY")){
		mInitVelocity.y = props["InitVelocityY"].valFloat;
	}
	if(props.hasKey("InitVelocityZ")){
		mInitVelocity.z = props["InitVelocityZ"].valFloat;
	}
	mDirectionVectors[DIRECTION_FRONT] = mInitVelocity;
	mDirectionVectors[DIRECTION_BACK] = mInitVelocity * -1;
	mDirectionVectors[DIRECTION_LEFT] = mInitVelocity.crossProduct(Vector3(0,-1,0));
	mDirectionVectors[DIRECTION_RIGHT] = mInitVelocity.crossProduct(Vector3(0,1,0));

	//mPlayerObstacle->setVelocity(mInitVelocity);
	// setup init position
	if(props.hasKey("InitPositionX")){
		mInitPosition.x = props["InitPositionX"].valFloat;
	}
	if(props.hasKey("InitPositionY")){
		mInitPosition.y = props["InitPositionY"].valFloat;
	}
	if(props.hasKey("InitPositionZ")){
		mInitPosition.z = props["InitPositionZ"].valFloat;
	}
	mPlayerObstacle->setPosition(mInitPosition);
	// camera clip distance
	if(props.hasKey("CameraClipMin")){
		mCameraCtrl->mNearClipMin = props["CameraClipMin"].valInt;
	}
	if(props.hasKey("CameraClipMax")){
		mCameraCtrl->mNearClipMax = props["CameraClipMax"].valInt;
	}
	// camera position
	if(props.hasKey("CameraInitLookAtX")){
		mCameraCtrl->mCameraInitLookAt.x = props["CameraInitLookAtX"].valInt;
	}
	if(props.hasKey("CameraInitLookAtY")){
		mCameraCtrl->mCameraInitLookAt.y = props["CameraInitLookAtY"].valInt;
	}
	if(props.hasKey("CameraInitLookAtZ")){
		mCameraCtrl->mCameraInitLookAt.z = props["CameraInitLookAtZ"].valInt;
	}
	if(props.hasKey("CameraInitPositionX")){
		mCameraCtrl->mCameraInitPosition.x = props["CameraInitPositionX"].valInt;
	}
	if(props.hasKey("CameraInitPositionY")){
		mCameraCtrl->mCameraInitPosition.y = props["CameraInitPositionY"].valInt;
	}
	if(props.hasKey("CameraInitPositionZ")){
		mCameraCtrl->mCameraInitPosition.z = props["CameraInitPositionZ"].valInt;
	}
	mCameraCtrl->mCameraLookAtOffset = mCameraCtrl->mCameraInitLookAt - mInitPosition;
	mCameraCtrl->mCameraPositionOffset = mCameraCtrl->mCameraInitPosition - mInitPosition;
	mCameraCtrl->setupCamera();

	// sky
	if(props.hasKey("SkyType") && props.hasKey("SkyName")){
		if(props["SkyType"].valStr == "Dome"){
			mSceneMgr->setSkyDome(true, props["SkyName"].valStr, 5, 8);
		}
		else if(props["SkyType"].valStr == "Box"){
			mSceneMgr->setSkyBox(true, props["SkyName"].valStr);
		}
	}
	// floor material
	if(props.hasKey("GroundMaterialName")){
		mFloor->getEntity()->setMaterialName(props["GroundMaterialName"].valStr);
	}
	// bullet
	if(props.hasKey("BulletLifeTime")){
		mBulletLifeTime = 	props["BulletLifeTime"].valFloat;
	}
	if(props.hasKey("BulletSpeedFactor")){
		mBulletSpeedFactor = mInitVelocity.length() * props["BulletSpeedFactor"].valFloat;
	}
	else{
		mBulletSpeedFactor = mInitVelocity.length() * 5;	
	}
	// air jump 
	if(props.hasKey("AirJumpSpeed")){
		mAirJumpSpeed = props["AirJumpSpeed"].valFloat;
	}
	if(props.hasKey("AirJumpMax")){
		mAirJumpMax = props["AirJumpMax"].valInt;
	}
	// record init orientation
	mInitOrientation = mPlayerObstacle->getOrientation();

}

void BasicTutorial_00::createScene(void) 
{
	// [Camera]
	mCameraCtrl->setup(mCamera,mSceneMgr,this);
	// [GUI]
	mGUI->setup(this);
	mGUI->createAllWindow();

	// [NEW]
	mObstacleMgr->setup(
		this,
		mSceneMgr,
		AxisAlignedBox ( //aligned box for Bullet
		Ogre::Vector3 (-10000, -10000, -10000), 
		Ogre::Vector3 (10000,  10000,  10000)),
		Vector3(0,-9.81 * 400,0) // Gravity
		);
	// -----------
	mSceneMgr->setAmbientLight( ColourValue( 0.8, 0.8, 0.8 ) ); //bright
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE); 
	//Lights
	mLight = mSceneMgr->createLight("Light1"); 
	mLight->setType(Light::LT_POINT); 
	mLight->setPosition(Vector3(100, 3000, 250)); 
	mLight->setDiffuseColour(0.8, 0.8, 0.8);		
	mLight->setSpecularColour(1.0, 1.0, 1.0);	
	mLightOffset = mLight->getPosition() - mInitPosition;

	// [NEW]
	// create a plane (floor)
	// plane
	mFloor = mObstacleMgr->createFloor(
		Vector3::UNIT_Y, // normal
		0, // distance
		0.1f, // restitution
		0.3f // friction
		);
	// -----------
	loadLevelFromScene("");
	NCTU::Audio::playBGM("Menu.wav");
}

void BasicTutorial_00::updateBasic(const FrameEvent &evt){
	BaseApplication::frameStarted(evt);
	mGUI->update(evt.timeSinceLastFrame);
	if(!mEnableFreeMode){
		updateLightPosition(evt);
		mCameraCtrl->updateBasic(evt);		
		equalizeSpeed(evt);
	}
	fixOrientation(evt);
	//keyboardhandler->updateData();
	processInputBasic(evt);
}

void BasicTutorial_00::updatePlayingGame(const FrameEvent &evt){
	mCameraCtrl->updatePlayingGame(evt);
	mObstacleMgr->stepSimulation(evt.timeSinceLastFrame);   // update Physics animation
	fixOrientation(evt);
	mObstacleMgr->updateLifeTime(evt);
	mPlayerObstacle->updatePlayingGame(evt);
	mObstacleMgr->updateBulletCollision(evt);
	mObstacleMgr->updatePlayerPickupsCollision(evt);
	mObstacleMgr->updatePickupsEffects(evt);
	if(mEnableCollision){
		checkCollision(evt);
	}
	if(mPlayerObstacle->isOnFloor() || mPlayerObstacle->IsOnObstaclePlane()){
		mAirJumpLeft = mAirJumpMax;
	}
	processInputPlayingGame(evt);
	// Score
	if(mPlayerObstacle->isSliding()){
		mTimeScoreTemp += evt.timeSinceLastFrame * 0.2f;
	}
	else{
		mTimeScoreTemp += evt.timeSinceLastFrame;	
	}
	mTimeElapsed += evt.timeSinceLastFrame;
	if(mTimeScoreTemp > 0.2f){
		int pts = mTimeScoreTemp / 0.2f;
		mTimeScoreTemp -= 0.2f * pts;
		mScore += pts;
		refreshScore();
	}
	mGUI->getScoreBar()->drawTime(mTimeElapsed);
}
void BasicTutorial_00::processInputBasic(const FrameEvent& evt){
	if(keyboardhandler->isKeyTriggered(OIS::KC_F7)){
		mEnableCollision = !mEnableCollision;
	}
	if(keyboardhandler->isKeyTriggered(OIS::KC_F9) ){
		mEnableFreeMode = !mEnableFreeMode;
	}
	if(keyboardhandler->isKeyTriggered(OIS::KC_F11)){
		mDisableLose = !mDisableLose;
	}
	if(keyboardhandler->isKeyTriggered(OIS::KC_F8)){
		startGame();
	}
	if(mEnableFreeMode){
		if(keyboardhandler->isKeyPressing(OIS::KC_I)){
			mPlayerObstacle->applyVelocityChange(getFrontDirection() * speedAdjustment(mPlayerObstacle->getVelocity(),getFrontDirection()) * mSpeedRate);
		}
		if(keyboardhandler->isKeyPressing(OIS::KC_K) ){
			Vector3 goDir = getFrontDirection() * -1;
			mPlayerObstacle->applyVelocityChange(goDir * mSpeedRate * speedAdjustment(mPlayerObstacle->getVelocity(),goDir));
		}
		if(keyboardhandler->isKeyPressing(OIS::KC_J) ){
			Vector3 goDir = Vector3::UNIT_Y.crossProduct(getFrontDirection());
			mPlayerObstacle->applyVelocityChange(goDir * mSpeedRate * speedAdjustment(mPlayerObstacle->getVelocity(),goDir));
		}
		if(keyboardhandler->isKeyPressing(OIS::KC_L) ){
			Vector3 goDir = Vector3::UNIT_Y.crossProduct(getFrontDirection()) * -1;
			mPlayerObstacle->applyVelocityChange(goDir * mSpeedRate * speedAdjustment(mPlayerObstacle->getVelocity(),goDir));
		}
	}
	if(keyboardhandler->isKeyTriggered(OIS::KC_O) ){
		mSpeedRate += 1.0f;
		Ogre::LogManager::getSingleton().logMessage("[DEMO] Player Speed Rate: " + StringConverter::toString(mSpeedRate));
		//mCamera->setNearClipDistance(speed_rate);
	}
	if(keyboardhandler->isKeyTriggered(OIS::KC_P) ){
		mSpeedRate -= 1.0f;
		if(mSpeedRate < 1.0f){
			mSpeedRate = 1.0f;	
		}
		mCamera->setNearClipDistance(mSpeedRate);
		Ogre::LogManager::getSingleton().logMessage("[DEMO] Player Speed Rate: " + StringConverter::toString(mSpeedRate));
	}

	if(keyboardhandler->isKeyPressing(OIS::KC_B) )
	{
		Real mass = 10.0f;
		if(keyboardhandler->isKeyPressing(OIS::KC_N)){
			mass = 0.0f;
		}
		NCTU::CubeObstacle* obstacle = mObstacleMgr->createCube(
			0.6f, // restitution
			1.0f, // friction
			mass, // mass
			(mCamera->getDerivedPosition() + mCamera->getDerivedDirection().normalisedCopy() * 500), // position
			Vector3(100,100,100), // size
			Quaternion(0,0,0,1) // orientation
			);        
		obstacle->setVelocity(
			mCamera->getDerivedDirection().normalisedCopy() * 7.0f ); // shooting speed
		if(mKeyboard->isKeyDown(OIS::KC_Z)){
			obstacle->setScale(Vector3(0.5,0.5,0.5));
		}

	}

	if(keyboardhandler->isKeyPressing(OIS::KC_V) )
	{

		Real mass = 10.0f;
		if(keyboardhandler->isKeyPressing(OIS::KC_N)){
			mass = 0.0f;
		}
		NCTU::SphereObstacle* obstacle = mObstacleMgr->createSphere(
			0.6f, // restitution
			1.0f, // friction
			mass, // mass
			(mCamera->getDerivedPosition() + mCamera->getDerivedDirection().normalisedCopy() * 500), // position
			40.0f, // radius
			Quaternion(0,0,0,1) // orientation
			);        
		obstacle->setVelocity(
			mCamera->getDerivedDirection().normalisedCopy() * 7.0f ); // shooting speed
		obstacle->getEntity()->setMaterialName("Bullet/Capsule");
		if(keyboardhandler->isKeyPressing(OIS::KC_Z)){
			obstacle->setScale(Vector3(0.5,0.5,0.5));
		}
	}



}
void BasicTutorial_00::processInputPlayingGame(const FrameEvent& evt){
	if(!mEnableFreeMode){
		if(keyboardhandler->isKeyTriggered(OIS::KC_LEFT) && mCameraCtrl->isTurnOK() && mPlayerObstacle->isTurnOK(turnLeft)){
			currentDirection -= 1;
			if(currentDirection < 0){
				currentDirection = 3;
			}
			mCameraCtrl->TurnCamera(turnLeft,mPlayerObstacle->getPosition());
			mPlayerObstacle->onTurn(turnLeft);
			mPlayerObstacle->setOrientation(mInitOrientation);
			mPlayerObstacle->getSceneNode()->yaw(Degree(90));
			mInitOrientation = mPlayerObstacle->getOrientation();
			fixOrientation(evt);
		}
		if(keyboardhandler->isKeyTriggered(OIS::KC_RIGHT) && mCameraCtrl->isTurnOK() && mPlayerObstacle->isTurnOK(turnRight)){
			currentDirection += 1;
			if(currentDirection > 3){
				currentDirection = 0;
			}
			mCameraCtrl->TurnCamera(turnRight,mPlayerObstacle->getPosition());
			mPlayerObstacle->onTurn(turnRight);
			mPlayerObstacle->setOrientation(mInitOrientation);
			mPlayerObstacle->getSceneNode()->yaw(Degree(-90));
			mInitOrientation = mPlayerObstacle->getOrientation();
			fixOrientation(evt);
		}
	}
	if(keyboardhandler->isKeyPressing(OIS::KC_Z)){
		mPlayerObstacle->requireSlide(true);
	}
	else{
		//mPlayerObstacle->requireSlide(false);
	}
	if(mPlayerObstacle->isJumpEnable() && keyboardhandler->isKeyTriggered(OIS::KC_SPACE)){
		mPlayerObstacle->performJump();

	}


	if(keyboardhandler->isKeyTriggered(OIS::KC_X) && !mPlayerObstacle->isSliding()){
		Vector3 shoot_v = mPlayerObstacle->getVelocity().normalisedCopy() * 2 ;
		shoot_v.y = 0.0f;
		NCTU::BulletObstacle* obstacle = mObstacleMgr->createBullet(
			0.6f, // restitution
			1.0f, // friction
			1.0f, // mass
			NCTU::typeRed,
			(mPlayerObstacle->getPosition() - shoot_v * 100) // position
			);     
		//Vector3 shoot_v = mCamera->getDerivedDirection().normalisedCopy() * 2 ;
		shoot_v.y = 0.1f;
		obstacle->setVelocity(
			shoot_v * mBulletSpeedFactor); // shooting speed
		obstacle->getEntity()->setMaterialName("Bullet/Capsule");
		obstacle->setLifeTime(mBulletLifeTime);

	}
	if(keyboardhandler->isKeyTriggered(OIS::KC_C) && !mPlayerObstacle->isSliding() ){
		Vector3 shoot_v = mPlayerObstacle->getVelocity().normalisedCopy() * 2 ;
		shoot_v.y = 0.0f;
		NCTU::BulletObstacle* obstacle = mObstacleMgr->createBullet(
			0.6f, // restitution
			1.0f, // friction
			1.0f, // mass
			NCTU::typeBlue,
			(mPlayerObstacle->getPosition() - shoot_v * 100) // position
			);     
		//Vector3 shoot_v = mCamera->getDerivedDirection().normalisedCopy() * 2 ;
		
		shoot_v.y = 0.1f;
		obstacle->setVelocity(
			shoot_v * mBulletSpeedFactor); // shooting speed
		obstacle->getEntity()->setMaterialName("Bullet/Capsule");
		obstacle->setLifeTime(mBulletLifeTime);
	}
	if(mPauseTimeInterval <= 0.0f && keyboardhandler->isKeyTriggered(OIS::KC_ESCAPE)){
		mPauseTimeInterval = mPauseTimeIntervalMax;
		pauseGame();
	}

}
void BasicTutorial_00::updatePausedGame(const FrameEvent& evt){
	processInputPausedGame(evt);
}

void BasicTutorial_00::processInputPausedGame(const FrameEvent& evt){
	if(mPauseTimeInterval <= 0.0f && keyboardhandler->isKeyTriggered(OIS::KC_ESCAPE) ){
		mPauseTimeInterval = mPauseTimeIntervalMax;
		resumeGame();
	}
}

bool BasicTutorial_00::frameStarted(const FrameEvent &evt)
{
	// update for all case
	updateBasic(evt);
	if(mGameStarted){
		if(mPauseTimeInterval > 0.0f){
			mPauseTimeInterval -= evt.timeSinceLastFrame;
		}
		if(!mGamePaused){
			// Update for playing game
			updatePlayingGame(evt);


		}
		else{
			if(!mGameOvered){// Update for paused game
				updatePausedGame(evt);
			}
			else{
				// Update for overed game
				// Nothing
			}
		}
	}
	return true;
}
// [NEW]
void BasicTutorial_00::updateLightPosition(const FrameEvent& evt){
	mLight->setPosition(mPlayerObstacle->getSceneNode()->getPosition() + mLightOffset);
}

// [NEW]
void BasicTutorial_00::equalizeSpeed(const FrameEvent& evt){
	// speed
	Vector3 currentV = mPlayerObstacle->getVelocity();
	Vector3 finalV = mDirectionVectors[currentDirection];
	finalV[1] = currentV[1];
	mPlayerObstacle->setVelocity(finalV);
}

// [NEW]
void BasicTutorial_00::fixOrientation(const FrameEvent& evt){
	mPlayerObstacle->setOrientation(mInitOrientation);
}

// [NEW]
void BasicTutorial_00::checkCollision(const FrameEvent& evt){
	// this is essential to update all collision information
	mObstacleMgr->updateCollision(evt);

	// when we bump into obstacle
	if(mPlayerObstacle->IsBumpObstacle() ){
		if(!mDisableLose){
			onLoseGame();
		}
		else{
			Audio::playSE("Buzzer.wav");
		}

	}
}

Vector3 BasicTutorial_00::getFrontDirection(){
	Vector3 frontDir =  mCamera->getDerivedDirection();
	frontDir.y = 0;
	frontDir.normalise();
	return frontDir;
}
// [NEW]
Real BasicTutorial_00::speedAdjustment(const Vector3& old,const Vector3& go){
	Real product = old.dotProduct(go);
	if(product <= 0.0f && old.length() > go.length()*5){
		return 5.0f;
	}
	else{
		return 1.0f;
	}

}

//[KEYBOARD]
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg ){
	keyboardhandler->keyPressed(arg);
	mGUI->keyPressed(arg); // GUI
	if(mEnableFreeMode){
		mCameraMan->injectKeyDown(arg);
	}
	return BaseApplication::keyPressed(arg);
}

//[KEYBOARD]
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg ){
	keyboardhandler->keyReleased(arg);
	mGUI->keyReleased(arg); // GUI
	if(mEnableFreeMode){
		mCameraMan->injectKeyUp(arg);
	}
	return BaseApplication::keyReleased(arg);

}
// GUI
bool BasicTutorial_00::mouseMoved( const OIS::MouseEvent &arg )
{
	mGUI->mouseMoved(arg);
	if(mEnableFreeMode){
		mCameraMan->injectMouseMove(arg);
	}
	return BaseApplication::mouseMoved(arg);
}
// GUI
bool BasicTutorial_00::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	mGUI->mousePressed(arg,id);
	return BaseApplication::mousePressed(arg,id);
}
// GUI
bool BasicTutorial_00::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	mGUI->mouseReleased(arg,id);
	return BaseApplication::mouseReleased(arg,id);
}

// Menu Control
void BasicTutorial_00::startGame(){
	// close GUI
	mGUI->getMainMenu()->setVisible(false);
	// start game
	mGameStarted = true;
	mGamePaused = false;
	currentDirection = DIRECTION_FRONT;
	mPlayerObstacle->setVelocity(mDirectionVectors[DIRECTION_FRONT]);
	mPlayerObstacle->setPosition(mInitPosition);
	mPlayerObstacle->resetAction();
	NCTU::Audio::playBGM(mCurrentBGM);
}

void BasicTutorial_00::exitGame(){
	mShutDown = true;
}
void BasicTutorial_00::pauseGame(){
	mGamePaused = true;
	mGUI->getGameMenu()->setVisible(true);
	NCTU::Audio::pauseBGM();
}
void BasicTutorial_00::resumeGame(){
	mGamePaused = false;
	mGUI->getGameMenu()->setVisible(false);
	NCTU::Audio::resumeBGM();
}
void BasicTutorial_00::backToMainMenu(){
	resetGame();
	mGUI->getGameMenu()->setVisible(false);
	mGUI->getGameOver()->setVisible(false);
	mGUI->getMainMenu()->setVisible(true);
	NCTU::Audio::playBGM("Menu.wav");
}
void BasicTutorial_00::resetGame(){
	// score
	mScore = 0;
	mTimeScoreTemp = 0.0f;
	mTimeElapsed = 0.0;
	mGUI->getScoreBar()->reset();
	// system
	mGameStarted = false;
	mGamePaused = true;
	mObstacleMgr->removeAllObstacles();
	mObstacleMgr->removePlayerObstacle();
	mDotScene.destroyDedicatedSceneNodes();
	loadLevelFromScene(getCurrentLevelName());
	mPlayerObstacle->setVelocity(mInitVelocity);
	mPlayerObstacle->setPosition(mInitPosition);
	mPlayerObstacle->resetAction();
}
void BasicTutorial_00::onLoseGame(){
	mGameOvered = true;
	mGamePaused = true;
	mGUI->getGameOver()->setVisible(true);
	Audio::playSE("Dead.wav");
	Audio::playBGM("GameOver.wav");
	mPlayerObstacle->setOffParticleSystem(0);
}

void BasicTutorial_00::refreshScore(){
	mGUI->getScoreBar()->drawScore(mScore);
}


void BasicTutorial_00::changeScore(int val){
	mScore += val;
	if(mScore < 0){
		mScore = 0;
	}
	refreshScore();
}

void BasicTutorial_00::setCurrentLevelName(const String& newLevel){
	// check level
	if(mCurrentLevelName != newLevel){
		mCurrentLevelName = newLevel;
		resetGame();
	}
	exitLevelMenu();
}
void BasicTutorial_00::exitLevelMenu(){
	mGUI->getMainMenu()->setVisible(true);
	mGUI->getLevelMenu()->setVisible(false);
}
void BasicTutorial_00::enterLevelMenu(){
	mGUI->getMainMenu()->setVisible(false);
	mGUI->getLevelMenu()->setVisible(true);
}

void BasicTutorial_00::onPickupGet(){
	changeScore(100);
}