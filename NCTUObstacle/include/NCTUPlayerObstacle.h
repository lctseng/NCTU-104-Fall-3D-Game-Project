#ifndef NCTU_PLAYER_OBSTACLE_h_
#define NCTU_PLAYER_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"       // for Spheres
#include "NCTUObstacleCallback.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	class PlayerObstacle : public Obstacle{
	public:
		PlayerObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,const Ogre::String& name, Ogre::Real scale);
		virtual void setSliding(bool val);
		
		virtual void updateCollision(const Ogre::FrameEvent& evt);
		virtual bool isJumpEnable();
		virtual bool isSlideEnable();

		virtual inline bool isSliding() const {return mIsSliding;}
		

	protected:
		
		virtual void updateFloorCollision(const Ogre::FrameEvent& evt);
		virtual void updateAllObstacleCollision(const Ogre::FrameEvent& evt);

		bool mIsSliding;
		



	};
};

#endif