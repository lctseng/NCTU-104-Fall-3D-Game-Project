#include "OgreGamePlatform.h"

using namespace Ogre;
namespace ns_phys {
	OgreGamePlatform::OgreGamePlatform()
	{
	}

	void OgreGamePlatform::createDefaultObjs(Ogre::SceneManager* a_SceneMgr)
	{
		mSceneMgr = a_SceneMgr;
    Ogre::Entity* entNinja = a_SceneMgr->createEntity("_Ninja", "ninja.mesh");
   // entNinja->setCastShadows(true);
	SceneNode *snode;
    snode = a_SceneMgr->getRootSceneNode()->createChildSceneNode();
	snode->attachObject(entNinja);
	snode->translate(Vector3(20, 20, 20));

	}

	void OgreGamePlatform::setupServerClients()
	{
		mOgreGameServer = new OgreGameServer;
		mMaxNumClients = 2;
	mOgreGameClientsArr = new OgreGameClient*[mMaxNumClients];
	mCurNumClients = 2;
	for (int i = 0; i < mCurNumClients; ++i) {
mOgreGameClientsArr[i] = new OgreGameClient;
	}


	int objID;
	objID = mOgreGameServer->addObj(80, 0, -80, 2, 0.0, 2, 10);

	objID = mOgreGameServer->addObj(-80, 0, 80, 2, 0.0, -2, 15);

	objID = mOgreGameServer->addObj(-80, 0, -80, 2, 0.0, 2, 30);
	
	objID = mOgreGameServer->addObj(60, 0, 300, -2, 0.0, 2, 20);
	mOgreGameClientsArr[0]->setOwner(objID);

	objID = mOgreGameServer->addObj(300, 0, 60, -1.5, 0.0, -2);
	mOgreGameClientsArr[1]->setOwner(objID);


	mOgreGameServer->registerClient(mOgreGameClientsArr[0]);
	mOgreGameServer->registerClient(mOgreGameClientsArr[1]);
	//
	mOgreGameServer->setSceneManager(mSceneMgr);
	mOgreGameServer->createObjForRendering();
	}

	void OgreGamePlatform::handleKeyboardEvents(int key, bool state)
	{
	}
	void OgreGamePlatform::updateSimulation()
	{

		mOgreGameServer->forward();
		mOgreGameServer->prepareRendering();
	}
};