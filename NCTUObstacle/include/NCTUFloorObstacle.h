#ifndef NCTU_FLOOR_OBSTACLE_h_
#define NCTU_FLOOR_OBSTACLE_h_

#include "NCTUObstacleCommon.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	class FloorObstacle : public Obstacle{
	public:
		FloorObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction,const Ogre::Vector3& normal,Ogre::Real distance);
		FloorObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction,Ogre::Plane& plane,Ogre::Entity* entity);
	protected:
		Ogre::Vector3 mNormal;
		Ogre::Real mDistance;
		Ogre::Plane mPlane;
	};

};

#endif