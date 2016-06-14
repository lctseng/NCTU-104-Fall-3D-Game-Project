#include "NCTUObstacleManager.h"
#include "NCTUPlayerObstacle.h"
#include <iostream>

using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace std;

PlayerObstacle::PlayerObstacle(ObstacleManager* mgmt,Real restitution, Real friction, Real mass,const String& name, Vector3 scale)
	:Obstacle(mgmt,restitution,friction,mass),mIsSliding(false),mSlidingValidTime(0.0f),mJumpCoolDown(0.0f),mParticleTime(0.0f)
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
	// base node and entity
	createBaseEntity();
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
PlayerObstacle::~PlayerObstacle(){
	if(!mEntityDetached){
		mBaseNode->detachObject(mBaseEntity);
	}
	mManager->getSceneMgr()->destroyEntity(mBaseEntity);
	mManager->getSceneMgr()->destroySceneNode(mBaseNode);
}

void PlayerObstacle::detachEntity(){
	Obstacle::detachEntity();
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
	// base node and entity
	createBaseEntity();
	// bullet
	mShape = generatePlayerShape(mNode,mEntity);
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
	initParticleSystem("Examples/GreenyNimbus",0);
	initParticleSystem("Examples/GreenyNimbus",1);
	mAnimationState = mEntity->getAnimationState("Walk");
	if(mAnimationState){
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
	}
}
OgreBulletCollisions::CollisionShape* PlayerObstacle::generatePlayerShape(SceneNode* node, Entity* ent){
	/*
	使用OgreBullet的AnimatedMeshToShapeConverter
	這個物件的作用是輸入Entity取得Mesh的詳細資料，
	便於算出ConvexHull或更複雜的GImpactCollision
	其實用另一個StaticMeshToShapeConverter也行，並不影響結果
	*/
	OgreBulletCollisions::StaticMeshToShapeConverter *converter = 
		new OgreBulletCollisions::StaticMeshToShapeConverter(
		ent, //很單純就載入Entity，裡面會去取得所需要的Mesh資訊
		node->_getFullTransform()); /*載入此Entity的Matrix4，
									也就是取得大小與位置，
									這邊直接用_getFullTransform()從node取得最方便*/

	//使用createConcave產生我們所要的GImpactConcaveShape
	converter->addEntity(mBaseEntity,mBaseNode->_getFullTransform());
	GImpactConcaveShape *shape = converter->createConcave();
	return shape;
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
	// particle system
	if(mParticleTime > 0.0f){
		mParticleTime -= evt.timeSinceLastFrame;
		if(mParticleTime <= 0.0f){
			stopParticleSystem(1);
		}
	}
	if(mAnimationState){
		mAnimationState->addTime(evt.timeSinceLastFrame * 4.0);
	}
	
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
void PlayerObstacle::onPickupGet(){
	setOffParticleSystem(1);
	mParticleTime = 3.0f;
	Audio::playSE("Pickup.wav");
}
void PlayerObstacle::createBaseEntity(){
	mBaseNode = mNode->createChildSceneNode();
	mBaseEntity = mManager->getSceneMgr()
		->createEntity( mName + ".base", "sphere.mesh" ); 
	mBaseNode->attachObject(mBaseEntity);
	mBaseEntity->setVisible(false);
	mBaseNode->scale(0.01,0.01,0.01);
	
}