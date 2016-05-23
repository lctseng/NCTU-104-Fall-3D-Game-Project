#include "NCTUObstacleManager.h"
#include "NCTUPickupObstacle.h"

using namespace NCTU;
using namespace Ogre;

PickupObstacle::PickupObstacle(ObstacleManager* mgmt,INDEX_TYPE index,SceneNode* node, Entity* ent)
:Obstacle(mgmt,0,0,0),mIndex(index)
{
	mName = "pickup.general." + StringConverter::toString(mIndex);
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
		mManager->getWorld(),COL_GROUP_ALL,COL_MASK_BULLET);
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
	initParticleSystem("Examples/GreenyNimbus");
	setOffParticleSystem();
	mNode->yaw(Degree(rand()%180));
	mNode->roll(Degree(rand()%180));
	mNode->pitch(Degree(rand()%180));
}
void PickupObstacle::updateEffect(const Ogre::FrameEvent& evt){
	Degree deg(evt.timeSinceLastFrame * 60) ;
	mNode->yaw(deg);
	mNode->roll(deg);
	mNode->pitch(deg);
}
void PickupObstacle::cleanUp(){
	mManager->removePickupIterator(mPickupIterator);
	Obstacle::cleanUp();
}