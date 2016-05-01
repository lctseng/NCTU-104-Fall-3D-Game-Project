#include "NCTUObstacleManager.h"
#include "NCTUSphereObstacle.h"

using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;

/*!
	\brief Create a sphere obstacle (full)
*/

SphereObstacle::SphereObstacle(
		ObstacleManager* mgmt,
		Real restitution,
		Real friction,
		Real mass,
		INDEX_TYPE index,
		const Vector3& position,
		Real radius,
		const Quaternion& orientation)
	:Obstacle(mgmt,restitution,friction,mass),
	mIndex(index),
	mRadius(radius)
{
	mName = "obstacle.sphere." + StringConverter::toString(mIndex);
	// create ogre objects
	mEntity = mManager->getSceneMgr()->createEntity(
		mName,
		"ellipsoid.mesh");   
	mEntity->setCastShadows(true);

	mNode = mManager->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mEntity);
	mNode->scale(radius,radius,radius);  
	// bullet
	mShape = new OgreBulletCollisions::SphereCollisionShape(radius);
	// and the Bullet rigid body
	mBody = new OgreBulletDynamics::RigidBody(
		mName,
		mManager->getWorld(),COL_GROUP_ALL,COL_MASK_OBSTACLE);

	mBody->setShape(   mNode,
					mShape,
					mRestitution,         // dynamic body restitution
					mFriction,         // dynamic body friction
					mMass,          // dynamic bodymass
					position,      // starting position of the box
					orientation
					);// orientation of the box     
	mBody->getBulletObject()->setUserPointer(this);
	
}
void SphereObstacle::setScale(const Ogre::Vector3& v){
	mNode->setScale(v * mRadius);
	mShape->getBulletShape()->setLocalScaling(OgreBtConverter::to(v));
}
