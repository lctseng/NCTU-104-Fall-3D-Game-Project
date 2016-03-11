#include "OgreGameServer.h"
#include "BasicTools.h"

using namespace Ogre;
namespace ns_phys
{
	OgreGameServer::OgreGameServer()
	{
		mSceneMgr = 0;
			mCurNumOgreObjs = 0;
	mMaxNumOgreObjs = 0;
	mSceneNodeArr = 0;
	}

	void OgreGameServer::setSceneManager(Ogre::SceneManager* a_SceneMgr)
	{
		mSceneMgr = a_SceneMgr;
	}

	void OgreGameServer::createObjForRendering()
	{
		if (mSceneMgr == 0) return;
		mMaxNumOgreObjs = 100;
		mSceneNodeArr = new SceneNode*[mMaxNumOgreObjs];
		mCurNumOgreObjs = 0;

		int numObjs = mPhysEngine->getNumOfObjs();
		Ogre::String name;
		Ogre::Entity* enode;
		
    
	Ogre::SceneNode *snode;
   

		for (int i = 0; i < numObjs; ++i)
		{
//mSceneMgr->
			genNameUsingIndex("_s", i, name);
			enode = mSceneMgr->createEntity(name, "sphere.mesh");
			 snode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	snode->attachObject(enode);
	//snode->scale(0.5, 0.5, 0.5);
	//
	GameObject *gameObj = mPhysEngine->getObj(i);
	float r = gameObj->getRadius();
			r = r/50.0*0.5;
			snode->scale(r, r, r);
	//
	//snode->translate(Vector3(20, 20, 20));
mSceneNodeArr[mCurNumOgreObjs] = snode;

	++mCurNumOgreObjs;
		}
	}
	void OgreGameServer::prepareRendering()
	{
		int numObjs = mPhysEngine->getNumOfObjs();
		
	Ogre::SceneNode *snode;
   
		for (int i = 0; i < numObjs; ++i)
		{
			GameObject *gameObj = mPhysEngine->getObj(i);
			vector3 pos = gameObj->getPosition();
			snode = mSceneNodeArr[i];
			//snode->scale(1.0, 1.0, 1.0);
			//float r = gameObj->getRadius();
			//r = r/50.0*0.5;
			//snode->scale(r, r, r);
			snode->setPosition(pos.x, pos.y, pos.z);
			//
		}
	}
};