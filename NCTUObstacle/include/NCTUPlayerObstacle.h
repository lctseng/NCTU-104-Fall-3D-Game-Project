#ifndef NCTU_PLAYER_OBSTACLE_h_
#define NCTU_PLAYER_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"       // for Spheres
#include "NCTUObstacleCallback.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	/*! 
	\brief player obstacle 
	*/
	class PlayerObstacle : public Obstacle{
	public:
		/*! 
		\brief constructor
		*/
		PlayerObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,const Ogre::String& name, Ogre::Vector3 scale);
		/*! 
		\brief another constructor, but not create scene node and entity
		*/
		PlayerObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,Ogre::SceneNode* node, Ogre::Entity* ent);
		/*! 
		\brief destructor
		*/
		virtual ~PlayerObstacle();
		/*! 
		\brief detach entity from scene node
		*/
		virtual void detachEntity();
		/*! 
		\brief set sliding state
		*/
		virtual void setSliding(bool val);
		/*! 
		\brief update collision
		*/
		virtual void updateCollision(const Ogre::FrameEvent& evt);
		/*! 
		\brief update routing for playing game
		*/
		virtual void updatePlayingGame(const Ogre::FrameEvent& evt);
		/*! 
		\brief is jump enabled?
		*/
		virtual bool isJumpEnable();
		/*! 
		\brief is slide enabled?
		*/
		virtual bool isSlideEnable();
		/*! 
		\brief is player sliding now?
		*/
		virtual inline bool isSliding() const {return mIsSliding;}
		/*! 
		\brief perform jump
		*/
		virtual void performJump();
		/*! 
		\brief require player to slide (called by application
		*/
		virtual inline void requireSlide(bool v);
		/*! 
		\brief reset player action
		*/
		virtual void resetAction();
		/*! 
		\brief is currently turn ok?
		*/
		virtual bool isTurnOK(int turn);
		/*! 
		\brief process on turn
		*/
		virtual void onTurn(int turn);
		/*! 
		\brief is this object can be shoot?
		*/
		virtual bool canBeShoot() const{ return false;}
		/*! 
		\brief is this object can be standed on?
		*/
		virtual bool canStandOn() const{ return false;}
		/*! 
		\brief is this object cause dead?
		*/
		virtual bool canCauseDead() const{ return false;}
		/*! 
		\brief process when get a pickup object
		*/
		virtual void onPickupGet();
	protected:
		/*! 
		\brief update floor collision
		*/
		virtual void updateFloorCollision(const Ogre::FrameEvent& evt);
		/*! 
		\brief update collision for all obstacles
		*/
		virtual void updateAllObstacleCollision(const Ogre::FrameEvent& evt);
		/*! 
		\brief update sliding
		*/
		virtual void updateSliding(const Ogre::FrameEvent& evt);
		/*! 
		\brief update jumping
		*/
		virtual void updateJumping(const Ogre::FrameEvent& evt);
		/*! 
		\brief is currently sliding?
		*/
		bool mIsSliding;
		/*! 
		\brief sliding valid time
		*/
		Ogre::Real mSlidingValidTime;
		/*! 
		\brief cool down time for jumping
		*/
		Ogre::Real mJumpCoolDown;
		/*! 
		\brief is currently requiring slide?
		*/
		bool mSlideRequiring;
		/*! 
		\brief the particle show time
		*/
		Ogre::Real mParticleTime;
		/*! 
		\brief base SceneNode for player
		*/
		Ogre::SceneNode* mBaseNode;
		/*! 
		\brief base Entity for player
		*/
		Ogre::Entity* mBaseEntity;
		/*! 
		\brief animation state for player
		*/
		Ogre::AnimationState* mAnimationState;
		/*! 
		\brief is standing up?
		*/
		bool up;
		/*! 
		\brief is sliding down?
		*/
		bool down;
		/*! 
		\brief generate player's collision shape
		*/
		virtual OgreBulletCollisions::CollisionShape* generatePlayerShape(Ogre::SceneNode* node, Ogre::Entity* ent); 
		/*! 
		\brief create the base entitiy
		*/
		virtual void createBaseEntity();
	};
};

#endif
