#ifndef NCTU_PICKUP_OBSTACLE_h_
#define NCTU_PICKUP_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	/*! 
	\brief pickup obstacle
	*/
	class PickupObstacle : public Obstacle{
	public:
		/*! 
		\brief constructor
		*/
		PickupObstacle(
			ObstacleManager* mgmt,
			INDEX_TYPE index,
			Ogre::SceneNode* node, 
			Ogre::Entity* ent);
		/*! 
		\brief set pickup iterator for manager
		*/
		virtual inline void setPickupIterator(std::list<PickupObstacle *>::iterator it){mPickupIterator = it;}
		/*! 
		\brief clean up routing
		*/
		virtual inline void cleanUp();
		/*! 
		\brief is this object can be shoot?
		*/
		virtual bool canBeShoot() const{ return false;}
		/*! 
		\brief is this object can be standed on?
		*/
		virtual bool canStandOn() const{ return false;}
		/*! 
		\brief is this object can cause dead?
		*/
		virtual bool canCauseDead() const{ return false;}
		/*! 
		\brief update the effect
		*/
		virtual void updateEffect(const Ogre::FrameEvent& evt);
	protected:
		/*! 
		\brief object index
		*/
		INDEX_TYPE mIndex;
		/*! 
		\brief iterator for manager
		*/
		std::list<PickupObstacle *>::iterator mPickupIterator;
	};
};

#endif