#ifndef NCTU_OBSTACLE_CALLBACK_h_
#define NCTU_OBSTACLE_CALLBACK_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacle.h"

namespace NCTU{
	// -------------------------------------------------------------
	// Callbacks
	struct FloorContactResultCallback : public btCollisionWorld::ContactResultCallback
	{
		FloorContactResultCallback(Obstacle* ptr):mSubject(ptr){}
		btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj0Wrap,
			int partId0,
			int index0,
			const btCollisionObjectWrapper* colObj1Wrap,
			int partId1,
			int index1);

		Obstacle* mSubject;
	};
	struct ObstacleContactResultCallback : public btCollisionWorld::ContactResultCallback
	{
		ObstacleContactResultCallback(Obstacle* ptr):mSubject(ptr){}
		btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj0Wrap,
			int partId0,
			int index0,
			const btCollisionObjectWrapper* colObj1Wrap,
			int partId1,
			int index1);
		Obstacle* mSubject;
	};
};
#endif