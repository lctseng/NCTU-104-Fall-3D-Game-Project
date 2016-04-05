#include "NCTUObstacleManager.h"
#include "NCTUFloorObstacle.h"

using namespace NCTU;
using namespace Ogre;

/*!
	\brief Create a plane with Ogre3D and Bullet
*/
FloorObstacle::FloorObstacle(ObstacleManager* mgmt,Real restitution, Real friction,const Vector3& normal,Real distance)
	:Obstacle(mgmt,restitution,friction,0.0f),mPlane(normal,distance)
{
	// store params
	mNormal = normal;
	mDistance = distance;
	// Create Ogre object
	MeshManager::getSingleton().createPlane(
		"obstacle.floor",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		mPlane,
		1500000,1500000, // width, height
		250,250, // x- and y-segments
		true, // normal
		1, // num texture sets
		1000,1000, // x- and y-tiles
		Vector3::UNIT_Z // upward vector
		); 
	// plane entity
	mEntity = mManager->getSceneMgr()->createEntity(
				"floorEntity", "obstacle.floor"); 
	mNode = mManager->getSceneMgr()		
		->getRootSceneNode()
		->createChildSceneNode();
	mNode->attachObject(mEntity); 
	// create bullet object
	mShape = new OgreBulletCollisions::StaticPlaneCollisionShape(normal, distance); // (normal vector, distance)
	mBody = new OgreBulletDynamics::RigidBody(
			"floor",
			mManager->getWorld());
	mBody->setStaticShape(mShape, mFriction, mRestitution); // (shape, restitution, friction)
	mBody->getBulletObject()->setUserPointer(this);
}