#ifndef NCTU_SPHERE_OBSTACLE_h_
#define NCTU_SPHERE_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	class SphereObstacle : public Obstacle{
	public:
		SphereObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,INDEX_TYPE index,const Ogre::Vector3& position,Ogre::Real radius,const Ogre::Quaternion& orientation);
		virtual void setScale(const Ogre::Vector3&);
	protected:
		INDEX_TYPE mIndex;
		Ogre::Real mRadius;
	};
};

#endif