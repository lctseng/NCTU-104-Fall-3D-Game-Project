/*
Author: Sai-Keung Wong

Date: 2010/9/25
National Chiao-Tung University
*/
#ifndef __PhysEngine_H__
#define __PhysEngine_H__
#include "maths/vector3.h"
#include "GameObj.h"
namespace ns_phys {
class PhysEngine {
public:
	PhysEngine();
	void forward();
	void backward();
	void forwardWithSteps(int nStep);
	void backwardWithSteps(int nStep);
	void forwardToStep(int step);
	void backwardToStep(int step);
	int addObj(float x, float y, float z);
	int addObj(float x, float y, float z, float vx, float vy, float vz);
	int addObj(float x, float y, float z, float vx, float vy, float vz, float radius);
	int getNumOfObjs() const;
	GameObject *getObj(int a_ID) const;

protected:
	float mTimeStep;
	void adjustVelocityDueToCollision(float a_TimeStep, GameObject *g0, GameObject *g1);
	void adjustVelocityDueToCollision(float a_TimeStep);

private:
	void init();
private:
	int mFlgInit;
	GameObject **mGameObjArr;
	int mCurNumGameObj;
	int mMaxNumGameObj;
	vector3 *mPositionArrHistory;
	vector3 *mVelocityArrHistory;
	int mCurIndexHistory;
	int mCurTotalHistory;
	int mMaxIndexHistory;
};
};
#endif