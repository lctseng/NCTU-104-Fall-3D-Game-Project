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
	/*! 
	\brief a pack of particle system variables
	*/
	struct ParticleSystemPack{
		/*! 
		\brief is the particle system initailized?
		*/
		bool mParticleSystemInit;
		/*! 
		\brief the pointer to the particle system scene node
		*/
		Ogre::SceneNode* mParticleSystemNode;
		/*! 
		\brief the pointer to the particle system
		*/
		Ogre::ParticleSystem* mParticleSystem;
		/*! 
		\brief name of particle system
		*/
		Ogre::String mParticleSystemName;
		/*! 
		\brief constructor
		*/
		ParticleSystemPack():
				mParticleSystemInit(false),
				mParticleSystemNode(nullptr),
				mParticleSystem(nullptr),
				mParticleSystemName()
			{}
	};


	// -------------------------------------------------------------
	/*! 
	\brief base class for all obstacle
	*/
	class Obstacle{
	public:
		/*! 
		\brief constructor
		*/
		Obstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction,Ogre::Real mass);
		/*! 
		\brief copy constructor
		*/
		Obstacle(const Obstacle&);
		/*! 
		\brief destructor
		*/
		virtual ~Obstacle();
		/*! 
		\brief set object scale
		*/
		virtual void setScale(const Ogre::Vector3&);
		/*! 
		\brief routine for update collision
		*/
		virtual void updateCollision(const Ogre::FrameEvent& evt){};
		/*! 
		\brief routine for update life time
		*/
		virtual void updateLifeTime(const Ogre::FrameEvent& evt);
		/*! 
		\brief routine for a playing game
		*/
		virtual void updatePlayingGame(const Ogre::FrameEvent& evt);
		/*! 
		\brief get the scene node
		*/
		virtual inline Ogre::SceneNode* getSceneNode(){return mNode;}
		/*! 
		\brief get the entity
		*/
		virtual inline Ogre::Entity* getEntity(){return mEntity;}
		/*! 
		\brief get the bullet rigid body
		*/
		virtual inline OgreBulletDynamics::RigidBody* getBody(){return mBody;}
		/*! 
		\brief git the bullet collision shape
		*/
		virtual inline OgreBulletCollisions::CollisionShape* getShape(){return mShape;}
		/*! 
		\brief set velocity
		*/
		virtual inline void setVelocity(const Ogre::Vector3 v){mBody->setLinearVelocity(v);}
		/*! 
		\brief get velocity
		*/
		virtual inline Ogre::Vector3 getVelocity() const {return mBody->getLinearVelocity();}
		/*! 
		\brief apply velocity change
		*/
		virtual inline void applyVelocityChange(const Ogre::Vector3 v){setVelocity(getVelocity() + v);}
		/*! 
		\brief set position 
		*/
		virtual inline void setPosition(const Ogre::Vector3 v){mBody->setPosition(v); mNode->setPosition(v);}
		/*! 
		\brief get position
		*/
		virtual inline Ogre::Vector3 getPosition() const {return mNode->getPosition();}
		/*! 
		\brief set orientation
		*/
		virtual inline void setOrientation(const Ogre::Quaternion q){mBody->setOrientation(q); mNode->setOrientation(q);}
		/*! 
		\brief get orieatation
		*/
		virtual inline Ogre::Quaternion getOrientation() const {return mNode->getOrientation();}
		/*! 
		\brief set the on floor state
		*/
		virtual inline void setOnFloor(bool val);
		/*! 
		\brief get the on floor state
		*/
		virtual inline bool getOnFloor(int threshold = FLOOR_TOUCH_THRESHOLD) const {return mFloorTouchValue < FLOOR_TOUCH_THRESHOLD;}
		/*! 
		\brief is on floor?
		*/
		virtual inline bool isOnFloor(int threshold = FLOOR_TOUCH_THRESHOLD) const {return getOnFloor(threshold);}
		/*! 
		\brief set the bump obstacle state
		*/
		virtual inline void setIsBumpObstacle(bool val) {mIsBumpObstacle = val;}
		/*! 
		\brief get the bump obstacle state
		*/
		virtual bool getIsBumpObstacle() const {return mIsBumpObstacle;}
		/*! 
		\brief is bump obstacle?
		*/
		virtual bool IsBumpObstacle() const {return mIsBumpObstacle;}
		/*! 
		\brief process on bullet hit
		*/
		virtual void onBulletHit(BulletObstacle*, Obstacle*);
		/*! 
		\brief set on obstacle plane state
		*/
		virtual inline void setIsOnObstaclePlane(bool val);
		/*! 
		\brief get on obstacle plane state
		*/
		virtual inline bool getIsOnObstaclePlane(int threshold = OBSTACLE_PLANE_TOUCH_THRESHOLD) const {return mObstaclePlaneTouchValue < threshold;}
		/*! 
		\brief is on obstacle plane?
		*/
		virtual inline bool IsOnObstaclePlane(int threshold = OBSTACLE_PLANE_TOUCH_THRESHOLD) const {return getIsOnObstaclePlane(threshold);}
		/*! 
		\brief set my iterator for manager
		*/
		virtual inline void setMyIterator(std::list<Obstacle *>::iterator it){mMyIterator = it;}
		/*! 
		\brief clean up routing
		*/
		virtual inline void cleanUp(){}
		/*! 
		\brief process on life ended
		*/
		virtual inline void onLifeEnd();
		/*! 
		\brief destory physics system
		*/
		virtual void destroyPhysics();
		/*! 
		\brief detach entity
		*/
		virtual void detachEntity();
		/*! 
		\brief is alive?
		*/
		virtual inline bool isAlive() const {return !mDeleteMark && !mFrozen;}
		/*! 
		\brief is need to be deleted?
		*/
		virtual inline bool needDeleted()const {return mDeleteMark;}
		/*! 
		\brief set life time
		*/
		virtual inline void setLifeTime(Ogre::Real v){mLifeTimeEnable = true; mLifeTime = v;};
		/*! 
		\brief cancel life time
		*/
		virtual inline void cancelLifeTime(){mLifeTimeEnable = false;};
		/*! 
		\brief set the hit point
		*/
		virtual inline void setHitPoint(int val, HpType type){ mHitPoint = val;mHpType = type;};
		/*! 
		\brief get the hit point
		*/
		virtual inline int getHitPoint() const {return mHitPoint;}
		/*! 
		\brief is invincible?
		*/
		virtual inline bool isInvincible() const {return mHitPoint < 0;}
		/*! 
		\brief initialize the particle system
		*/
		virtual void initParticleSystem(const Ogre::String& particleName, int index = 0);
		/*! 
		\brief set off the particle system
		*/
		virtual void setOffParticleSystem(int index = 0);
		/*! 
		\brief stop the particle system
		*/
		virtual void stopParticleSystem(int index = 0);
		/*! 
		\brief destroy the particle system
		*/
		virtual void destroyParticleSystem();
		/*! 
		\brief get hp type
		*/
		virtual inline HpType getHpType()const {return mHpType;}
		/*! 
		\brief decrease hp
		*/
		virtual int decreaseHp(int value = 1);
		/*! 
		\brief set bump-jump speed
		*/
		virtual inline void setBumpSpeed(Ogre::Real val){mBumpSpeed = val;}
		/*! 
		\brief get bump-jump speed
		*/
		virtual inline Ogre::Real getBumpSpeed() const {return mBumpSpeed;}
		/*! 
		\brief get the obstacle manager
		*/
		virtual inline ObstacleManager* getManager(){return mManager;}
		/*! 
		\brief set current obstacle touched
		*/
		virtual void setCurrentObstacle(Obstacle* obj);
		/*! 
		\brief set turn type
		*/
		virtual inline void setTurnType(const Ogre::String& v){mTurnType = v;}
		/*! 
		\brief get turn type
		*/
		virtual inline const Ogre::String& getTurnType() const {return mTurnType;}
		/*! 
		\brief set turn used state
		*/
		virtual inline void setTurnUsed(bool v){mTurnUsed = v;}
		/*! 
		\brief get turn used state
		*/
		virtual inline bool getTurnUsed() const {return mTurnUsed;}
		/*! 
		\brief get name
		*/
		virtual inline const Ogre::String& getName() const {return mName;}
		/*! 
		\brief is this object can be shoot?
		*/
		virtual bool canBeShoot() const{ return true;}
		/*! 
		\brief is this object can be standed on?
		*/
		virtual bool canStandOn() const{ return true;}
		/*! 
		\brief is this object can cause dead?
		*/
		virtual bool canCauseDead() const{ return true;}
		/*! 
		\brief destory obstacle
		*/
		virtual void destroy();
		/*! 
		\brief freeze the obstacle
		*/
		virtual void freeze() {mFrozen = true;}
		/*! 
		\brief unfreeze the obstacle
		*/
		virtual void unfreeze() {mFrozen = false;}
		/*! 
		\brief array of collision condition vectors
		*/
		std::deque<std::pair<Ogre::Vector3,Ogre::Real> > mCollisionConditionVectors;
		/*! 
		\brief material name for hp change
		*/
		propMap<int,Ogre::String> mHpChangeMaterials;
	protected:
		/*! 
		\brief is bump into obstacle?
		*/
		bool mIsBumpObstacle;
		/*! 
		\brief pointer to the manager
		*/
		ObstacleManager* mManager;
		/*! 
		\brief pointer to the rigid body
		*/
		OgreBulletDynamics::RigidBody* mBody;
		/*! 
		\brief pointer to the collision shape
		*/
		OgreBulletCollisions::CollisionShape* mShape;
		/*! 
		\brief physics restitution
		*/
		Ogre::Real mRestitution;
		/*! 
		\brief physics friction
		*/
		Ogre::Real mFriction;
		/*! 
		\brief physics mass
		*/
		Ogre::Real mMass;
		/*! 
		\brief pointer to scene node
		*/
		Ogre::SceneNode* mNode;
		/*! 
		\brief pointer to entity
		*/
		Ogre::Entity* mEntity;
		/*! 
		\brief obstalce name
		*/
		Ogre::String mName;
		/*! 
		\brief scale difference of object
		*/
		Ogre::Vector3 mScaleDifference;
		/*! 
		\brief floor touch value
		*/
		int mFloorTouchValue;
		/*! 
		\brief obstacle touch value
		*/
		int mObstaclePlaneTouchValue;
		/*! 
		\brief life time
		*/
		Ogre::Real mLifeTime;
		/*! 
		\brief is life time enabled?
		*/
		bool mLifeTimeEnable;
		/*! 
		\brief is need deleted?
		*/
		bool mDeleteMark;
		/*! 
		\brief is entity detached?
		*/
		bool mEntityDetached;
		/*! 
		\brief hit point
		*/
		int mHitPoint;
		/*! 
		\brief hp type
		*/
		HpType mHpType;
		/*! 
		\brief bump-jump speed
		*/
		Ogre::Real mBumpSpeed;
		/*! 
		\brief turn type
		*/
		Ogre::String mTurnType;
		/*! 
		\brief is turn used?
		*/
		bool mTurnUsed;
		/*! 
		\brief is frozen?
		*/
		bool mFrozen;
		/*! 
		\brief iterator for manager
		*/
		std::list<Obstacle *>::iterator mMyIterator;
		/*! 
		\brief pointer to the current obstacle
		*/
		Obstacle* mCurrentObstacle;
		/*! 
		\brief valid time for current obstacle
		*/
		Ogre::Real mCurrentObstacleValid;
		/*! 
		\brief array of particle system
		*/
		std::deque<ParticleSystemPack> mParticleSystems;
		/*! 
		\brief generate fitting bullet collision shape
		*/
		virtual OgreBulletCollisions::CollisionShape* generateFittingShape(Ogre::SceneNode* node, Ogre::Entity* ent); 
		/*! 
		\brief generate convex bullet collision shape
		*/
		virtual OgreBulletCollisions::CollisionShape* generateConvexShape(Ogre::SceneNode* node, Ogre::Entity* ent); 
	};
};

#endif