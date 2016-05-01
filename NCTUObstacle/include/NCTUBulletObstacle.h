#ifndef NCTU_BULLET_OBSTACLE_h_
#define NCTU_BULLET_OBSTACLE_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacle.h"


namespace NCTU{
	// -------------------------------------------------------------
	class BulletObstacle : public Obstacle{
	public:
		BulletObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,INDEX_TYPE index,const Ogre::Vector3& position,Ogre::Real radius,const Ogre::Quaternion& orientation);
		virtual void setScale(const Ogre::Vector3&);
		virtual inline void setBulletIterator(std::list<BulletObstacle *>::iterator it){mBulletIterator = it;}
		virtual void onBulletHit();
		virtual inline bool isAlive() const;
		virtual inline void cleanUp();
	protected:
		int mIndex;
		Ogre::Real mRadius;
		std::list<BulletObstacle *>::iterator mBulletIterator;
		bool mHit;

		virtual inline void onLifeEnd();
	};
};

#endif