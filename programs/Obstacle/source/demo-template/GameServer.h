/*
Author: Sai-Keung Wong

Date: 2010/9/25
National Chiao-Tung University
*/

#ifndef __GameServer_H__
#define __GameServer_H__
#include "PhysEngine.h"
#include "GameClient.h"
namespace ns_phys {
class GameServer {
public:
	GameServer();
	int addObj(float x, float y, float z);
	int addObj(float x, float y, float z, float vx, float vy, float vz);
	int addObj(float x, float y, float z, float vx, float vy, float vz, float radius);
	void registerClient(GameClient *a_GameClient);
	void forward();
protected:
	PhysEngine *mPhysEngine;
	void init();
private:
};
};
#endif