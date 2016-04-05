#include "NCTUObstacleCommon.h"
#include "NCTUObstacleManager.h"
#include "NCTUPlayerObstacle.h"

using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;

PlayerObstacle::PlayerObstacle(ObstacleManager* mgmt,Real restitution, Real friction, Real mass)
	:Obstacle(mgmt,restitution,friction,mass),mIsSliding(false)
{
	// some default settings
	Real radius = 50.0f;
	Vector3 position(0,0,0);
	Quaternion orientation(0,0,0,1);
	// for ogre
	mEntity
		= mManager->getSceneMgr()
		->createEntity( "obstacle.player", "Suzanne.mesh" ); 
	mEntity->setCastShadows(true);
	mNode
		= mManager->getSceneMgr()
		->getRootSceneNode()
		->createChildSceneNode( 
		"playerNode", position ); 
	mNode->scale(radius,radius,radius);
	mNode->attachObject( mEntity );
	mEntity->setMaterialName("Bullet/Ball");
	// for bullet
	mShape = new OgreBulletCollisions::SphereCollisionShape(radius);
	mBody = new OgreBulletDynamics::RigidBody(
		"playerRigid",
		mManager->getWorld());
	mBody->setShape(   mNode,
					mShape,
					mRestitution,         // dynamic body restitution
					mFriction,         // dynamic body friction
					mMass,          // dynamic bodymass
					position,      // starting position of the box
					orientation);// orientation of the box       
	mBody->getBulletObject()->setUserPointer(this);
}

void PlayerObstacle::setScale(const Ogre::Vector3& v){
	// some default settings
	Real radius = 50.0f;
	mNode->setScale(v * radius);
	mShape->getBulletShape()->setLocalScaling(OgreBtConverter::to(v));
}
void PlayerObstacle::updateCollision(const FrameEvent& evt){
	Obstacle::updateCollision(evt);
	updateFloorCollision(evt);
	updateAllObstacleCollision(evt);
}
void PlayerObstacle::updateFloorCollision(const FrameEvent& evt){
	mOnFloor = false;
	FloorContactResultCallback f_callback(this);
	mManager->setPlayerFloorCallback(f_callback);
}
void PlayerObstacle::updateAllObstacleCollision(const FrameEvent& evt){
	mIsBumpObstacle = false;
	mOnObstaclePlane = false;
	ObstacleContactResultCallback callback(this);
	mManager->setPlayerAllObstacleCallback(callback);
}
void PlayerObstacle::setSliding(bool val){
	mIsSliding = val;
	if(mIsSliding){
		setScale(Vector3(0.5,0.5,0.5));
		//Vector3 finalPos = getPosition();
		//finalPos[1] -= 50.0f;
		//setPosition(finalPos);
	}
	else{
		setScale(Vector3(1,1,1));
	}
}

bool PlayerObstacle::isJumpEnable(){
	return ( isOnFloor() || IsOnObstaclePlane()) && !isSliding() ;
}
bool PlayerObstacle::isSlideEnable(){
	return mNode->getPosition()[1] <= 55.0f;
}
