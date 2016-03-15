#include "NCTUObstacleCommon.h"


using namespace NCTU;
using namespace Ogre;

PlayerObstacle::PlayerObstacle(ObstacleManager* mgmt,Real restitution, Real friction, Real mass)
	:Obstacle(mgmt,restitution,friction,mass)
{
	// some default settings
	Real radius = 50.0f;
	Vector3 position(0,0,0);
	Quaternion orientation(0,0,0,1);
	// for ogre
	mEntity
		= mManager->getSceneMgr()
		->createEntity( "obstacle.player", "ellipsoid.mesh" ); 
	mEntity->setCastShadows(true);
	mNode
		= mManager->getSceneMgr()
		->getRootSceneNode()
		->createChildSceneNode( 
		"playerNode", position ); 
	mNode->scale(radius,radius,radius);
	mNode->attachObject( mEntity );
	mEntity->setMaterialName("Bullet/Ball");
	// for bullet
	mShape = new OgreBulletCollisions::SphereCollisionShape(radius);
	mBody = new OgreBulletDynamics::RigidBody(
		"playerRigid",
		mManager->getWorld());
	mBody->setShape(   mNode,
					mShape,
					mRestitution,         // dynamic body restitution
					mFriction,         // dynamic body friction
					mMass,          // dynamic bodymass
					position,      // starting position of the box
					orientation);// orientation of the box       
	mBody->getBulletObject()->setUserPointer(this);
}