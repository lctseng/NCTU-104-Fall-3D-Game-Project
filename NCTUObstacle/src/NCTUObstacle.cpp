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
	mHitPoint(-1) // invincible
{

}
Obstacle::~Obstacle(){
	// delete shape and body
	delete mBody;
	delete mShape;
	// detach node and entity
	mNode->detachObject(mEntity);
	mManager->getSceneMgr()->destroyEntity(mEntity);
	mManager->getSceneMgr()->destroySceneNode(mNode);
}

void Obstacle::setScale(const Ogre::Vector3& v){
	mNode->setScale(v * mScaleDifference);
	mShape->getBulletShape()->setLocalScaling(OgreBtConverter::to(v));
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
			destroy();
		}
	}
}

void Obstacle::destroy(){
	mLifeTime = 0.0f;
	mDeleteMark = true;
}

void Obstacle::onBulletHit(){
	if(mHitPoint > 0){
		if(--mHitPoint == 0){
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