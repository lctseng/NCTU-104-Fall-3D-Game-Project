//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"
#include <iostream>

using namespace Ogre;
using namespace std;


// [NEW]
// collision callbacks
struct FloorContactResultCallback : public btCollisionWorld::ContactResultCallback
{
    btScalar addSingleResult(btManifoldPoint& cp,
        const btCollisionObjectWrapper* colObj0Wrap,
        int partId0,
        int index0,
        const btCollisionObjectWrapper* colObj1Wrap,
        int partId1,
        int index1)
    {
        cout << "collide with floor" << endl;
		return 0;
    }
};



BasicTutorial_00::BasicTutorial_00(void) {
	// [NEW]
	mObstacleMgr = new NCTU::ObstacleManager();
	mInitVelocity = Vector3(300,0,0);
	mInitPosition = Vector3( -1000, 50, 30 );
	// ------
}

BasicTutorial_00::~BasicTutorial_00(void) {
	// [NEW]
	delete mObstacleMgr;
}


void BasicTutorial_00::createScene(void) 
{
	// [NEW]
	mObstacleMgr->setup(
			mSceneMgr,
			AxisAlignedBox ( //aligned box for Bullet
				Ogre::Vector3 (-10000, -10000, -10000), 
                Ogre::Vector3 (10000,  10000,  10000)),
			Vector3(0,-9.81 * 90,0) // Gravity
		);
	// -----------
	mSceneMgr->setAmbientLight( ColourValue( 0.8, 0.8, 0.8 ) ); //bright
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE); 
	//mSceneMgr->setAmbientLight( ColourValue( 0, 0, 0 ) );  //dark

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

	// [NEW]
	// Player
	mPlayerObstacle = mObstacleMgr->createPlayer(
				0.6f, // restitution
				10.0f, // friction
				10.0f // mass
				);
	// set init position and speed
	mPlayerObstacle->setPosition(mInitPosition);
	mPlayerObstacle->setVelocity(mInitVelocity);
	// -----------

	// [NEW]
	//mObstacleMgr->setFloorCallback(new FloorContactResultCallback);
	
	
	// [NEW]
	NCTU::CubeObstacle* obstacle = mObstacleMgr->createCube(
				0.0f, // restitution
				1.0f, // friction
				0.0, // mass
				Vector3(0,100,0), // position
				Vector3(200,200,200), // size
				Quaternion(0,0,0,1) // orientation
				);
	obstacle->getEntity()->setMaterialName("Examples/BumpyMetal");
	// -----------

	Light *light = mSceneMgr->createLight("Light1"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(100, 1200, 250)); 
	light->setDiffuseColour(0.8, 0.8, 0.8);		
	light->setSpecularColour(1.0, 1.0, 1.0);	
}
bool BasicTutorial_00::frameStarted(const FrameEvent &evt)
{
	bool ret = BaseApplication::frameStarted(evt);
	// [NEW]
	processUnbufferedKeyInput(evt); // Process keys, go into functions
	// [NEW]
	mObstacleMgr->stepSimulation(evt.timeSinceLastFrame);   // update Physics animation
	// [NEW]
	checkCollision(evt);	
	


    return ret;
}

// [NEW]
void BasicTutorial_00::checkCollision(const FrameEvent& evt){
	// floor callback
	FloorContactResultCallback callback;
	mObstacleMgr->setFloorCallback(callback);

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



	if(mKeyboard->isKeyDown(OIS::KC_F8) && timeUntilNextToggle > 1.0f){
		timeUntilNextToggle = 0.0f;
		mPlayerObstacle->setVelocity(mInitVelocity);
		mPlayerObstacle->setPosition(mInitPosition);
	}
	if(mKeyboard->isKeyDown(OIS::KC_SPACE) && timeUntilNextToggle > 0.2f){
		timeUntilNextToggle = 0.0f;
		mPlayerObstacle->applyVelocityChange(Vector3(0,speed_rate * 20,0));
	}
	if(mKeyboard->isKeyDown(OIS::KC_I) && timeUntilNextToggle > 0.1f){
		timeUntilNextToggle = 0.0f;
		mPlayerObstacle->applyVelocityChange(frontDir * speedAdjustment(currentVel,frontDir) * speed_rate);
	}
	if(mKeyboard->isKeyDown(OIS::KC_K) && timeUntilNextToggle > 0.1f){
		timeUntilNextToggle = 0.0f;
		Vector3 goDir = frontDir * -1;
		mPlayerObstacle->applyVelocityChange(goDir * speed_rate * speedAdjustment(currentVel,goDir));
	}
	if(mKeyboard->isKeyDown(OIS::KC_J) && timeUntilNextToggle > 0.1f){
		timeUntilNextToggle = 0.0f;
		Vector3 goDir = upVector.crossProduct(frontDir);
		mPlayerObstacle->applyVelocityChange(goDir * speed_rate * speedAdjustment(currentVel,goDir));

	}
	if(mKeyboard->isKeyDown(OIS::KC_L) && timeUntilNextToggle > 0.1f){
		timeUntilNextToggle = 0.0f;
		Vector3 goDir = upVector.crossProduct(frontDir) * -1;
		mPlayerObstacle->applyVelocityChange(goDir * speed_rate * speedAdjustment(currentVel,goDir));

	}
	if(mKeyboard->isKeyDown(OIS::KC_O) && timeUntilNextToggle > 0.1f){
		timeUntilNextToggle = 0.0f;
		speed_rate += 1.0f;
		Ogre::LogManager::getSingleton().logMessage("[DEMO] Player Speed Rate: " + StringConverter::toString(speed_rate));
	}
	if(mKeyboard->isKeyDown(OIS::KC_P) && timeUntilNextToggle > 0.1f){
		timeUntilNextToggle = 0.0f;
		speed_rate -= 1.0f;
		if(speed_rate < 0.0f){
			speed_rate = 0.0;	
		}
		Ogre::LogManager::getSingleton().logMessage("[DEMO] Player Speed Rate: " + StringConverter::toString(speed_rate));
	}

	
	if(mKeyboard->isKeyDown(OIS::KC_B) && timeUntilNextToggle > 0.1f)
	{
		Real mass = 10.0f;
		if(mKeyboard->isKeyDown(OIS::KC_N)){
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
         
	}
	


	if(mKeyboard->isKeyDown(OIS::KC_V) && timeUntilNextToggle > 0.1f)
	{
		timeUntilNextToggle = 0.0f;
     
		Real mass = 10.0f;
		if(mKeyboard->isKeyDown(OIS::KC_N)){
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