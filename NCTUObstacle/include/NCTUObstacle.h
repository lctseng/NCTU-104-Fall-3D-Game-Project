#ifndef NCTU_OBSTACLE_h_
#define NCTU_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#define FLOOR_TOUCH_THRESHOLD 5
#define OBSTACLE_PLANE_TOUCH_THRESHOLD 5

#include <deque>
#include <list>
#include <map>

namespace NCTU{
	// -------------------------------------------------------------
	class Obstacle{
	public:
		Obstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction,Ogre::Real mass);
		Obstacle(const Obstacle&);
		virtual ~Obstacle();
		
		virtual void setScale(const Ogre::Vector3&);
		virtual void updateCollision(const Ogre::FrameEvent& evt){};
		virtual void updateLifeTime(const Ogre::FrameEvent& evt);

		virtual inline Ogre::SceneNode* getSceneNode(){return mNode;}
		virtual inline Ogre::Entity* getEntity(){return mEntity;}
		virtual inline OgreBulletDynamics::RigidBody* getBody(){return mBody;}
		virtual inline OgreBulletCollisions::CollisionShape* getShape(){return mShape;}

		virtual inline void setVelocity(const Ogre::Vector3 v){mBody->setLinearVelocity(v);}
		virtual inline Ogre::Vector3 getVelocity() const {return mBody->getLinearVelocity();}
		virtual inline void applyVelocityChange(const Ogre::Vector3 v){setVelocity(getVelocity() + v);}


		virtual inline void setPosition(const Ogre::Vector3 v){mBody->setPosition(v); mNode->setPosition(v);}
		virtual inline Ogre::Vector3 getPosition() const {return mNode->getPosition();}
		
		virtual inline void setOrientation(const Ogre::Quaternion q){mBody->setOrientation(q); mNode->setOrientation(q);}
		virtual inline Ogre::Quaternion getOrientation() const {return mNode->getOrientation();}

		virtual inline void setOnFloor(bool val);
		virtual inline bool getOnFloor() const {return mFloorTouchValue < FLOOR_TOUCH_THRESHOLD;}
		virtual inline bool isOnFloor() const {return getOnFloor();}
		
		virtual inline void setIsBumpObstacle(bool val) {mIsBumpObstacle = val;}
		virtual bool getIsBumpObstacle() const {return mIsBumpObstacle;}
		virtual bool IsBumpObstacle() const {return mIsBumpObstacle;}

		virtual void onBulletHit(BulletObstacle*, Obstacle*);

		virtual inline void setIsOnObstaclePlane(bool val);
		virtual inline bool getIsOnObstaclePlane() const {return mObstaclePlaneTouchValue < OBSTACLE_PLANE_TOUCH_THRESHOLD;}
		virtual inline bool IsOnObstaclePlane() const {return getIsOnObstaclePlane();}
		

		virtual inline void setMyIterator(std::list<Obstacle *>::iterator it){mMyIterator = it;}
		virtual inline void cleanUp(){}
		virtual inline void onLifeEnd();
		virtual void destroyPhysics();
		virtual void detachEntity();

		virtual inline bool isAlive() const {return !mDeleteMark && !mFrozen;}
		virtual inline bool needDeleted()const {return mDeleteMark;}
		virtual inline void setLifeTime(Ogre::Real v){mLifeTimeEnable = true; mLifeTime = v;};
		virtual inline void cancelLifeTime(){mLifeTimeEnable = false;};

		virtual inline void setHitPoint(int val, HpType type){ mHitPoint = val;mHpType = type;};
		virtual inline int getHitPoint() const {return mHitPoint;}
		virtual inline bool isInvincible() const {return mHitPoint < 0;}

		virtual void initParticleSystem(const Ogre::String& particleName);
		virtual void setOffParticleSystem();
		virtual void stopParticleSystem();
		virtual void destroyParticleSystem();

		virtual inline HpType getHpType()const {return mHpType;}
		virtual int decreaseHp(int value = 1);
		virtual inline void setBumpSpeed(Ogre::Real val){mBumpSpeed = val;}
		virtual inline Ogre::Real getBumpSpeed() const {return mBumpSpeed;}

		virtual inline ObstacleManager* getManager(){return mManager;}

		std::deque<std::pair<Ogre::Vector3,Ogre::Real> > mCollisionConditionVectors;
		propMap<int,Ogre::String> mHpChangeMaterials;
	protected:

		bool mIsBumpObstacle;

		ObstacleManager* mManager;
		OgreBulletDynamics::RigidBody* mBody;
		OgreBulletCollisions::CollisionShape* mShape;
		Ogre::Real mRestitution;
		Ogre::Real mFriction;
		Ogre::Real mMass;
		Ogre::SceneNode* mNode;
		Ogre::Entity* mEntity;
		Ogre::String mName;

		Ogre::Vector3 mScaleDifference;

		int mFloorTouchValue;
		int mObstaclePlaneTouchValue;
		Ogre::Real mLifeTime;
		bool mLifeTimeEnable;
		bool mDeleteMark;
		bool mEntityDetached;
		int mHitPoint;
		HpType mHpType;
		Ogre::Real mBumpSpeed;

		bool mFrozen;

		std::list<Obstacle *>::iterator mMyIterator;

		// particle system
		bool mParticleSystemInit;
		Ogre::SceneNode* mParticleSystemNode;
		Ogre::ParticleSystem* mParticleSystem;
		Ogre::String mParticleSystemName;


		virtual OgreBulletCollisions::CollisionShape* generateFittingShape(Ogre::SceneNode* node, Ogre::Entity* ent); 
		virtual void destroy();


	private:
	};
};

#endif