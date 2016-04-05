#ifndef NCTU_CUBE_OBSTACLE_h_
#define NCTU_CUBE_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"       // for Boxes
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	class CubeObstacle : public Obstacle{
	public:
		CubeObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,int index,const Ogre::Vector3& position,const Ogre::Vector3& size,const Ogre::Quaternion& orientation);
		virtual void setScale(const Ogre::Vector3&);
	protected:
		int mIndex;
		Ogre::Vector3 mInitScale;
	};
};

#endif