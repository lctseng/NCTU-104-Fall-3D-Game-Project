#include "NCTUObstacle.h"
#include "NCTUObstacleManager.h"
#include "TutorialApplication.h"
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
	mFrozen(false),
	mEntityDetached(false),
	mBumpSpeed(0.0f),
	mTurnUsed(false),
	mCurrentObstacleValid(0.0f)
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
	�ϥ�OgreBullet��AnimatedMeshToShapeConverter
	�o�Ӫ��󪺧@�άO��JEntity���oMesh���ԲӸ�ơA
	�K���XConvexHull�Χ������GImpactCollision
	���Υt�@��StaticMeshToShapeConverter�]��A�ä��v�T���G
	*/
	OgreBulletCollisions::StaticMeshToShapeConverter *converter = 
		new OgreBulletCollisions::StaticMeshToShapeConverter(
		ent, //�ܳ�´N���JEntity�A�̭��|�h���o�һݭn��Mesh��T
		node->_getFullTransform()); /*���J��Entity��Matrix4�A
									�]�N�O���o�j�p�P��m�A
									�o�䪽����_getFullTransform()�qnode���o�̤�K*/

	//�ϥ�createConcave���ͧڭ̩ҭn��GImpactConcaveShape

	GImpactConcaveShape *shape = converter->createConcave();
	return shape;
}

void Obstacle::initParticleSystem(const String& particleName, int index){
	// check entry exists
	if(index >= mParticleSystems.size()){
		// exceeds, fill entries to fill
		for(int i=mParticleSystems.size();i<=index;i++){
			mParticleSystems.push_back(ParticleSystemPack());
		}
	}
	ParticleSystemPack& pack = mParticleSystems[index];
	if(!pack.mParticleSystemInit){
		pack.mParticleSystemInit = true;
		pack.mParticleSystemName = "particle." + StringConverter::toString(index) + "." + mName;
		pack.mParticleSystemNode = static_cast<SceneNode*>(
			mNode->createChild());
		pack.mParticleSystem = mManager->getSceneMgr()->createParticleSystem(
			pack.mParticleSystemName, particleName);

		ParticleEmitter *e = pack.mParticleSystem->getEmitter(0);
		e->setEnabled(false);
		pack.mParticleSystemNode->attachObject(pack.mParticleSystem);
		pack.mParticleSystemNode->setPosition(Vector3::ZERO);
		pack.mParticleSystemNode->setVisible(false);
	}
}
void Obstacle::setOffParticleSystem(int index){
	// check entry exists
	if(index >= mParticleSystems.size()){
		return; // exceeds
	}
	else if(index < 0){
		// all
		for(int i=0;i<mParticleSystems.size();i++){
			setOffParticleSystem(i);
		}
	}
	else{
		ParticleSystemPack& pack = mParticleSystems[index];
		if(pack.mParticleSystemInit)	{
			pack.mParticleSystemNode->setVisible(true);
			pack.mParticleSystem->setVisible(true);
			ParticleEmitter *e = pack.mParticleSystem->getEmitter(0);
			e->setEnabled(true);
		}
	}

}
void Obstacle::destroyParticleSystem(){
	for(int i=0;i<mParticleSystems.size();i++){
		ParticleSystemPack& pack = mParticleSystems[i];
		if(pack.mParticleSystemInit){
			pack.mParticleSystemNode->detachObject(pack.mParticleSystem);
			mManager->getSceneMgr()->destroyParticleSystem(pack.mParticleSystem);
			mManager->getSceneMgr()->destroySceneNode(pack.mParticleSystemNode);
			pack.mParticleSystemInit = false;
		}
	}
}

void Obstacle::stopParticleSystem(int index){
	// check entry exists
	if(index >= mParticleSystems.size()){
		return; // exceeds
	}
	else if(index < 0){
		// all
		for(int i=0;i<mParticleSystems.size();i++){
			stopParticleSystem(i);
		}
	}
	else{
		ParticleSystemPack& pack = mParticleSystems[index];
		if(pack.mParticleSystemInit)	{
			ParticleEmitter *e = pack.mParticleSystem->getEmitter(0);
			e->setEnabled(false);
		}
	}
}

int Obstacle::decreaseHp(int value){
	if(mHitPoint > 0){
		mHitPoint -= value;
		if(mHitPoint <= 0){
			mManager->getApp()->changeScore(100);
			mHitPoint = 0;
			switch(getHpType()){
			case typeRed:
				Audio::playSE("BreakRed.wav");
				break;
			case typeBlue:
				Audio::playSE("BreakBlue.wav");
				break;
			case typeBoth:
				Audio::playSE("BreakGeneral.wav");
				break;
			}
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
void Obstacle::setCurrentObstacle(Obstacle* obj){
	mCurrentObstacle = obj;
	if(obj){
		mCurrentObstacleValid = 0.1f;	
	}
	else{
		mCurrentObstacleValid = 0.0f;
	}
}
void Obstacle::updatePlayingGame(const FrameEvent& evt){
	if(mCurrentObstacleValid > 0.0f){
		mCurrentObstacleValid -= evt.timeSinceLastFrame;
	}
	else{
		mCurrentObstacle = nullptr;
	}
}