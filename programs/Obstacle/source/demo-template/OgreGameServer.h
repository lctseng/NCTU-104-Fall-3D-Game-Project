/*
Author: Sai-Keung Wong

Date: 2010/9/25
National Chiao-Tung University
*/
#ifndef __OgreGameServer_H__
#define __OgreGameServer_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include "GameServer.h"
#include "OgrePhysEngine.h"
//
namespace ns_phys {
	class OgreGameServer : public GameServer {
public:
	OgreGameServer();
	void setSceneManager(Ogre::SceneManager* a_SceneMgr);
	void createObjForRendering();
	void prepareRendering();
protected:
	OgrePhysEngine *mOgrePhysEngine;
	Ogre::SceneManager* mSceneMgr;
	int mCurNumOgreObjs;
	int mMaxNumOgreObjs;
	Ogre::SceneNode **mSceneNodeArr;
private:
};
};
#endif