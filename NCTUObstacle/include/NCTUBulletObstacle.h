#ifndef NCTU_BULLET_OBSTACLE_h_
#define NCTU_BULLET_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacle.h"

namespace NCTU{
	// -------------------------------------------------------------
	/*! 
	\brief bullet obstacle
	*/
	class BulletObstacle : public Obstacle{
	public:
		/*! 
		\brief constructor
		*/
		BulletObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,INDEX_TYPE index, HpType bulletType,const Ogre::Vector3& position,Ogre::Real radius,const Ogre::Quaternion& orientation);
		/*! 
		\brief set obstacle scale
		*/
		virtual void setScale(const Ogre::Vector3&);
		/*! 
		\brief set bullet interator for manager
		*/
		virtual inline void setBulletIterator(std::list<BulletObstacle *>::iterator it){mBulletIterator = it;}
		/*! 
		\brief process when bullet hit
		*/
		virtual void onBulletHit(BulletObstacle*, Obstacle*);
		/*! 
		\brief is bullet alive?
		*/
		virtual inline bool isAlive() const;
		/*! 
		\brief clean up routine
		*/
		virtual inline void cleanUp();
		/*! 
		\brief get the bullet hp type
		*/
		virtual inline HpType getBulletType()const {return mBulletType;}
		/*! 
		\brief update life time
		*/
		virtual void updateLifeTime(const Ogre::FrameEvent& evt);
		/*! 
		\brief is this object can be shoot?
		*/
		virtual bool canBeShoot() const{ return false;}
		/*! 
		\brief is this object can be standed on?
		*/
		virtual bool canStandOn() const{ return false;}
		/*! 
		\brief is this object can cause dead?
		*/
		virtual bool canCauseDead() const{ return false;}
		/*! 
		\brief set handler when bullet hit
		*/
		static void setHandlerBulletHit(BulletHitHandler handler){mBulletHitHandler = handler;};
	protected:
		/*! 
		\brief object index
		*/
		int mIndex;
		/*! 
		\brief bullet radius
		*/
		Ogre::Real mRadius;
		/*! 
		\brief iterator for manager
		*/
		std::list<BulletObstacle *>::iterator mBulletIterator;
		/*! 
		\brief is bullet hit something?
		*/
		bool mHit;
		/*! 
		\brief the hp type for bullet
		*/
		HpType mBulletType;
		/*! 
		\brief process when life ended
		*/
		virtual inline void onLifeEnd();
		/*! 
		\brief the bullet-hit handler
		*/
		static BulletHitHandler mBulletHitHandler;
		/*! 
		\brief life time for particle system
		*/
		Ogre::Real mParticleLifeTime;
	};
};

#endif