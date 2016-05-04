#include "NCTUObstacleManager.h"
#include "NCTUBulletObstacle.h"

using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;



BulletHitHandler BulletObstacle::mBulletHitHandler = nullptr;
/*!
	\brief Create a bullet obstacle (full)
*/

BulletObstacle::BulletObstacle(
		ObstacleManager* mgmt,
		Real restitution,
		Real friction,
		Real mass,
		INDEX_TYPE index,
		HpType bulletType,
		const Vector3& position,
		Real radius,
		const Quaternion& orientation
		)
	:Obstacle(mgmt,restitution,friction,mass),
	mIndex(index),
	mRadius(radius),
	mHit(false),
	mBulletType(bulletType)
{
	mName = "obstacle.bullet." + StringConverter::toString(mIndex);
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
	// fire a particle system
	if(mBulletType == typeRed){
		initParticleSystem("Examples/JetEngine1");	
	}
	else{
		initParticleSystem("Examples/JetEngine3");
	}
	setOffParticleSystem();
	
}
void BulletObstacle::setScale(const Ogre::Vector3& v){
	mNode->setScale(v * mRadius);
	if(mShape){
		mShape->getBulletShape()->setLocalScaling(OgreBtConverter::to(v));
	}
}

void BulletObstacle::cleanUp(){
	mManager->removeBulletIterator(mBulletIterator);
	Obstacle::cleanUp();
}

void BulletObstacle::onLifeEnd(){
	if(mFrozen){
		destroy();
	}
	else{
		destroyPhysics();
		detachEntity();
		stopParticleSystem();
		setLifeTime(1.0f);
		Audio::playSE("Cursor1.wav");
	}
}

bool BulletObstacle::isAlive() const {
	return Obstacle::isAlive() && !mHit;
}

void BulletObstacle::onBulletHit(BulletObstacle* bullet, Obstacle* object){
	setLifeTime(0.0f);
	mHit = true;
	if(BulletObstacle::mBulletHitHandler){
		BulletObstacle::mBulletHitHandler(bullet,object);
	}
}