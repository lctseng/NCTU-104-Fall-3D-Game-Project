#include "GameClient.h"

namespace ns_phys
{
	GameClient::GameClient()
	{
		mOwnerID = 0;
	}

	void GameClient::setOwner(int a_ObjID)
	{
		mOwnerID = a_ObjID;
	}


	int GameClient::addObj(float x, float y, float z)
	{
		int objID = 0;
		objID = mPhysEngine->addObj(x, y, z);
		return objID;
	}
};