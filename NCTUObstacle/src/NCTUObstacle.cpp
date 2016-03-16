#include "NCTUObstacleCommon.h"


using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;

Obstacle::Obstacle(ObstacleManager* mgmt,Real restitution,Real friction,Real mass)
:mManager(mgmt),
mFriction(friction),
mRestitution(restitution),
mMass(mass)
{
	
}
Obstacle::~Obstacle(){
	// delete shape and body
	delete mBody;
	delete mShape;
}

void Obstacle::setScale(const Ogre::Vector3& v){
	mNode->setScale(v);
	mShape->getBulletShape()->setLocalScaling(OgreBtConverter::to(v));
}
