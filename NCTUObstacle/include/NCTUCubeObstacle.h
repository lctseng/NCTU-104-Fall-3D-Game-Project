#ifndef NCTU_CUBE_OBSTACLE_h_
#define NCTU_CUBE_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	/*! 
	\brief cube obstacle for testing
	*/
	class CubeObstacle : public Obstacle{
	public:
		/*! 
		\brief constructor
		*/
		CubeObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,INDEX_TYPE index,const Ogre::Vector3& position,const Ogre::Vector3& size,const Ogre::Quaternion& orientation);
		/*! 
		\brief set scale for this object
		*/
		virtual void setScale(const Ogre::Vector3&);
	protected:
		/*! 
		\brief object index
		*/
		INDEX_TYPE mIndex;
		/*! 
		\brief initial scale for this object
		*/
		Ogre::Vector3 mInitScale;
	};
};

#endif