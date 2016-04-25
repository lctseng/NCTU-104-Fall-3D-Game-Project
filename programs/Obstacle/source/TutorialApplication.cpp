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
	//mCameraInitLookAt = Vector3(-1000,0,0);
	//mCameraInitPosition = Vector3(-1000,250,3200);
	mCameraInitLookAt = Vector3(-1000,150,0);
	mCameraInitPosition = Vector3(-1600,350,0);
	mCameraLookAtOffset = mCameraInitLookAt - mInitPosition;
	mCameraPositionOffset = mCameraInitPosition - mInitPosition;

	// ------
	//[KEYBOARD]
	keyboardhandler = new KeyBoardHandler();
}

BasicTutorial_00::~BasicTutorial_00(void) {
	// [NEW]
	delete mObstacleMgr;
}

void BasicTutorial_00::createCamera(void){
	BaseApplication::createCamera();
	// set offset
	mCamera->setPosition(mCameraInitPosition);
	mCamera->lookAt(mCameraInitLookAt);

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

	/*
	// [NEW] Loops for create lots of obstacle
	srand(time(0));
	int nextX = 350;
	for(int i=0;i<20;i++){
		Vector3 position;
		Vector3 size;
		String material;
		std::deque<std::pair<Ogre::Vector3,Ogre::Real> > conditionVectors;
		switch(rand() %4){
		case 0: case 1: // normal box
			position = Vector3(nextX,100,0);
			size = Vector3(100,200,200);
			material = "Examples/BumpyMetal";
			nextX += 700;
			conditionVectors.push_back(make_pair(Vector3(-1,0,0),45.0f)); // side
			break;
		case 2: // tall box
			position = Vector3(nextX,375,0);
			size = Vector3(200,600,200);
			material = "Examples/BumpyMetal";
			nextX += 700;
			conditionVectors.push_back(make_pair(Vector3(-1,0,0),45.0f)); // side
			conditionVectors.push_back(make_pair(Vector3(0,-1,0),80.0f)); // bottom
			break;
		case 3: // all dead box
			position = Vector3(nextX,100,0);
			size = Vector3(100,200,200);
			nextX += 700;
			conditionVectors.push_back(make_pair(Vector3(-1,0,0),180.0f)); // all side
		}

		NCTU::CubeObstacle* obstacle = mObstacleMgr->createCube(
			0.0f, // restitution
			0.0f, // friction
			0.0, // mass
			position, // position
			size, // size
			Quaternion(0,0,0,1) // orientation
			);
		if(material.length() > 0){
			obstacle->getEntity()->setMaterialName(material);
		}
		obstacle->mCollisionConditionVectors = conditionVectors;
	}
	*/




	mDotScene.parseDotScene("test.scene",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,mSceneMgr,mObstacleMgr);
	// player setup
	mPlayerObstacle = mObstacleMgr->getPlayer();
	mPlayerObstacle->setVelocity(mInitVelocity);
	mPlayerObstacle->setPosition(mInitPosition);
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
		mCamera->setNearClipDistance(5);	
	}
	else{
		mCamera->setNearClipDistance(400);
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

	/*
	if(mPlayerObstacle->isOnFloor()){
	cout << "On Floor" << endl;
	}
	else{
	cout << "Not On Floor" << endl;
	}
	*/

	/*
	auto* world = mWorld->getBulletCollisionWorld();
	int numManifolds = world->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
	btPersistentManifold* contactManifold =  world->getDispatcher()->getManifoldByIndexInternal(i);
	btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
	btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());
	// check if it's player

	int numContacts = contactManifold->getNumContacts();
	for (int j=0;j<numContacts;j++)
	{
	btManifoldPoint& pt = contactManifold->getContactPoint(j);
	if (pt.getDistance()<0.f)
	{
	const btVector3& ptA = pt.getPositionWorldOnA();
	const btVector3& ptB = pt.getPositionWorldOnB();
	const btVector3& normalOnB = pt.m_normalWorldOnB;
	std::cout << "Collision Body A: " << obA->getCollisionShape()->getName() << std::endl;
	std::cout << "Collision Body B: " << obB->getCollisionShape()->getName() << std::endl;
	}
	}
	}
	*/
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