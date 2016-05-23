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
		PlayerObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,const Ogre::String& name, Ogre::Vector3 scale);
		PlayerObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,Ogre::SceneNode* node, Ogre::Entity* ent);
		virtual void setSliding(bool val);
		
		virtual void updateCollision(const Ogre::FrameEvent& evt);
		virtual void updatePlayingGame(const Ogre::FrameEvent& evt);

		virtual bool isJumpEnable();
		virtual bool isSlideEnable();

		virtual inline bool isSliding() const {return mIsSliding;}
		
		virtual void performJump();

		virtual inline void requireSlide(bool v){mSlideRequiring = v;}
		virtual void resetAction();
		
		virtual bool isTurnOK(int turn);
		virtual void onTurn(int turn);

		virtual bool canBeShoot() const{ return false;}
		virtual bool canStandOn() const{ return false;}
		virtual bool canCauseDead() const{ return false;}

		virtual void onPickupGet();

	protected:
		
		virtual void updateFloorCollision(const Ogre::FrameEvent& evt);
		virtual void updateAllObstacleCollision(const Ogre::FrameEvent& evt);
		virtual void updateSliding(const Ogre::FrameEvent& evt);
		virtual void updateJumping(const Ogre::FrameEvent& evt);

		bool mIsSliding;
		
		Ogre::Real mSlidingValidTime;
		Ogre::Real mJumpCoolDown;
		bool mSlideRequiring;
		Ogre::Real mParticleTime;

		



	};
};

#endif
