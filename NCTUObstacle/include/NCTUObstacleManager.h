#ifndef NCTU_OBSTACLE_MANAGER_h_
#define NCTU_OBSTACLE_MANAGER_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacleCallback.h"
#include "NCTUPlayerObstacle.h"
#include "NCTUCubeObstacle.h"
#include "NCTUSphereObstacle.h"
#include "NCTUFloorObstacle.h"
#include "NCTUGeneralObstacle.h"

#include <deque>

namespace NCTU{
	// -------------------------------------------------------------
	class ObstacleManager{
	public:
		ObstacleManager();
		ObstacleManager(const ObstacleManager&);
		~ObstacleManager();

		void setup(Ogre::SceneManager*,const Ogre::AxisAlignedBox& bound,const Ogre::Vector3 g);

		FloorObstacle* createFloor(const Ogre::Vector3& normal,Ogre::Real distance,Ogre::Real restitution, Ogre::Real friction);
		FloorObstacle* createFloor(Ogre::Plane& plane,Ogre::Entity* entity,Ogre::Real restitution, Ogre::Real friction);
		
		// create player
		// direct
		PlayerObstacle* createPlayer(
			Ogre::Real restitution, 
			Ogre::Real friction,
			Ogre::Real mass,
			const Ogre::String& name, 
			Ogre::Vector3 scale = Ogre::Vector3(50.0f,50.0f,50.0f)
			);
		// attach
		PlayerObstacle* createPlayer(
			Ogre::Real restitution, 
			Ogre::Real friction,
			Ogre::Real mass,
			Ogre::SceneNode* node,
			Ogre::Entity* ent
			);

		CubeObstacle* createCube(Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,const Ogre::Vector3& position,const Ogre::Vector3& size = Ogre::Vector3::ZERO,const Ogre::Quaternion& orientation = Ogre::Quaternion(0,0,0,1));
		SphereObstacle* createSphere(Ogre::Real restitution, Ogre::Real friction, Ogre::Real mass,const Ogre::Vector3& position,Ogre::Real radius = 1.0f,const Ogre::Quaternion& orientation = Ogre::Quaternion(0,0,0,1));
		
		GeneralObstacle* createGeneralObstacle(
			Ogre::Real restitution,
			Ogre::Real friction,
			Ogre::Real mass,
			Ogre::SceneNode* node,
			Ogre::Entity* ent
			);

		void setPlayerFloorCallback(btCollisionWorld::ContactResultCallback& callback);
		void setPlayerAllObstacleCallback(btCollisionWorld::ContactResultCallback& callback);

		void updateCollision(const Ogre::FrameEvent& evt);

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