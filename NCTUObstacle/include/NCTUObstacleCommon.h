#ifndef NCTU_OBSTACLE_COMMON_h_
#define NCTU_OBSTACLE_COMMON_h_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <deque>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include "OgreBulletDynamicsRigidBody.h"
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h" // for static planes
#include "Shapes/OgreBulletCollisionsBoxShape.h"       // for Boxes
#include "Shapes/OgreBulletCollisionsSphereShape.h"       // for Spheres


namespace NCTU{

	class ObstacleManager;
	class Obstacle;
	class SphereObstacle;
	class CubeObstacle;
	class FloorObstacle; // specialized
	class PlayerObstacle; // a player (by default, a ball)
	// -------------------------------------------------------------
	class Obstacle{
	public:
		Obstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction,Ogre::Real mass);
		Obstacle(const Obstacle&);
		virtual ~Obstacle();
		
		inline Ogre::SceneNode* getSceneNode(){return mNode;}
		inline Ogre::Entity* getEntity(){return mEntity;}

		inline void setVelocity(const Ogre::Vector3 v){mBody->setLinearVelocity(v);}
		inline Ogre::Vector3 getVelocity() const {return mBody->getLinearVelocity();}
		inline void applyVelocityChange(const Ogre::Vector3 v){setVelocity(getVelocity() + v);}


		inline void setPosition(const Ogre::Vector3 v){mBody->setPosition(v);}


	protected:
		ObstacleManager* mManager;
		OgreBulletDynamics::RigidBody* mBody;
		OgreBulletCollisions::CollisionShape* mShape;
		Ogre::Real mRestitution;
		Ogre::Real mFriction;
		Ogre::Real mMass;
		Ogre::SceneNode* mNode;
		Ogre::Entity* mEntity;
	private:
	};
	// -------------------------------------------------------------
	class FloorObstacle : public Obstacle{
	public:
		FloorObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction,const Ogre::Vector3& normal,Ogre::Real distance);
		FloorObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction,Ogre::Plane& plane,Ogre::Entity* entity);
	protected:
		Ogre::Vector3 mNormal;
		Ogre::Real mDistance;
		Ogre::Plane mPlane;
	};
	// -------------------------------------------------------------
	class PlayerObstacle : public Obstacle{
	public:
		PlayerObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass);
	protected:

	};
	// -------------------------------------------------------------
	class CubeObstacle : public Obstacle{
	public:
		CubeObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,int index,const Ogre::Vector3& position,const Ogre::Vector3& size,const Ogre::Quaternion& orientation);
	protected:
		int mIndex;
	};
	// -------------------------------------------------------------
	class SphereObstacle : public Obstacle{
	public:
		SphereObstacle(ObstacleManager* mgmt,Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,int index,const Ogre::Vector3& position,Ogre::Real radius,const Ogre::Quaternion& orientation);
	protected:
		int mIndex;
	};
	// -------------------------------------------------------------
	class ObstacleManager{
	public:
		ObstacleManager();
		ObstacleManager(const ObstacleManager&);
		~ObstacleManager();

		void setup(Ogre::SceneManager*,const Ogre::AxisAlignedBox& bound,const Ogre::Vector3 g);
		
		FloorObstacle* createFloor(const Ogre::Vector3& normal,Ogre::Real distance,Ogre::Real restitution, Ogre::Real friction);
		FloorObstacle* createFloor(Ogre::Plane& plane,Ogre::Entity* entity,Ogre::Real restitution, Ogre::Real friction);
		PlayerObstacle* createPlayer(Ogre::Real restitution, Ogre::Real friction,Ogre::Real mass);

		CubeObstacle* createCube(Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,const Ogre::Vector3& position,const Ogre::Vector3& size = Ogre::Vector3::ZERO,const Ogre::Quaternion& orientation = Ogre::Quaternion(0,0,0,1));
		SphereObstacle* createSphere(Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,const Ogre::Vector3& position,Ogre::Real radius = 1.0f,const Ogre::Quaternion& orientation = Ogre::Quaternion(0,0,0,1));


		inline OgreBulletDynamics::DynamicsWorld* getWorld(){return mWorld;}
		inline Ogre::SceneManager* getSceneMgr(){return mSceneMgr;}
		inline PlayerObstacle* getPlayer(){return mPlayerObstacle;}
		inline FloorObstacle* getFloor(){return mFloorObstacle;}

		inline void stepSimulation(Ogre::Real time){mWorld->stepSimulation(time);}
		

	private:
		// Core
		Ogre::SceneManager* mSceneMgr;

		// General
		std::deque<Obstacle*> mObstacles;  // Store all obstacle except plane and player
		Ogre::AxisAlignedBox  mBulletBox; // box for bullet
		Ogre::Vector3 mGravityVector; // gravity for bullet
		OgreBulletDynamics::DynamicsWorld *mWorld;   // OgreBullet World
		OgreBulletCollisions::DebugDrawer *mDebugDrawer; // bullet debug
		// special pointer for floor
		FloorObstacle* mFloorObstacle;
		// special pointer for Player
		PlayerObstacle* mPlayerObstacle;

		int mObstacleIndex; // general obstacle
	};
};
#endif