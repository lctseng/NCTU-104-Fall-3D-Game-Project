#ifndef NCTU_OBSTACLE_PRE_REQUISITES_h_
#define NCTU_OBSTACLE_PRE_REQUISITES_h_

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


#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"

#include "Shapes/OgreBulletCollisionsSphereShape.h"       // for Spheres
#include "Shapes/OgreBulletCollisionsBoxShape.h"       // for Boxes
#include "Shapes/OgreBulletCollisionsGImpactShape.h"
#include "Shapes/OgreBulletCollisionsTriMeshShape.h"
#include "Shapes/OgreBulletCollisionsConvexHullShape.h"


#include "btBulletCollisionCommon.h"

#define COL_MASK_PLAYER 0x1
#define COL_MASK_OBSTACLE 0x2
#define COL_MASK_FLOOR 0x4
#define COL_MASK_BULLET 0x8

#define COL_GROUP_ALL (COL_MASK_PLAYER | COL_MASK_OBSTACLE | COL_MASK_FLOOR | COL_MASK_BULLET)
#define COL_GROUP_NO_BULLET (COL_MASK_PLAYER | COL_MASK_OBSTACLE | COL_MASK_FLOOR)

typedef unsigned long INDEX_TYPE;

namespace NCTU{

	class ObstacleManager;
	class Obstacle;
	class SphereObstacle;
	class CubeObstacle;
	class GeneralObstacle;
	class FloorObstacle; // specialized
	class PlayerObstacle; // a player
	class BulletObstacle;

};

template<class Key, class Value>
class propMap : public std::map<Key,Value>{
public:
	bool hasKey(const Key& key) const{
		return this->find(key) != this->end();
	}
};




#endif