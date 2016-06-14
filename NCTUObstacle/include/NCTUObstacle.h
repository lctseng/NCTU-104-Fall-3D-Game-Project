#ifndef NCTU_OBSTACLE_h_
#define NCTU_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#define FLOOR_TOUCH_THRESHOLD 20
#define OBSTACLE_PLANE_TOUCH_THRESHOLD 10
#define FLOOR_TOUCH_STRICT_THRESHOLD 1
#define OBSTACLE_PLANE_TOUCH_STRICT_THRESHOLD 1

#include <deque>
#include <list>
#include <map>

namespace NCTU{

	struct ParticleSystemPack{
		bool mParticleSystemInit;
		Ogre::SceneNode* mParticleSystemNode;
		Ogre::ParticleSystem* mParticleSystem;
		Ogre::String mParticleSystemName;
		ParticleSystemPack():
				mParticleSystemInit(false),
				mParticleSystemNode(nullptr),
				mParticleSystem(nullptr),
				mParticleSystemName()
			{}
	};


	// -------------------------------------------------------------
	class Obstacle{
	public:
		Obstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction,Ogre::Real mass);
		Obstacle(const Obstacle&);
		virtual ~Obstacle();
		
		virtual void setScale(const Ogre::Vector3&);
		virtual void updateCollision(const Ogre::FrameEvent& evt){};
		virtual void updateLifeTime(const Ogre::FrameEvent& evt);
		virtual void updatePlayingGame(const Ogre::FrameEvent& evt);

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
		virtual inline bool getOnFloor(int threshold = FLOOR_TOUCH_THRESHOLD) const {return mFloorTouchValue < FLOOR_TOUCH_THRESHOLD;}
		virtual inline bool isOnFloor(int threshold = FLOOR_TOUCH_THRESHOLD) const {return getOnFloor(threshold);}
		
		virtual inline void setIsBumpObstacle(bool val) {mIsBumpObstacle = val;}
		virtual bool getIsBumpObstacle() const {return mIsBumpObstacle;}
		virtual bool IsBumpObstacle() const {return mIsBumpObstacle;}

		virtual void onBulletHit(BulletObstacle*, Obstacle*);

		virtual inline void setIsOnObstaclePlane(bool val);
		virtual inline bool getIsOnObstaclePlane(int threshold = OBSTACLE_PLANE_TOUCH_THRESHOLD) const {return mObstaclePlaneTouchValue < threshold;}
		virtual inline bool IsOnObstaclePlane(int threshold = OBSTACLE_PLANE_TOUCH_THRESHOLD) const {return getIsOnObstaclePlane(threshold);}
		

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

		virtual void initParticleSystem(const Ogre::String& particleName, int index = 0);
		virtual void setOffParticleSystem(int index = 0);
		virtual void stopParticleSystem(int index = 0);
		virtual void destroyParticleSystem();

		virtual inline HpType getHpType()const {return mHpType;}
		virtual int decreaseHp(int value = 1);
		virtual inline void setBumpSpeed(Ogre::Real val){mBumpSpeed = val;}
		virtual inline Ogre::Real getBumpSpeed() const {return mBumpSpeed;}

		virtual inline ObstacleManager* getManager(){return mManager;}

		virtual void setCurrentObstacle(Obstacle* obj);
		virtual inline void setTurnType(const Ogre::String& v){mTurnType = v;}
		virtual inline const Ogre::String& getTurnType() const {return mTurnType;}

		virtual inline void setTurnUsed(bool v){mTurnUsed = v;}
		virtual inline bool getTurnUsed() const {return mTurnUsed;}

		virtual inline const Ogre::String& getName() const {return mName;}
		virtual bool canBeShoot() const{ return true;}
		virtual bool canStandOn() const{ return true;}
		virtual bool canCauseDead() const{ return true;}

		virtual void destroy();
		virtual void freeze() {mFrozen = true;}
		virtual void unfreeze() {mFrozen = false;}

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
		Ogre::String mTurnType;
		bool mTurnUsed;

		bool mFrozen;
		

		std::list<Obstacle *>::iterator mMyIterator;

		Obstacle* mCurrentObstacle;
		Ogre::Real mCurrentObstacleValid;

		// particle system
		std::deque<ParticleSystemPack> mParticleSystems;


		virtual OgreBulletCollisions::CollisionShape* generateFittingShape(Ogre::SceneNode* node, Ogre::Entity* ent); 
		virtual OgreBulletCollisions::CollisionShape* generateConvexShape(Ogre::SceneNode* node, Ogre::Entity* ent); 
		


	private:
	};
};

#endif