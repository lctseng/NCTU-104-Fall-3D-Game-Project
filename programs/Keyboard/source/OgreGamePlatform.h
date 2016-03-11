#ifndef __OgreGamePlatform_H__
#define __OgreGamePlatform_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

/*
Author: Sai-Keung Wong

Date: 2010/9/25
National Chiao-Tung University
*/
#include "GamePlatform.h"
#include "OgreGameServer.h"
#include "OgreGameClient.h"

namespace ns_phys {
	class OgreGamePlatform : public GamePlatform{
public:
	OgreGamePlatform();
	void createDefaultObjs(Ogre::SceneManager* a_SceneMgr);
	void setupServerClients();
	void updateSimulation();
	void handleKeyboardEvents(int key, bool state);
protected:
	Ogre::SceneManager* mSceneMgr;
	OgreGameServer *mOgreGameServer;
	OgreGameClient **mOgreGameClientsArr;
	int mCurNumClients;
	int mMaxNumClients;
private:
};
};
#endif