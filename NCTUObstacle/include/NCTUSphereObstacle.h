#ifndef NCTU_SPHERE_OBSTACLE_h_
#define NCTU_SPHERE_OBSTACLE_h_

#include "NCTUObstacleCommon.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	class SphereObstacle : public Obstacle{
	public:
		SphereObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,int index,const Ogre::Vector3& position,Ogre::Real radius,const Ogre::Quaternion& orientation);
		virtual void setScale(const Ogre::Vector3&);
	protected:
		int mIndex;
		Ogre::Real mRadius;
	};
};

#endif