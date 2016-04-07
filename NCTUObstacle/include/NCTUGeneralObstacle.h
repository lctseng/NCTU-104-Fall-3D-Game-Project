#ifndef NCTU_GENERAL_OBSTACLE_h_
#define NCTU_GENERAL_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	class GeneralObstacle : public Obstacle{
	public:
		GeneralObstacle(
			ObstacleManager* mgmt,
			Ogre::Real restitution, 
			Ogre::Real friction, 
			Ogre::Real mass,
			int index,
			Ogre::SceneNode* node, 
			Ogre::Entity* ent);
	protected:
		int mIndex;
	};
};

#endif