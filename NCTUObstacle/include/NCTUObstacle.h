#ifndef NCTU_OBSTACLE_h_
#define NCTU_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"


#include <deque>

namespace NCTU{
	// -------------------------------------------------------------
	class Obstacle{
	public:
		Obstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction,Ogre::Real mass);
		Obstacle(const Obstacle&);
		virtual ~Obstacle();
		
		virtual void setScale(const Ogre::Vector3&);
		virtual void updateCollision(const Ogre::FrameEvent& evt){};

		inline Ogre::SceneNode* getSceneNode(){return mNode;}
		inline Ogre::Entity* getEntity(){return mEntity;}
		inline OgreBulletDynamics::RigidBody* getBody(){return mBody;}
		inline OgreBulletCollisions::CollisionShape* getShape(){return mShape;}

		inline void setVelocity(const Ogre::Vector3 v){mBody->setLinearVelocity(v);}
		inline Ogre::Vector3 getVelocity() const {return mBody->getLinearVelocity();}
		inline void applyVelocityChange(const Ogre::Vector3 v){setVelocity(getVelocity() + v);}


		inline void setPosition(const Ogre::Vector3 v){mBody->setPosition(v); mNode->setPosition(v);}
		inline Ogre::Vector3 getPosition() const {return mNode->getPosition();}
		

		virtual inline void setOnFloor(bool val) {mOnFloor = val;}
		virtual inline bool getOnFloor() const {return mOnFloor;}
		virtual inline bool isOnFloor() const {return getOnFloor();}
		
		virtual inline void setIsBumpObstacle(bool val) {mIsBumpObstacle = val;}
		virtual bool getIsBumpObstacle() const {return mIsBumpObstacle;}
		virtual bool IsBumpObstacle() const {return mIsBumpObstacle;}

		virtual inline void setIsOnObstaclePlane(bool val) {mOnObstaclePlane = val;}
		virtual bool getIsOnObstaclePlane() const {return mOnObstaclePlane;}
		virtual bool IsOnObstaclePlane() const {return getIsOnObstaclePlane();}
		
		std::deque<std::pair<Ogre::Vector3,Ogre::Real> > mCollisionConditionVectors;

	protected:

		bool mOnFloor;
		bool mIsBumpObstacle;
		bool mOnObstaclePlane;

		ObstacleManager* mManager;
		OgreBulletDynamics::RigidBody* mBody;
		OgreBulletCollisions::CollisionShape* mShape;
		Ogre::Real mRestitution;
		Ogre::Real mFriction;
		Ogre::Real mMass;
		Ogre::SceneNode* mNode;
		Ogre::Entity* mEntity;

		Ogre::Vector3 mScaleDifference;

		virtual OgreBulletCollisions::CollisionShape* generateFittingShape(Ogre::SceneNode* node, Ogre::Entity* ent); 

	private:
	};
};

#endif