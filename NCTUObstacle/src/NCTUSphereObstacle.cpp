#include "NCTUObstacleCommon.h"

using namespace NCTU;
using namespace Ogre;

/*!
	\brief Create a sphere obstacle (full)
*/

SphereObstacle::SphereObstacle(
		ObstacleManager* mgmt,
		Real restitution,
		Real friction,
		Real mass,
		int index,
		const Vector3& position,
		Real radius,
		const Quaternion& orientation)
	:Obstacle(mgmt,restitution,friction,mass),
	mIndex(index)
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
		"obstacle.sphere." + StringConverter::toString(mIndex),
		mManager->getWorld());

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
