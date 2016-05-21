#include "NCTUObstacleManager.h"
#include "NCTUPlayerObstacle.h"
#include <iostream>

using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace std;

PlayerObstacle::PlayerObstacle(ObstacleManager* mgmt,Real restitution, Real friction, Real mass,const String& name, Vector3 scale)
	:Obstacle(mgmt,restitution,friction,mass),mIsSliding(false),mSlidingValidTime(0.0f),mJumpCoolDown(0.0f)
{
	mName = "obstacle.player";
	// some default settings
	mScaleDifference = scale;
	Vector3 position(0,0,0);
	Quaternion orientation(0,0,0,1);
	// for ogre
	mEntity
		= mManager->getSceneMgr()
		->createEntity( mName, name ); 
	mEntity->setCastShadows(true);
	mNode
		= mManager->getSceneMgr()
		->getRootSceneNode()
		->createChildSceneNode( 
		mName, position ); 
	mNode->scale(scale);
	mNode->attachObject( mEntity );
	mEntity->setMaterialName("Bullet/Ball");
	// for bullet
	mShape = generateFittingShape(mNode,mEntity);
	mBody = new OgreBulletDynamics::RigidBody(
		mName,
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
	mName = "obstacle.player";
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
		mName,
		mManager->getWorld(),COL_GROUP_NO_BULLET,COL_MASK_PLAYER);
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
	//cout << mSlidingValidTime << endl;
	//cout << "Floor:" << mFloorTouchValue << endl;
	//cout << "Obs:" << mObstaclePlaneTouchValue << endl;
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
void PlayerObstacle::updateSliding(const FrameEvent& evt){
	if(mSlidingValidTime > 0.0f){
		mSlidingValidTime -= evt.timeSinceLastFrame;
	}
	if(isOnFloor(FLOOR_TOUCH_STRICT_THRESHOLD) || IsOnObstaclePlane(OBSTACLE_PLANE_TOUCH_STRICT_THRESHOLD)){
		mSlidingValidTime = 0.2f;
	}
	if(mSlideRequiring && isSlideEnable()){
		setSliding(true);
	}
	else{
		setSliding(false);
	}
}
void PlayerObstacle::updateJumping(const FrameEvent& evt){
	if(mJumpCoolDown > 0.0f){
		mJumpCoolDown -= evt.timeSinceLastFrame;
	}
}
void PlayerObstacle::updatePlayingGame(const Ogre::FrameEvent& evt){
	Obstacle::updatePlayingGame(evt);
	updateSliding(evt);
	updateJumping(evt);
	//cout << "Floor:" << isOnFloor() << endl;
	//cout << "Floor cnt:" << mFloorTouchValue << endl;
	//cout << "Obs:" << IsOnObstaclePlane()<< endl;
	//cout << "Obs cnt:" << mObstaclePlaneTouchValue << endl;
	//cout << "Not Sliding:" << isSliding() << endl;
	//cout << "Time:" << mJumpCoolDown << endl;
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
	return ( isOnFloor() || IsOnObstaclePlane()) && !isSliding() && mJumpCoolDown <= 0.0f ;
}
bool PlayerObstacle::isSlideEnable(){
	return mSlidingValidTime > 0.0f && mJumpCoolDown <= 0.0f;
	//return mNode->getPosition()[1] <= 55.0f;
}

void PlayerObstacle::performJump(){
	// normal jump
	Vector3 finalV = getVelocity();
	finalV[1] = 1400.0f;
	setVelocity(finalV);
	// cancel slide
	mSlidingValidTime = 0.0f;
	mJumpCoolDown = 0.5f;
	// Air jump is deprecated
	//else if(finalV.y < 0.0f && mAirJumpLeft > 0){ // air jump?
	//	finalV[1] += mAirJumpSpeed;
	//	--mAirJumpLeft;
	//	cout << "Air Jump Left: " << mAirJumpLeft << endl;
	//}

	
}
void PlayerObstacle::resetAction(){
	mIsSliding = false;
	mSlidingValidTime = 0.0f;
	mJumpCoolDown = 0.0f;
}

bool PlayerObstacle::isTurnOK(int turn){
	// check obstacle touched or used?
	if(!mCurrentObstacle || mCurrentObstacle->getTurnUsed()){
		return false;
	}
	// check turn type
	switch(turn){
	case turnRight:
		if(mCurrentObstacle->getTurnType() == "Right" || mCurrentObstacle->getTurnType() == "Both"){
			return true;
		}
		break;
	case turnLeft:
		if(mCurrentObstacle->getTurnType() == "Left" || mCurrentObstacle->getTurnType() == "Both"){
			return true;
		}
		break;
	}
	return false;
}
void PlayerObstacle::onTurn(int turn){
	if(mCurrentObstacle){
		mCurrentObstacle->setTurnUsed(true);
		Vector3 finalPos = mCurrentObstacle->getPosition();
		finalPos.y = getPosition().y;
		setPosition(finalPos);
	}
}