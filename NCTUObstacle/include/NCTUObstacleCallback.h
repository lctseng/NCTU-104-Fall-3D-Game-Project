#ifndef NCTU_OBSTACLE_CALLBACK_h_
#define NCTU_OBSTACLE_CALLBACK_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacle.h"

namespace NCTU{
	// -------------------------------------------------------------
	// Callbacks
	/*! 
	\brief callback for player-floor contact
	*/
	struct FloorContactResultCallback : public btCollisionWorld::ContactResultCallback
	{
		/*! 
		\brief handle contact result
		*/
		FloorContactResultCallback(Obstacle* ptr):mSubject(ptr){}
		btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj0Wrap,
			int partId0,
			int index0,
			const btCollisionObjectWrapper* colObj1Wrap,
			int partId1,
			int index1);
		/*! 
		\brief pointer to the subject
		*/
		Obstacle* mSubject;
	};
	/*! 
	\brief callback for player-obstalce contact event
	*/
	struct ObstacleContactResultCallback : public btCollisionWorld::ContactResultCallback
	{
		/*! 
		\brief handle contact result
		*/
		ObstacleContactResultCallback(Obstacle* ptr):mSubject(ptr){}
		btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj0Wrap,
			int partId0,
			int index0,
			const btCollisionObjectWrapper* colObj1Wrap,
			int partId1,
			int index1);
		/*! 
		\brief pointer to the subject
		*/
		Obstacle* mSubject;
	};
	/*! 
	\brief callback for bullet-obstacle contact
	*/
	struct BulletContactResultCallback : public btCollisionWorld::ContactResultCallback
	{
		/*! 
		\brief handle contact result
		*/
		BulletContactResultCallback(BulletObstacle* me,Obstacle* tgr):mSubject(me),mObject(tgr){}
		btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj0Wrap,
			int partId0,
			int index0,
			const btCollisionObjectWrapper* colObj1Wrap,
			int partId1,
			int index1);
		/*! 
		\brief pointer to the obstacle
		*/
		Obstacle* mObject;
		/*! 
		\brief pointer to the bullet
		*/
		BulletObstacle* mSubject;
	};
	/*! 
	\brief callback for player-pickup contact
	*/
	struct PickupContactResultCallback : public btCollisionWorld::ContactResultCallback
	{
		/*! 
		\brief handle contact result
		*/
		PickupContactResultCallback(PlayerObstacle* me,PickupObstacle* tgr):mSubject(me),mObject(tgr){}
		btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj0Wrap,
			int partId0,
			int index0,
			const btCollisionObjectWrapper* colObj1Wrap,
			int partId1,
			int index1);
		/*! 
		\brief pointer to the pickup
		*/
		PickupObstacle* mObject;
		/*! 
		\brief pointer to the player
		*/
		PlayerObstacle* mSubject;
	};
};
#endif