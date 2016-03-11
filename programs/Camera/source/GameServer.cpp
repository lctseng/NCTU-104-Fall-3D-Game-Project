#include "GameServer.h"

namespace ns_phys
{
	GameServer::GameServer()
	{
		mPhysEngine = 0; // pointer
		init();
	}

	void GameServer::init()
	{
		mPhysEngine = new PhysEngine;

	}
	int GameServer::addObj(float x, float y, float z)
	{
		int objID = 0;
		objID = mPhysEngine->addObj(x, y, z);
		return objID;
	}

	int GameServer::addObj(float x, float y, float z, float vx, float vy, float vz)
	{
		int objID = 0;
		objID = mPhysEngine->addObj(x, y, z, vx, vy, vz);
		return objID;

	}

	int GameServer::addObj(float x, float y, float z, float vx, float vy, float vz, float radius)
	{
		int objID = 0;
		objID = mPhysEngine->addObj(x, y, z, vx, vy, vz, radius);
		return objID;

	}

	void GameServer::registerClient(GameClient *a_GameClient)
	{

	}

	void GameServer::forward()
	{
		mPhysEngine->forward();
	}


};

