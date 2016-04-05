#include "NCTUObstacleCallback.h"
#include <iostream>

using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace std;
btScalar FloorContactResultCallback::addSingleResult(btManifoldPoint& cp,
	const btCollisionObjectWrapper* colObj0Wrap,
	int partId0,
	int index0,
	const btCollisionObjectWrapper* colObj1Wrap,
	int partId1,
	int index1)
{
	if(cp.getDistance() < 0.0f){
		//std::cout << "collide with floor" << std::endl;
		mSubject->setOnFloor(true);
	}
	return 0;
}

btScalar ObstacleContactResultCallback::addSingleResult(btManifoldPoint& cp,
	const btCollisionObjectWrapper* colObj0Wrap,
	int partId0,
	int index0,
	const btCollisionObjectWrapper* colObj1Wrap,
	int partId1,
	int index1)
{
	if(cp.getDistance() < 0.0f){
		Vector3 normalOnB = OgreBulletCollisions::BtOgreConverter::to(cp.m_normalWorldOnB);
		Obstacle* obstacle = (Obstacle*)(colObj1Wrap->getCollisionObject()->getUserPointer());
		// check normal on B
		for(auto it = obstacle->mCollisionConditionVectors.begin();it != obstacle->mCollisionConditionVectors.end();++it){
			auto& entry = *it;
			if(normalOnB.angleBetween(entry.first).valueDegrees() <= entry.second){
				mSubject->setIsBumpObstacle(true);
				break;
			}
		}
		// check on plane
		if(normalOnB.angleBetween(Vector3(0,1,0)).valueDegrees() < 45
			){
			mSubject->setIsOnObstaclePlane(true);
		}
		
		/*
		std::cout << "[collide with obstacle]" << std::endl 
			<< "ptA:" << Ogre::StringConverter::toString(OgreBulletCollisions::BtOgreConverter::to(cp.getPositionWorldOnA())) << std::endl
			<< "ptB:" << Ogre::StringConverter::toString(OgreBulletCollisions::BtOgreConverter::to(cp.getPositionWorldOnB())) << std::endl
			<< "normal:" << Ogre::StringConverter::toString(OgreBulletCollisions::BtOgreConverter::to(cp.m_normalWorldOnB)) << std::endl;
		*/
	}
	return 0;
}