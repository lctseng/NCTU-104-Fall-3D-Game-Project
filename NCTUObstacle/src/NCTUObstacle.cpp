#include "NCTUObstacleCommon.h"


using namespace NCTU;
using namespace Ogre;

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

