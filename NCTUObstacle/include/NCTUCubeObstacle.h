#ifndef NCTU_CUBE_OBSTACLE_h_
#define NCTU_CUBE_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	class CubeObstacle : public Obstacle{
	public:
		CubeObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,INDEX_TYPE index,const Ogre::Vector3& position,const Ogre::Vector3& size,const Ogre::Quaternion& orientation);
		virtual void setScale(const Ogre::Vector3&);
	protected:
		INDEX_TYPE mIndex;
		Ogre::Vector3 mInitScale;
	};
};

#endif