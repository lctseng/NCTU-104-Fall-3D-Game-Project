#ifndef NCTU_SPHERE_OBSTACLE_h_
#define NCTU_SPHERE_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	/*! 
	\brief sphere obstacle for testing
	*/
	class SphereObstacle : public Obstacle{
	public:
		/*! 
		\brief constructor
		*/
		SphereObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,INDEX_TYPE index,const Ogre::Vector3& position,Ogre::Real radius,const Ogre::Quaternion& orientation);
		/*! 
		\brief set scale for this object
		*/
		virtual void setScale(const Ogre::Vector3&);
	protected:
		/*! 
		\brief the object index
		*/
		INDEX_TYPE mIndex;
		/*! 
		\brief sphere radius
		*/
		Ogre::Real mRadius;
	};
};

#endif