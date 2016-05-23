#include "NCTUObstacleManager.h"
#include "NCTUBulletObstacle.h"
#include "TutorialApplication.h"

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
	mBulletType(bulletType),
	mParticleLifeTime(3.0f)
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
		initParticleSystem("Examples/JetEngine1",0);	
		Audio::playSE("ShootRed.wav");
	}
	else{
		initParticleSystem("Examples/JetEngine3",0);
		Audio::playSE("ShootBlue.wav");
	}
	setOffParticleSystem(0);
	
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
		stopParticleSystem(0);
		setLifeTime(5.0f);
		if(mParticleSystems.size() > 1 && mParticleSystems[1].mParticleSystemInit){
			mParticleSystems[1].mParticleSystemNode->lookAt(mManager->getPlayer()->getPosition(),Node::TS_WORLD,Vector3::UNIT_Y);	
		}
	}
}

void BulletObstacle::updateLifeTime(const Ogre::FrameEvent& evt){
	Obstacle::updateLifeTime(evt);
	if(mFrozen){
		mParticleLifeTime -= evt.timeSinceLastFrame;
		if(mParticleLifeTime <= 0){
			stopParticleSystem(1);
			// TODO:: stop particle system	
		}
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