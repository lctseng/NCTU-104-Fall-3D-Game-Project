#ifndef NCTU_OBSTACLE_MANAGER_h_
#define NCTU_OBSTACLE_MANAGER_h_

#include "NCTUObstaclePreRequisites.h"
#include "NCTUObstacleCallback.h"
#include "NCTUPlayerObstacle.h"
#include "NCTUCubeObstacle.h"
#include "NCTUSphereObstacle.h"
#include "NCTUBulletObstacle.h"
#include "NCTUPickupObstacle.h"
#include "NCTUFloorObstacle.h"
#include "NCTUGeneralObstacle.h"
#include "NCTUObstacleCallback.h"
#include <OgreSceneManager.h>

#include <list>

namespace NCTU{

	
	// -------------------------------------------------------------
	/*! 
	\brief obstacle manager
	*/
	class ObstacleManager{
	public:
		/*! 
		\brief constructor
		*/
		ObstacleManager();
		/*! 
		\brief copy constructor
		*/
		ObstacleManager(const ObstacleManager&);
		/*! 
		\brief destructor
		*/
		~ObstacleManager();
		/*! 
		\brief setup the manager
		*/
		void setup(BasicTutorial_00* app,Ogre::SceneManager*,const Ogre::AxisAlignedBox& bound,const Ogre::Vector3 g);
		/*! 
		\brief create a floor obstacle
		*/
		FloorObstacle* createFloor(const Ogre::Vector3& normal,Ogre::Real distance,Ogre::Real restitution, Ogre::Real friction);
		/*! 
		\brief create a floor obstacle without creating Ogre3D object
		*/
		FloorObstacle* createFloor(Ogre::Plane& plane,Ogre::Entity* entity,Ogre::Real restitution, Ogre::Real friction);
		
		// create player
		// direct
		/*! 
		\brief create a player obstacle
		*/
		PlayerObstacle* createPlayer(
			Ogre::Real restitution, 
			Ogre::Real friction,
			Ogre::Real mass,
			const Ogre::String& name, 
			Ogre::Vector3 scale = Ogre::Vector3(50.0f,50.0f,50.0f)
			);
		// attach
		/*! 
		\brief create a player obstacle without creating Ogre3D object
		*/
		PlayerObstacle* createPlayer(
			Ogre::Real restitution, 
			Ogre::Real friction,
			Ogre::Real mass,
			Ogre::SceneNode* node,
			Ogre::Entity* ent
			);
		/*! 
		\brief create a cube obstacle
		*/
		CubeObstacle* createCube(
			Ogre::Real restitution,
			Ogre::Real friction,
			Ogre::Real mass,
			const Ogre::Vector3& position,
			const Ogre::Vector3& size = Ogre::Vector3::ZERO,
			const Ogre::Quaternion& orientation = Ogre::Quaternion(0,0,0,1)
			);
		/*! 
		\brief create a sphere obstacle
		*/
		SphereObstacle* createSphere(
			Ogre::Real restitution, 
			Ogre::Real friction,
			Ogre::Real mass,
			const Ogre::Vector3& position,
			Ogre::Real radius = 1.0f,
			const Ogre::Quaternion& orientation = Ogre::Quaternion(0,0,0,1)
			);
		
		/*! 
		\brief create a bullet obstacle
		*/
		BulletObstacle* createBullet(
			Ogre::Real restitution,
			Ogre::Real friction, 
			Ogre::Real mass,
			HpType bulletType,
			const Ogre::Vector3& position,
			Ogre::Real radius = 20.0f,
			const Ogre::Quaternion& orientation = Ogre::Quaternion(0,0,0,1)
			);
		/*! 
		\brief create a pickup obstacle
		*/
		PickupObstacle* createPickup(
			Ogre::SceneNode* node,
			Ogre::Entity* ent
			);

		/*! 
		\brief create a general obstacle
		*/
		GeneralObstacle* createGeneralObstacle(
			Ogre::Real restitution,
			Ogre::Real friction,
			Ogre::Real mass,
			Ogre::SceneNode* node,
			Ogre::Entity* ent
			);
		/*! 
		\brief set player-floor callback
		*/
		void setPlayerFloorCallback(btCollisionWorld::ContactResultCallback& callback);
		/*! 
		\brief set player-all_obstacles callback
		*/
		void setPlayerAllObstacleCallback(btCollisionWorld::ContactResultCallback& callback);
		
		/*! 
		\brief update collision
		*/
		void updateCollision(const Ogre::FrameEvent& evt);
		/*! 
		\brief update life time
		*/
		void updateLifeTime(const Ogre::FrameEvent& evt);
		/*! 
		\brief update bullet collision
		*/
		void updateBulletCollision(const Ogre::FrameEvent& evt);
		/*! 
		\brief update player-pickups collision
		*/
		void updatePlayerPickupsCollision(const Ogre::FrameEvent& evt);
		/*! 
		\brief update pickup effect
		*/
		void updatePickupsEffects(const Ogre::FrameEvent& evt);

		/*! 
		\brief get the bullet world pointer
		*/
		inline OgreBulletDynamics::DynamicsWorld* getWorld(){return mWorld;}
		/*! 
		\brief get the scene manager pointer
		*/
		inline Ogre::SceneManager* getSceneMgr(){return mSceneMgr;}
		/*! 
		\brief get the player obstacle pointer
		*/
		inline PlayerObstacle* getPlayer(){return mPlayerObstacle;}
		/*! 
		\brief get the floor obstacle pointer
		*/
		inline FloorObstacle* getFloor(){return mFloorObstacle;}
		/*! 
		\brief get the pointer to the application
		*/
		inline BasicTutorial_00* getApp(){return mApp;}
		/*! 
		\brief step the simulation for physics
		*/
		void stepSimulation(Ogre::Real time);
		/*! 
		\brief remove the player obstacle
		*/
		void removePlayerObstacle();
		/*! 
		\brief remove the floor obstacle
		*/
		void removeFloorObstacle();
		/*! 
		\brief remove all obstacle
		*/
		void removeAllObstacles();
		/*! 
		\brief the score handler
		*/
		ScoreHandler mScoreHandler;
		/*! 
		\brief delete obstacle by iterator
		*/
		inline std::list<Obstacle *>::iterator deleteByIterator(std::list<Obstacle *>::iterator it){delete *it; return mObstacles.erase(it);}
		/*! 
		\brief delete bullet by iterator
		*/
		inline std::list<BulletObstacle *>::iterator removeBulletIterator(std::list<BulletObstacle *>::iterator it){return mBullets.erase(it);}
		/*! 
		\brief delete pickup by iterator
		*/
		inline std::list<PickupObstacle *>::iterator removePickupIterator(std::list<PickupObstacle *>::iterator it){return mPickups.erase(it);}
	private:
		// Core
		Ogre::SceneManager* mSceneMgr;

		// General
		std::list<Obstacle*> mObstacles;  // Store all obstacle except plane and player
		std::list<BulletObstacle*> mBullets;  // Store all bullet, only for reference
		std::list<PickupObstacle*> mPickups;  // Store all pickup, only for reference

		Ogre::AxisAlignedBox  mBulletBox; // box for bullet
		Ogre::Vector3 mGravityVector; // gravity for bullet
		OgreBulletDynamics::DynamicsWorld *mWorld;   // OgreBullet World
		OgreBulletCollisions::DebugDrawer *mDebugDrawer; // bullet debug
		// special pointer for floor
		FloorObstacle* mFloorObstacle;
		// special pointer for Player
		PlayerObstacle* mPlayerObstacle;

		BasicTutorial_00* mApp;

		INDEX_TYPE mObstacleIndex; // general obstacle
	};
};
#endif