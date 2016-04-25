//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"
#include <iostream>

using namespace Ogre;
using namespace std;
using namespace OgreBulletCollisions;





BasicTutorial_00::BasicTutorial_00(void) {
	// [NEW]
	mObstacleMgr = new NCTU::ObstacleManager();
	mInitVelocity = Vector3(700,0,0);
	mInitPosition = Vector3( -1000, 50, 0 );
	mEnableCollision = true;
	mEnableFreeMode = false;
	mDisableLose = false;
	mCameraInitLookAt = Vector3(-1000,150,0);
	mCameraInitPosition = Vector3(-1600,350,0);

	// ------
	//[KEYBOARD]
	keyboardhandler = new KeyBoardHandler();
}

BasicTutorial_00::~BasicTutorial_00(void) {
	// [NEW]
	delete keyboardhandler;
	delete mObstacleMgr;

}

void BasicTutorial_00::createCamera(void){
	BaseApplication::createCamera();
}


void BasicTutorial_00::createScene(void) 
{
	// [NEW]
	mObstacleMgr->setup(
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
	NCTU::FloorObstacle* floor = mObstacleMgr->createFloor(
		Vector3::UNIT_Y, // normal
		0, // distance
		0.1f, // restitution
		0.3f // friction
		);
	floor->getEntity()->setMaterialName("Examples/BeachStones");
	// -----------


	mDotScene.parseDotScene("test.scene",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,mSceneMgr,mObstacleMgr);
	// player setup
	mPlayerObstacle = mObstacleMgr->getPlayer();
	// apply general props
	propMap& props = mDotScene.mGeneralProps;
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
	mPlayerObstacle->setVelocity(mInitVelocity);
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
	
}
bool BasicTutorial_00::frameStarted(const FrameEvent &evt)
{
	bool ret = BaseApplication::frameStarted(evt);
	// [NEW]
	processUnbufferedKeyInput(evt); // Process keys, go into functions
	// [NEW]
	mObstacleMgr->stepSimulation(evt.timeSinceLastFrame);   // update Physics animation
	if(!mEnableFreeMode){
		// [NEW]
		updateLightPosition(evt);
		// [NEW]
		updateCameraPosition(evt);
		// [NEW]
		equalizeSpeed(evt);
	}
	// [NEW]
	if(mEnableCollision){
		checkCollision(evt);
	}



	return ret;
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
	if(mPlayerObstacle->getVelocity().y <= -150.0f){
		mCamera->setNearClipDistance(mNearClipMin);	
	}
	else{
		mCamera->setNearClipDistance(mNearClipMax);
	}
	//cout << mPlayerObstacle->getVelocity() << endl;
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
void BasicTutorial_00::checkCollision(const FrameEvent& evt){
	// this is essential to update all collision information
	mObstacleMgr->updateCollision(evt);

	// when we bump into obstacle
	if(mPlayerObstacle->IsBumpObstacle() ){
		if(!mDisableLose){
			mPlayerObstacle->setVelocity(mInitVelocity);
			mPlayerObstacle->setPosition(mInitPosition);
		}
		
	}
}

// [NEW]
bool BasicTutorial_00::processUnbufferedKeyInput(const FrameEvent& evt)
{

	static Real timeUntilNextToggle = 0.0f;
	timeUntilNextToggle += evt.timeSinceLastFrame;
	static Real speed_rate = 40.0f;
	Vector3 frontDir =  mCamera->getDerivedDirection();
	Vector3 currentVel = mPlayerObstacle->getVelocity();
	frontDir.y = 0;
	frontDir.normalise();
	static Vector3 upVector = Vector3::UNIT_Y;

	// toggle settings

	if(keyboardhandler->isKeyPressing(OIS::KC_F7) && timeUntilNextToggle > 0.2f){
		timeUntilNextToggle = 0.0f;
		mEnableCollision = !mEnableCollision;
	}
	if(keyboardhandler->isKeyPressing(OIS::KC_F9) && timeUntilNextToggle > 0.2f){
		timeUntilNextToggle = 0.0f;
		mEnableFreeMode = !mEnableFreeMode;
	}
	if(keyboardhandler->isKeyTriggered(OIS::KC_F11)){
		mDisableLose = !mDisableLose;
	}
	static Real playerScaleFactor = 50.0f;
	if(keyboardhandler->isKeyPressing(OIS::KC_Z) && mPlayerObstacle->isSlideEnable()){
		mPlayerObstacle->setSliding(true);
	}
	else{
		mPlayerObstacle->setSliding(false);
	}
	if(keyboardhandler->isKeyPressing(OIS::KC_F8) && timeUntilNextToggle > 0.5f){
		timeUntilNextToggle = 0.0f;
		mPlayerObstacle->setVelocity(mInitVelocity);
		mPlayerObstacle->setPosition(mInitPosition);
	}
	if(keyboardhandler->isKeyTriggered(OIS::KC_SPACE) && mPlayerObstacle->isJumpEnable() ){
		timeUntilNextToggle = 0.0f;
		Vector3 finalV = mPlayerObstacle->getVelocity();
		finalV[1] = speed_rate * 35.0f;
		mPlayerObstacle->setVelocity(finalV);
		//mPlayerObstacle->applyVelocityChange(Vector3(0,speed_rate * 35,0));
	}
	if(mEnableFreeMode){
		if(keyboardhandler->isKeyPressing(OIS::KC_I) && timeUntilNextToggle > 0.1f){
			timeUntilNextToggle = 0.0f;
			mPlayerObstacle->applyVelocityChange(frontDir * speedAdjustment(currentVel,frontDir) * speed_rate);
		}
		if(keyboardhandler->isKeyPressing(OIS::KC_K) && timeUntilNextToggle > 0.1f){
			timeUntilNextToggle = 0.0f;
			Vector3 goDir = frontDir * -1;
			mPlayerObstacle->applyVelocityChange(goDir * speed_rate * speedAdjustment(currentVel,goDir));
		}
		if(keyboardhandler->isKeyPressing(OIS::KC_J) && timeUntilNextToggle > 0.1f){
			timeUntilNextToggle = 0.0f;
			Vector3 goDir = upVector.crossProduct(frontDir);
			mPlayerObstacle->applyVelocityChange(goDir * speed_rate * speedAdjustment(currentVel,goDir));
		}
		if(keyboardhandler->isKeyPressing(OIS::KC_L) && timeUntilNextToggle > 0.1f){
			timeUntilNextToggle = 0.0f;
			Vector3 goDir = upVector.crossProduct(frontDir) * -1;
			mPlayerObstacle->applyVelocityChange(goDir * speed_rate * speedAdjustment(currentVel,goDir));
		}
	}
	if(keyboardhandler->isKeyPressing(OIS::KC_O) && timeUntilNextToggle > 0.1f){
		timeUntilNextToggle = 0.0f;
		speed_rate += 1.0f;
		Ogre::LogManager::getSingleton().logMessage("[DEMO] Player Speed Rate: " + StringConverter::toString(speed_rate));
		mCamera->setNearClipDistance(speed_rate);
	}
	if(keyboardhandler->isKeyPressing(OIS::KC_P) && timeUntilNextToggle > 0.1f){
		timeUntilNextToggle = 0.0f;
		speed_rate -= 1.0f;
		if(speed_rate < 0.0f){
			speed_rate = 0.0;	
		}
		mCamera->setNearClipDistance(speed_rate);
		Ogre::LogManager::getSingleton().logMessage("[DEMO] Player Speed Rate: " + StringConverter::toString(speed_rate));
	}


	if(keyboardhandler->isKeyPressing(OIS::KC_B) && timeUntilNextToggle > 0.1f)
	{
		Real mass = 10.0f;
		if(keyboardhandler->isKeyPressing(OIS::KC_N)){
			mass = 0.0f;
		}

		timeUntilNextToggle = 0.0f;
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



	if(keyboardhandler->isKeyPressing(OIS::KC_V) && timeUntilNextToggle > 0.1f)
	{
		timeUntilNextToggle = 0.0f;

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

	return true;
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

	return BaseApplication::keyPressed(arg);
}

//[KEYBOARD]
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg ){
	keyboardhandler->keyReleased(arg);

	return BaseApplication::keyReleased(arg);

}