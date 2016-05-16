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
	if(!dynamic_cast<NCTU::BulletObstacle*>(object)){ // works for non-bullet
		if(object->getHpType() == typeBoth  || bullet->getBulletType() == typeBoth || bullet->getBulletType() == object->getHpType()){
			object->decreaseHp();
		}		
		else{
			// error hit
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
	mCameraInitLookAt = Vector3(-1000,150,0);
	mCameraInitPosition = Vector3(-1600,350,0);
	mBulletSpeedFactor = 1000.0f;
	mNearClipMin = 5;
	mNearClipMax = 400;
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
	// ------
	//[KEYBOARD]
	keyboardhandler = new KeyBoardHandler();
	// [Bullet]
	NCTU::BulletObstacle::setHandlerBulletHit(onBulletHit);
	// [GUI]
	mGUI = new NCTU::GUIManager();
}

BasicTutorial_00::~BasicTutorial_00(void) {
	// [NEW]
	delete keyboardhandler;
	delete mObstacleMgr;
	delete mGUI;
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
		mNearClipMin = props["CameraClipMin"].valInt;
	}
	if(props.hasKey("CameraClipMax")){
		mNearClipMax = props["CameraClipMax"].valInt;
	}
	mCamera->setNearClipDistance(mNearClipMax);
	// camera position
	if(props.hasKey("CameraInitLookAtX")){
		mCameraInitLookAt.x = props["CameraInitLookAtX"].valInt;
	}
	if(props.hasKey("CameraInitLookAtY")){
		mCameraInitLookAt.y = props["CameraInitLookAtY"].valInt;
	}
	if(props.hasKey("CameraInitLookAtZ")){
		mCameraInitLookAt.z = props["CameraInitLookAtZ"].valInt;
	}
	if(props.hasKey("CameraInitPositionX")){
		mCameraInitPosition.x = props["CameraInitPositionX"].valInt;
	}
	if(props.hasKey("CameraInitPositionY")){
		mCameraInitPosition.y = props["CameraInitPositionY"].valInt;
	}
	if(props.hasKey("CameraInitPositionZ")){
		mCameraInitPosition.z = props["CameraInitPositionZ"].valInt;
	}
	mCameraLookAtOffset = mCameraInitLookAt - mInitPosition;
	mCameraPositionOffset = mCameraInitPosition - mInitPosition;
	mCamera->setPosition(mCameraInitPosition);
	mCamera->lookAt(mCameraInitLookAt);
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
	loadLevelFromScene("test.scene");

	
	
}

void BasicTutorial_00::updateBasic(const FrameEvent &evt){
	BaseApplication::frameStarted(evt);
	mGUI->update(evt.timeSinceLastFrame);
	if(!mEnableFreeMode){
		updateLightPosition(evt);
		updateCameraPosition(evt);
		equalizeSpeed(evt);
	}
	fixOrientation(evt);
	//keyboardhandler->updateData();
	processInputBasic(evt);
}

void BasicTutorial_00::updatePlayingGame(const FrameEvent &evt){
	mObstacleMgr->stepSimulation(evt.timeSinceLastFrame);   // update Physics animation
	mObstacleMgr->updateLifeTime(evt);
	mObstacleMgr->updateBulletCollision(evt);
	if(mEnableCollision){
		checkCollision(evt);
	}
	if(mPlayerObstacle->isOnFloor() || mPlayerObstacle->IsOnObstaclePlane()){
		mAirJumpLeft = mAirJumpMax;
	}
	processInputPlayingGame(evt);
	mCameraMotion.record(mPlayerObstacle->getVelocity());
	// Score
	mTimeScoreTemp += evt.timeSinceLastFrame;
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
	if(keyboardhandler->isKeyPressing(OIS::KC_Z) && mPlayerObstacle->isSlideEnable()){
		mPlayerObstacle->setSliding(true);
	}
	else{
		mPlayerObstacle->setSliding(false);
	}
	if(keyboardhandler->isKeyTriggered(OIS::KC_SPACE)){
		Vector3 finalV = mPlayerObstacle->getVelocity();
		// normal jump?
		if(mPlayerObstacle->isJumpEnable()){
			finalV[1] = mSpeedRate * 35.0f;
		}
		else if(finalV.y < 0.0f && mAirJumpLeft > 0){ // air jump?
			finalV[1] += mAirJumpSpeed;
			--mAirJumpLeft;
			cout << "Air Jump Left: " << mAirJumpLeft << endl;
		}
		mPlayerObstacle->setVelocity(finalV);
		//mPlayerObstacle->applyVelocityChange(Vector3(0,speed_rate * 35,0));
	}


	if(keyboardhandler->isKeyTriggered(OIS::KC_X) ){
		NCTU::BulletObstacle* obstacle = mObstacleMgr->createBullet(
			0.6f, // restitution
			1.0f, // friction
			1.0f, // mass
			NCTU::typeRed,
			(mCamera->getDerivedPosition() + mCamera->getDerivedDirection().normalisedCopy() * 500) // position
			);     
		Vector3 shoot_v = mCamera->getDerivedDirection().normalisedCopy() * 2 ;
		shoot_v.y = 0.3f;
		obstacle->setVelocity(
			shoot_v * mBulletSpeedFactor); // shooting speed
		obstacle->getEntity()->setMaterialName("Bullet/Capsule");
		obstacle->setLifeTime(mBulletLifeTime);
	}
	if(keyboardhandler->isKeyTriggered(OIS::KC_C) ){
		NCTU::BulletObstacle* obstacle = mObstacleMgr->createBullet(
			0.6f, // restitution
			1.0f, // friction
			1.0f, // mass
			NCTU::typeBlue,
			(mCamera->getDerivedPosition() + mCamera->getDerivedDirection().normalisedCopy() * 500) // position
			);     
		Vector3 shoot_v = mCamera->getDerivedDirection().normalisedCopy() * 2 ;
		shoot_v.y = 0.3f;
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
			// Update for paused game
			updatePausedGame(evt);
		}
	}

	return true;
}
// [NEW]
void BasicTutorial_00::updateLightPosition(const FrameEvent& evt){
	mLight->setPosition(mPlayerObstacle->getSceneNode()->getPosition() + mLightOffset);
}
// [NEW]
void BasicTutorial_00::updateCameraPosition(const FrameEvent& evt){
	Vector3 playerPos = mPlayerObstacle->getSceneNode()->getPosition();
	//playerPos[1] = mInitPosition[1];
	mCamera->setPosition(playerPos + mCameraPositionOffset);
	mCamera->lookAt(playerPos + mCameraLookAtOffset);
	// clip
	if(!mGameStarted || mCameraMotion.isDown()){
		mCamera->setNearClipDistance(mNearClipMin);	
	}
	else{
		mCamera->setNearClipDistance(mNearClipMax);
	}
	//cout << mPlayerObstacle->getVelocity() << endl;
	//cout << mCamera->getPosition() << endl;
}

// [NEW]
void BasicTutorial_00::equalizeSpeed(const FrameEvent& evt){
	// speed
	Vector3 currentV = mPlayerObstacle->getVelocity();
	Vector3 finalV = mInitVelocity;
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
	return BaseApplication::keyPressed(arg);
}

//[KEYBOARD]
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg ){
	keyboardhandler->keyReleased(arg);
	mGUI->keyReleased(arg); // GUI
	return BaseApplication::keyReleased(arg);

}
// GUI
bool BasicTutorial_00::mouseMoved( const OIS::MouseEvent &arg )
{
	mGUI->mouseMoved(arg);
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
	// cloose GUI
	mGUI->getMainMenu()->setVisible(false);
	// start game
	mGameStarted = true;
	mGamePaused = false;
	mPlayerObstacle->setVelocity(mInitVelocity);
	mPlayerObstacle->setPosition(mInitPosition);
}

void BasicTutorial_00::exitGame(){
	mShutDown = true;
}
void BasicTutorial_00::pauseGame(){
	mGamePaused = true;
	mGUI->getGameMenu()->setVisible(true);
}
void BasicTutorial_00::resumeGame(){
	mGamePaused = false;
	mGUI->getGameMenu()->setVisible(false);
}
void BasicTutorial_00::backToMainMenu(){
	resetGame();
	mGUI->getGameMenu()->setVisible(false);
	mGUI->getMainMenu()->setVisible(true);
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
	loadLevelFromScene("test.scene");
	mPlayerObstacle->setVelocity(mInitVelocity);
	mPlayerObstacle->setPosition(mInitPosition);
}
void BasicTutorial_00::onLoseGame(){
	mPlayerObstacle->setVelocity(mInitVelocity);
	mPlayerObstacle->setPosition(mInitPosition);
}

void BasicTutorial_00::refreshScore(){
	mGUI->getScoreBar()->drawScore(mScore);
}

