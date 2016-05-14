#include "NCTUObstacle.h"
#include "NCTUObstacleManager.h"
#include <iostream>
using namespace NCTU;
using namespace Ogre;
using namespace std;
using namespace OgreBulletCollisions;


Obstacle::Obstacle(ObstacleManager* mgmt,Real restitution,Real friction,Real mass)
	:mManager(mgmt),
	mFriction(friction),
	mRestitution(restitution),
	mMass(mass),
	mIsBumpObstacle(false),
	mScaleDifference(1,1,1),
	mFloorTouchValue(FLOOR_TOUCH_THRESHOLD),
	mObstaclePlaneTouchValue(OBSTACLE_PLANE_TOUCH_THRESHOLD),
	mLifeTime(0.0f), 
	mLifeTimeEnable(false),
	mDeleteMark(false),
	mHitPoint(-1), // invincible
	mHpType(typeBoth),
	mName("obstacle"),
	mParticleSystemInit(false),
	mFrozen(false),
	mEntityDetached(false),
	mBumpSpeed(0.0f)
{

}
Obstacle::~Obstacle(){
	// delete physics
	destroyPhysics();
	// destory particle system
	destroyParticleSystem();
	// detach node and entity
	detachEntity();
	mManager->getSceneMgr()->destroyEntity(mEntity);
	mManager->getSceneMgr()->destroySceneNode(mNode);
	//cout << "Obstacle "  << mName << "Destroyed" << endl;
}

void Obstacle::detachEntity(){
	if(!mEntityDetached){
		mNode->detachObject(mEntity);
	}
}

void Obstacle::setScale(const Ogre::Vector3& v){
	mNode->setScale(v * mScaleDifference);
	if(mShape){
		mShape->getBulletShape()->setLocalScaling(OgreBtConverter::to(v));
	}
	
}

void Obstacle::setOnFloor(bool val){
	if(val){
		mFloorTouchValue = 0;
	}
	else{
		if(mFloorTouchValue < FLOOR_TOUCH_THRESHOLD){
			++mFloorTouchValue;
		}
	}
}
void Obstacle::setIsOnObstaclePlane(bool val){
	if(val){
		mObstaclePlaneTouchValue = 0;
	}
	else{
		if(mObstaclePlaneTouchValue < OBSTACLE_PLANE_TOUCH_THRESHOLD){
			++mObstaclePlaneTouchValue;
		}
	}
}

void Obstacle::updateLifeTime(const Ogre::FrameEvent& evt){
	if(mLifeTimeEnable){
		mLifeTime -= evt.timeSinceLastFrame;
		if(mLifeTime <= 0.0f){
			onLifeEnd();
		}
	}
}

void Obstacle::onLifeEnd(){
	destroy();
}

void Obstacle::destroy(){
	if(!mDeleteMark){
		mLifeTime = 0.0f;
		mDeleteMark = true;
	}
}

void Obstacle::destroyPhysics(){
	mFrozen = true;
	if(mBody){
		delete mBody;
		mBody = nullptr;
	}
	if(mShape){
		delete mShape;
		mShape = nullptr;
	}
}

void Obstacle::onBulletHit(BulletObstacle* bullet,Obstacle* object){
}

OgreBulletCollisions::CollisionShape* Obstacle::generateFittingShape(SceneNode* node, Entity* ent){
	/*
	使用OgreBullet的AnimatedMeshToShapeConverter
	這個物件的作用是輸入Entity取得Mesh的詳細資料，
	便於算出ConvexHull或更複雜的GImpactCollision
	其實用另一個StaticMeshToShapeConverter也行，並不影響結果
	*/
	OgreBulletCollisions::StaticMeshToShapeConverter *converter = 
		new OgreBulletCollisions::StaticMeshToShapeConverter(
		ent, //很單純就載入Entity，裡面會去取得所需要的Mesh資訊
		node->_getFullTransform()); /*載入此Entity的Matrix4，
									也就是取得大小與位置，
									這邊直接用_getFullTransform()從node取得最方便*/

	//使用createConcave產生我們所要的GImpactConcaveShape

	GImpactConcaveShape *shape = converter->createConcave();
	return shape;
}

void Obstacle::initParticleSystem(const String& particleName){
	if(!mParticleSystemInit){
		mParticleSystemInit = true;
		mParticleSystemName = "particle." + mName;
		mParticleSystemNode = static_cast<SceneNode*>(
			mNode->createChild());
		mParticleSystem = mManager->getSceneMgr()->createParticleSystem(
			mParticleSystemName, particleName);

		ParticleEmitter *e = mParticleSystem->getEmitter(0);
		e->setEnabled(false);
		mParticleSystemNode->attachObject(mParticleSystem);
		mParticleSystemNode->setPosition(Vector3::ZERO);
		mParticleSystemNode->setVisible(false);
	}
}
void Obstacle::setOffParticleSystem(){
	if(mParticleSystemInit)	{
		mParticleSystemNode->setVisible(true);
		mParticleSystem->setVisible(true);
		ParticleEmitter *e = mParticleSystem->getEmitter(0);
		e->setEnabled(true);
	}
}
void Obstacle::destroyParticleSystem(){
	if(mParticleSystemInit){
		mParticleSystemNode->detachObject(mParticleSystem);
		mManager->getSceneMgr()->destroyParticleSystem(mParticleSystem);
		mManager->getSceneMgr()->destroySceneNode(mParticleSystemNode);
		mParticleSystemInit = false;
	}
}

void Obstacle::stopParticleSystem(){
	if(mParticleSystemInit)	{
		ParticleEmitter *e = mParticleSystem->getEmitter(0);
		e->setEnabled(false);
	}
}

int Obstacle::decreaseHp(int value){
	if(mHitPoint > 0){
		mHitPoint -= value;
		if(mHitPoint <= 0){
			mHitPoint = 0;
			destroy();
		}
		else{
			// change the material if needed
			if(mHpChangeMaterials.hasKey(mHitPoint)){
				mEntity->setMaterialName(mHpChangeMaterials[mHitPoint]);
			}
		}
	}
	cout << "Hp Left:" << mHitPoint << endl;
	return mHitPoint;
}