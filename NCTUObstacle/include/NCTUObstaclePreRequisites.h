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




#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include "Utils/OgreBulletConverter.h"

#include "OgreBulletDynamicsRigidBody.h"




#include "btBulletCollisionCommon.h"



namespace NCTU{

	class ObstacleManager;
	class Obstacle;
	class SphereObstacle;
	class CubeObstacle;
	class FloorObstacle; // specialized
	class PlayerObstacle; // a player (by default, a ball)

};



#endif