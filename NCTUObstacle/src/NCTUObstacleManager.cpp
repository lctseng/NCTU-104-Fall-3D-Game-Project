#include "NCTUObstacleCommon.h"

using namespace Ogre;
using namespace NCTU;
using std::deque;

ObstacleManager::ObstacleManager()
	:mSceneMgr(nullptr),
	mObstacleIndex(0),
	mPlayerObstacle(nullptr),
	mFloorObstacle(nullptr)
{

}
ObstacleManager::~ObstacleManager()
{
	// obstacles
	std::deque<Obstacle *>::iterator it = mObstacles.begin();
	while (mObstacles.end() != it)
	{   
		delete *it;
		++it;
	}
	mObstacles.clear();
	// floor
	if(mFloorObstacle){
		delete mFloorObstacle;
	}
	// player
	if(mPlayerObstacle){
		delete mPlayerObstacle;
	}
	// world
	if(mWorld){
		delete mWorld->getDebugDrawer();
		mWorld->setDebugDrawer(0);
		delete mWorld;
	}
}

void ObstacleManager::setup(Ogre::SceneManager* mgmt,const Ogre::AxisAlignedBox& bound,const Ogre::Vector3 g){
	// param assign
	mSceneMgr = mgmt;
	mBulletBox = bound;
	mGravityVector = g;
	// create others
	mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, mBulletBox, mGravityVector);
	mDebugDrawer = new OgreBulletCollisions::DebugDrawer();
	mDebugDrawer->setDrawWireframe(true);   // we want to see the Bullet containers
	mWorld->setDebugDrawer(mDebugDrawer);
	mWorld->setShowDebugShapes(true);      // enable it if you want to see the Bullet containers
	SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("NCTUObstacle::debugDrawer", Ogre::Vector3::ZERO);
	node->attachObject(static_cast <SimpleRenderable *> (mDebugDrawer));
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
	Real mass)
{
	mPlayerObstacle = new PlayerObstacle(this,restitution,friction,mass);
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
	return obj;
}
void ObstacleManager::setPlayerFloorCallback(btCollisionWorld::ContactResultCallback& callback){
	assert(mFloorObstacle != nullptr);
	assert(mPlayerObstacle != nullptr);
	mWorld->getBulletCollisionWorld()->contactPairTest(mPlayerObstacle->getBody()->getBulletObject(),mFloorObstacle->getBody()->getBulletObject(),callback);
}
void ObstacleManager::setPlayerAllObstacleCallback(btCollisionWorld::ContactResultCallback& callback){
	assert(mPlayerObstacle != nullptr);
	for(int i=0;i<mObstacles.size();i++){
		mWorld->getBulletCollisionWorld()->contactPairTest(mPlayerObstacle->getBody()->getBulletObject(),mObstacles[i]->getBody()->getBulletObject(),callback);	
	}
}