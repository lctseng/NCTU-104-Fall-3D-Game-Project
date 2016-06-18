#ifndef NCTU_GENERAL_OBSTACLE_h_
#define NCTU_GENERAL_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	/*! 
	\brief general obstacle
	*/
	class GeneralObstacle : public Obstacle{
	public:
		/*! 
		\brief constructor
		*/
		GeneralObstacle(
			ObstacleManager* mgmt,
			Ogre::Real restitution, 
			Ogre::Real friction, 
			Ogre::Real mass,
			INDEX_TYPE index,
			Ogre::SceneNode* node, 
			Ogre::Entity* ent);
	protected:
		/*! 
		\brief object index
		*/
		INDEX_TYPE mIndex;
	};
};

#endif