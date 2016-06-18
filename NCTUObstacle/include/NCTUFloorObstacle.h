#ifndef NCTU_FLOOR_OBSTACLE_h_
#define NCTU_FLOOR_OBSTACLE_h_


#include "NCTUObstaclePreRequisites.h"
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h" // for static planes
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	/*! 
	\brief floor obstacke
	*/
	class FloorObstacle : public Obstacle{
	public:
		/*! 
		\brief constructor
		*/
		FloorObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction,const Ogre::Vector3& normal,Ogre::Real distance);
		/*! 
		\brief constructor without creating Ogre3D object
		*/
		FloorObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction,Ogre::Plane& plane,Ogre::Entity* entity);
	protected:
		/*! 
		\brief plane normal
		*/
		Ogre::Vector3 mNormal;
		/*! 
		\brief plane distance
		*/
		Ogre::Real mDistance;
		/*! 
		\brief Ogre3D plane object
		*/
		Ogre::Plane mPlane;
	};

};

#endif