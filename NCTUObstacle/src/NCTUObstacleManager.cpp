#include "NCTUObstacleManager.h"
#include "TutorialApplication.h"
#include <iostream>

using namespace Ogre;
using namespace NCTU;
using namespace std;

ObstacleManager::ObstacleManager()
	:mSceneMgr(nullptr),
	mObstacleIndex(0),
	mPlayerObstacle(nullptr),
	mFloorObstacle(nullptr),
	mScoreHandler(nullptr),
	mApp(nullptr)
{

}
ObstacleManager::~ObstacleManager()
{
	removeAllObstacles();
	removeFloorObstacle();
	removePlayerObstacle();
	// world
	if(mWorld){
		delete mWorld->getDebugDrawer();
		mWorld->setDebugDrawer(0);
		delete mWorld;
	}
}
void ObstacleManager::removeFloorObstacle(){
	// floor
	if(mFloorObstacle){
		delete mFloorObstacle;
		mFloorObstacle = nullptr;
	}
}
void ObstacleManager::removePlayerObstacle(){
	// player
	if(mPlayerObstacle){
		delete mPlayerObstacle;
		mPlayerObstacle = nullptr;
	}
}
void ObstacleManager::removeAllObstacles(){
	std::list<Obstacle *>::iterator it = mObstacles.begin();
	while (mObstacles.end() != it)
	{   
		delete *it;
		++it;
	}
	mObstacles.clear();
	mBullets.clear();
	mPickups.clear();
}

void ObstacleManager::setup(BasicTutorial_00* app,Ogre::SceneManager* mgmt,const Ogre::AxisAlignedBox& bound,const Ogre::Vector3 g){
	// param assign
	mApp = app;
	mSceneMgr = mgmt;
	mBulletBox = bound;
	mGravityVector = g;
	// create others
	mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, mBulletBox, mGravityVector);
	mDebugDrawer = new OgreBulletCollisions::DebugDrawer();
	mDebugDrawer->setDrawWireframe(true);   // we want to see the Bullet containers
	mWorld->setDebugDrawer(mDebugDrawer);
	mWorld->setShowDebugShapes(false);      // enable it if you want to see the Bullet containers
	SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("NCTUObstacle::debugDrawer", Ogre::Vector3::ZERO);
	node->attachObject(static_cast <SimpleRenderable *> (mDebugDrawer));
	// collision register
	btCollisionDispatcher * dispatcher = 
		static_cast<btCollisionDispatcher*>(mWorld->getBulletCollisionWorld()->getDispatcher());
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
}

FloorObstacle* ObstacleManager::createFloor(const Vector3& normal,Real distance,Real restitution, Real friction){
	mFloorObstacle = new FloorObstacle(this,restitution,friction,normal,distance);
	return mFloorObstacle;

}
/* TODO
FloorObstacle* ObstacleManager::createFloor(Plane& plane,Entity* entity,Real restitution, Real friction){
mFloorObstacle = new FloorObstacle(this,restitution,friction,plane,entity);
return mFloorObstacle;
}
*/

PlayerObstacle* ObstacleManager::createPlayer(
	Real restitution,
	Real friction,
	Real mass,
	const String& name,
	Vector3 scale
	)
{
	mPlayerObstacle = new PlayerObstacle(this,restitution,friction,mass,name,scale);
	return mPlayerObstacle;
}

PlayerObstacle* ObstacleManager::createPlayer(
	Real restitution,
	Real friction,
	Real mass,
	SceneNode* node,
	Entity* ent
	)
{
	mPlayerObstacle = new PlayerObstacle(this,restitution,friction,mass,node,ent);
	return mPlayerObstacle;
}

CubeObstacle* ObstacleManager::createCube(
	Real restitution,
	Real friction, 
	Real mass,
	const Vector3& position,
	const Vector3& size,
	const Quaternion& orientation)
{
	CubeObstacle* obj = new CubeObstacle(this,restitution,friction,mass,mObstacleIndex,position,size,orientation);
	++mObstacleIndex;
	mObstacles.push_back(obj);
	obj->setMyIterator(--mObstacles.end());
	return obj;
}


SphereObstacle* ObstacleManager::createSphere(
	Real restitution,
	Real friction, 
	Real mass,
	const Vector3& position,
	Real radius,
	const Quaternion& orientation)
{
	SphereObstacle* obj = new SphereObstacle(this,restitution,friction,mass,mObstacleIndex,position,radius,orientation);
	++mObstacleIndex;
	mObstacles.push_back(obj);
	obj->setMyIterator(--mObstacles.end());
	return obj;
}

BulletObstacle* ObstacleManager::createBullet(
	Real restitution,
	Real friction, 
	Real mass,
	HpType bulletType,
	const Vector3& position,
	Real radius,
	const Quaternion& orientation
	)
{
	BulletObstacle* obj = new BulletObstacle(this,restitution,friction,mass,mObstacleIndex,bulletType,position,radius,orientation);
	++mObstacleIndex;
	mObstacles.push_back(obj);
	obj->setMyIterator(--mObstacles.end());
	mBullets.push_back(obj);
	obj->setBulletIterator(--mBullets.end());
	//cout << "create index:" << mObstacleIndex << endl;
	return obj;
}


GeneralObstacle* ObstacleManager::createGeneralObstacle(
	Real restitution, 
	Real friction, 
	Real mass,
	SceneNode* node,
	Entity* ent
	)
{
	GeneralObstacle* obj = new GeneralObstacle(this,restitution,friction,mass,mObstacleIndex,node,ent);
	++mObstacleIndex;
	mObstacles.push_back(obj);
	obj->setMyIterator(--mObstacles.end());
	return obj;
}

PickupObstacle* ObstacleManager::createPickup(
	SceneNode* node,
	Entity* ent
	)
{
	PickupObstacle* obj = new PickupObstacle(this,mObstacleIndex,node,ent);
	++mObstacleIndex;
	mObstacles.push_back(obj);
	mPickups.push_back(obj);
	obj->setPickupIterator(--mPickups.end());
	obj->setMyIterator(--mObstacles.end());
	return obj;
}

void ObstacleManager::setPlayerFloorCallback(btCollisionWorld::ContactResultCallback& callback){
	assert(mFloorObstacle != nullptr);
	assert(mPlayerObstacle != nullptr);
	mWorld->getBulletCollisionWorld()->contactPairTest(mPlayerObstacle->getBody()->getBulletObject(),mFloorObstacle->getBody()->getBulletObject(),callback);
}
void ObstacleManager::setPlayerAllObstacleCallback(btCollisionWorld::ContactResultCallback& callback){
	assert(mPlayerObstacle != nullptr);
	// obstacles
	std::list<Obstacle *>::iterator it = mObstacles.begin();
	for(;it != mObstacles.end();it++){
		if((*it)->isAlive()){
			mWorld->getBulletCollisionWorld()->contactPairTest(mPlayerObstacle->getBody()->getBulletObject(),(*it)->getBody()->getBulletObject(),callback);	
		}
	}
}
void ObstacleManager::updatePlayerPickupsCollision(const FrameEvent& evt){
	assert(mPlayerObstacle != nullptr);
	// obstacles
	std::list<PickupObstacle *>::iterator it = mPickups.begin();
	for(;it != mPickups.end();it++){
		if((*it)->isAlive()){
			PickupContactResultCallback callback(mPlayerObstacle,*it);
			mWorld->getBulletCollisionWorld()->contactPairTest(mPlayerObstacle->getBody()->getBulletObject(),(*it)->getBody()->getBulletObject(),callback);	
		}
	}
}
void ObstacleManager::updatePickupsEffects(const FrameEvent& evt){
	std::list<PickupObstacle *>::iterator it = mPickups.begin();
	for(;it != mPickups.end();it++){
		if((*it)->isAlive()){
			(*it)->updateEffect(evt);
		}
	}
}

void ObstacleManager::updateCollision(const FrameEvent& evt){
	if(mPlayerObstacle){
		mPlayerObstacle->updateCollision(evt);
	}
}
void ObstacleManager::updateLifeTime(const FrameEvent& evt){
	// obstacles
	std::list<Obstacle *>::iterator it = mObstacles.begin();
	for(;it != mObstacles.end();it++){
		(*it)->updateLifeTime(evt);
	}
	// check erase
	it = mObstacles.begin();
	while(it != mObstacles.end()){
		if((*it)->needDeleted()){
			(*it)->cleanUp();
			// remove this one!
			it = deleteByIterator(it); // auto forward
		}
		else{
			++it;
		}
	}
}
void ObstacleManager::updateBulletCollision(const FrameEvent& evt){
	// set all bullet collision to all object
	std::list<BulletObstacle *>::iterator bullet_it = mBullets.begin();
	for(;bullet_it != mBullets.end();++bullet_it){
		if((*bullet_it)->isAlive()){
			std::list<Obstacle *>::iterator obj_it = mObstacles.begin();
			for(;obj_it != mObstacles.end();++obj_it){
				if(*bullet_it != *obj_it){ // don't set for yourself :)
					if((*obj_it)->isAlive() && (*obj_it)->canBeShoot()){
						BulletContactResultCallback callback(*bullet_it,*obj_it);
						mWorld->getBulletCollisionWorld()->contactPairTest((*bullet_it)->getBody()->getBulletObject(),(*obj_it)->getBody()->getBulletObject(),callback);		
					}
				}
			}
		}
	}
}
void ObstacleManager::stepSimulation(Ogre::Real time){
	mWorld->stepSimulation(time);
}