#include "NCTUObstacleManager.h"
#include "NCTUGeneralObstacle.h"

using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;

GeneralObstacle::GeneralObstacle(ObstacleManager* mgmt,Real restitution, Real friction, Real mass, int index,SceneNode* node, Entity* ent)
:Obstacle(mgmt,restitution,friction,mass),mIndex(index)
{
	// create settings
	mScaleDifference = node->getScale();
	Vector3 oldPosition = node->getPosition();
	Vector3 position = oldPosition;
	//Vector3 position(0,0,0);
	node->setPosition(0,0,0); // reset position
	Quaternion orientation = node->getOrientation();
	// save node and entity
	mNode = node;
	mEntity = ent;
	mEntity->setCastShadows(true);
	// bullet
	mShape = generateFittingShape(mNode,mEntity);
	mBody = new OgreBulletDynamics::RigidBody(
		"obstacle.general." + StringConverter::toString(mIndex),
		mManager->getWorld());
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
}

