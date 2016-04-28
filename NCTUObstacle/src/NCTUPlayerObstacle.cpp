#include "NCTUObstacleManager.h"
#include "NCTUPlayerObstacle.h"

using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;

PlayerObstacle::PlayerObstacle(ObstacleManager* mgmt,Real restitution, Real friction, Real mass,const String& name, Vector3 scale)
	:Obstacle(mgmt,restitution,friction,mass),mIsSliding(false)
{
	// some default settings
	mScaleDifference = scale;
	Vector3 position(0,0,0);
	Quaternion orientation(0,0,0,1);
	// for ogre
	mEntity
		= mManager->getSceneMgr()
		->createEntity( "obstacle.player", name ); 
	mEntity->setCastShadows(true);
	mNode
		= mManager->getSceneMgr()
		->getRootSceneNode()
		->createChildSceneNode( 
		"playerNode", position ); 
	mNode->scale(scale);
	mNode->attachObject( mEntity );
	mEntity->setMaterialName("Bullet/Ball");
	// for bullet
	mShape = generateFittingShape(mNode,mEntity);
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
PlayerObstacle::PlayerObstacle(ObstacleManager* mgmt,Real restitution, Real friction, Real mass,SceneNode* node, Entity* ent)
:Obstacle(mgmt,restitution,friction,mass),mIsSliding(false)
{
	// create settings
	mScaleDifference = node->getScale();
	Vector3 oldPosition = node->getPosition();
	Vector3 position(0,0,0);
	node->setPosition(0,0,0); // reset position
	Quaternion orientation = node->getOrientation();
	// save node and entity
	mNode = node;
	mEntity = ent;
	mEntity->setCastShadows(true);
	// bullet
	mShape = generateFittingShape(mNode,mEntity);
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
	setPosition(oldPosition);
}
void PlayerObstacle::updateCollision(const FrameEvent& evt){
	Obstacle::updateCollision(evt);
	updateFloorCollision(evt);
	updateAllObstacleCollision(evt);
}
void PlayerObstacle::updateFloorCollision(const FrameEvent& evt){
	setOnFloor(false);
	FloorContactResultCallback f_callback(this);
	mManager->setPlayerFloorCallback(f_callback);
}
void PlayerObstacle::updateAllObstacleCollision(const FrameEvent& evt){
	mIsBumpObstacle = false;
	setIsOnObstaclePlane(false);
	ObstacleContactResultCallback callback(this);
	mManager->setPlayerAllObstacleCallback(callback);
}
void PlayerObstacle::setSliding(bool val){
	mIsSliding = val;
	if(mIsSliding){
		setScale(Vector3(0.5,0.5,0.5));
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
