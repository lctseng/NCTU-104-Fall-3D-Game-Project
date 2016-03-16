#include "NCTUObstacleCommon.h"

using namespace NCTU;
using namespace Ogre;

/*!
	\brief Create a cube obstacle (full)
*/

CubeObstacle::CubeObstacle(
		ObstacleManager* mgmt,
		Real restitution,
		Real friction,
		Real mass,
		int index,
		const Vector3& position,
		const Vector3& size,
		const Quaternion& orientation)
	:Obstacle(mgmt,restitution,friction,mass),
	mIndex(index)
{
	// create ogre objects
	mEntity = mManager->getSceneMgr()->createEntity(
		"obstacle.cube." + StringConverter::toString(mIndex),
		"cube.mesh");   
	mEntity->setCastShadows(true);
	// compute scale
	AxisAlignedBox boundingB = mEntity->getBoundingBox();
	Vector3 scale;
	if(size == Vector3::ZERO){
		scale = Vector3(1,1,1);	
	}
	else{
		scale = size / (boundingB.getSize()); // for mesh
	}
	// Bullet margin is a bit bigger so we need a smaller size
	// (Bullet 2.76 Physics SDK Manual page 18)
	Vector3 btSize = (boundingB.getSize() / 2.0) * 0.96f;
	
	mNode = mManager->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mEntity);
	mNode->scale(scale);   // the cube is too big for us
	btSize *= scale;                  // don't forget to scale down the Bullet-box too
	// after that create the Bullet shape with the calculated size
	mShape = new OgreBulletCollisions::BoxCollisionShape(btSize);
	// and the Bullet rigid body
	mBody = new OgreBulletDynamics::RigidBody(
		"obstacle.cube." + StringConverter::toString(mIndex),
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
