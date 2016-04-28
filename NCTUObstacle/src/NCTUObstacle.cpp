#include "NCTUObstacle.h"
#include <iostream>
using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;


Obstacle::Obstacle(ObstacleManager* mgmt,Real restitution,Real friction,Real mass)
	:mManager(mgmt),
	mFriction(friction),
	mRestitution(restitution),
	mMass(mass),
	mIsBumpObstacle(false),
	mScaleDifference(1,1,1),
	mFloorTouchValue(FLOOR_TOUCH_THRESHOLD),
	mObstaclePlaneTouchValue(OBSTACLE_PLANE_TOUCH_THRESHOLD)
{

}
Obstacle::~Obstacle(){
	// delete shape and body
	delete mBody;
	delete mShape;
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
		++mFloorTouchValue;
	}
}
void Obstacle::setIsOnObstaclePlane(bool val){
	if(val){
		mObstaclePlaneTouchValue = 0;
	}
	else{
		++mObstaclePlaneTouchValue;
	}
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