#ifndef NCTU_PICKUP_OBSTACLE_h_
#define NCTU_PICKUP_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	class PickupObstacle : public Obstacle{
	public:
		PickupObstacle(
			ObstacleManager* mgmt,
			INDEX_TYPE index,
			Ogre::SceneNode* node, 
			Ogre::Entity* ent);
		virtual inline void setPickupIterator(std::list<PickupObstacle *>::iterator it){mPickupIterator = it;}
		virtual inline void cleanUp();

		virtual bool canBeShoot() const{ return false;}
		virtual bool canStandOn() const{ return false;}
		virtual bool canCauseDead() const{ return false;}
		virtual void updateEffect(const Ogre::FrameEvent& evt);
	protected:
		INDEX_TYPE mIndex;
		std::list<PickupObstacle *>::iterator mPickupIterator;
	};
};

#endif