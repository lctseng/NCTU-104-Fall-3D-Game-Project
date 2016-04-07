#include "NCTUObstacleManager.h"

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
	return obj;
}

void ObstacleManager::setPlayerFloorCallback(btCollisionWorld::ContactResultCallback& callback){
	assert(mFloorObstacle != nullptr);
	assert(mPlayerObstacle != nullptr);
	mWorld->getBulletCollisionWorld()->contactPairTest(mPlayerObstacle->getBody()->getBulletObject(),mFloorObstacle->getBody()->getBulletObject(),callback);
}
void ObstacleManager::setPlayerAllObstacleCallback(btCollisionWorld::ContactResultCallback& callback){
	assert(mPlayerObstacle != nullptr);
	for(unsigned i=0;i<mObstacles.size();i++){
		mWorld->getBulletCollisionWorld()->contactPairTest(mPlayerObstacle->getBody()->getBulletObject(),mObstacles[i]->getBody()->getBulletObject(),callback);	
	}
}

void ObstacleManager::updateCollision(const FrameEvent& evt){
	if(mPlayerObstacle){
		mPlayerObstacle->updateCollision(evt);
	}
}