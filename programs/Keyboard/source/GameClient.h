/*
Author: Sai-Keung Wong

Date: 2010/9/25
National Chiao-Tung University
*/
#ifndef __GameClient_H__
#define __GameClient_H__
#include "PhysEngine.h"
namespace ns_phys {
class GameClient {
public:
	GameClient();
	void setOwner(int a_ObjID);
	int addObj(float x, float y, float z);
protected:
	int mOwnerID;
	PhysEngine *mPhysEngine;
	void init();
private:
};
};
#endif