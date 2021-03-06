#include "NCTUObstacleManager.h"
#include "NCTUGeneralObstacle.h"

using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;

GeneralObstacle::GeneralObstacle(ObstacleManager* mgmt,Real restitution, Real friction, Real mass, INDEX_TYPE index,SceneNode* node, Entity* ent)
:Obstacle(mgmt,restitution,friction,mass),mIndex(index)
{
	mName = "obstacle.general." + StringConverter::toString(mIndex);
	// create settings
	mScaleDifference = node->getScale();
	Vector3 oldPosition = node->getPosition();
	node->setPosition(0,0,0); // reset position
	Quaternion oldOrientation = node->getOrientation();
	node->setOrientation(0,0,0,1); // reset orientation
	// save node and entity
	mNode = node;
	mEntity = ent;
	// bullet
	mShape = generateFittingShape(mNode,mEntity);
	mBody = new OgreBulletDynamics::RigidBody(
		mName,
		mManager->getWorld(),COL_GROUP_ALL,COL_MASK_OBSTACLE);
	mBody->setShape(   mNode,
					mShape,
					mRestitution,         // dynamic body restitution
					mFriction,         // dynamic body friction
					mMass);
					//,          // dynamic bodymass
					//position,      // starting position of the box
					//orientation);// orientation of the box       
 
	mBody->getBulletObject()->setUserPointer(this);
	setPosition(oldPosition);
	setOrientation(oldOrientation);
}

