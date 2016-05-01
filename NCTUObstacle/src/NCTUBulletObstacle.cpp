#include "NCTUObstacleManager.h"
#include "NCTUBulletObstacle.h"

using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;

/*!
	\brief Create a bullet obstacle (full)
*/

BulletObstacle::BulletObstacle(
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
	// create ogre objects
	mEntity = mManager->getSceneMgr()->createEntity(
		"obstacle.sphere." + StringConverter::toString(mIndex),
		"ellipsoid.mesh");   
	mEntity->setCastShadows(true);

	mNode = mManager->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mEntity);
	mNode->scale(radius,radius,radius);  
	// bullet
	mShape = new OgreBulletCollisions::SphereCollisionShape(radius);
	// and the Bullet rigid body
	mBody = new OgreBulletDynamics::RigidBody(
		"obstacle.bullet." + StringConverter::toString(mIndex),
		mManager->getWorld(),COL_GROUP_NO_BULLET,COL_MASK_BULLET);

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
void BulletObstacle::setScale(const Ogre::Vector3& v){
	mNode->setScale(v * mRadius);
	mShape->getBulletShape()->setLocalScaling(OgreBtConverter::to(v));
}

void BulletObstacle::destroy(){
	mManager->removeBulletIterator(mBulletIterator);
	Obstacle::destroy();
}

void BulletObstacle::onBulletHit(){
	destroy();
}