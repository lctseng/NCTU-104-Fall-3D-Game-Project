#include <iostream>
#include "PhysEngine.h"

namespace ns_phys {

	PhysEngine::PhysEngine()
	{
		mFlgInit = false;
		mGameObjArr = 0; //pointer
		mCurNumGameObj = 0;
		mMaxNumGameObj = 0;
		mPositionArrHistory = 0; //pointer
		mVelocityArrHistory = 0; //pointer
		mCurIndexHistory = 0;
		mCurTotalHistory = 0;
		mMaxIndexHistory = 0;

		//
		mTimeStep = 0.1;
		init();
	}

	void PhysEngine::init()
	{
		if (mFlgInit) return;
		mFlgInit = true;
		mCurNumGameObj = 0;
		mMaxNumGameObj = 10;
		mGameObjArr = new GameObject*[mMaxNumGameObj];
		//
		mMaxIndexHistory = 2000;
		mPositionArrHistory = new vector3[mMaxIndexHistory];
		mVelocityArrHistory = new vector3[mMaxIndexHistory];
		mCurIndexHistory = 0;
		mCurTotalHistory = 0;

	}

	bool isCollideSphere(GameObject *g0, GameObject *g1)
	{

		float r0 = g0->getRadius();
		float r1 = g1->getRadius();
		vector3 p0 = g0->getPosition();
		vector3 p1 = g1->getPosition();
		float d = p0.distance(p1);

		float e = 1.0;
		bool flg = d < r0 + r1 + e; 
		//std::cout << "r0 + r1 + e:" << r0 + r1 + e << std::endl;
		//std::cout << "d:" << d << "\tcollide:" << flg << std::endl;
		return flg;
	}

	void sphereCollisionResponse(GameObject *a, GameObject *b)
	{
		//
		//http://wp.freya.no/websvn/filedetails.php?repname=Public&path=%2Fopengl%2Fcollisiondetect%2Fcollisiondetect.cpp
		//
		vector3 U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;


		float m1, m2, x1, x2;
		vector3 v1temp, v1, v2, v1x, v2x, v1y, v2y, x(a->getPosition() - b->getPosition());

		x.Normalize();
		v1 = a->getVelocity();;
		x1 = x.dot(v1);
		v1x = x * x1;
		v1y = v1 - v1x;
		m1 = a->getMass();

		x = x*-1;
		v2 = b->getVelocity();;
		x2 = x.dot(v2);
		v2x = x * x2;
		v2y = v2 - v2x;
		m2 = b->getMass();

		a->setVelocity( v1x*(m1-m2)/(m1+m2) + v2x*(2*m2)/(m1+m2) + v1y );
		a->setVelocity_Y(0.0);
		b->setVelocity( v1x*(2*m1)/(m1+m2) + v2x*(m2-m1)/(m1+m2) + v2y );
		b->setVelocity_Y(0.0);
	}

	void PhysEngine::adjustVelocityDueToCollision(float a_TimeStep, GameObject *g0, GameObject *g1)
	{
		if (!isCollideSphere(g0, g1)) return;
		//g0->negVelocity();
		//g1->negVelocity();
		sphereCollisionResponse(g0, g1);
		g0->update(a_TimeStep);
		g1->update(a_TimeStep);

	}

	void PhysEngine::adjustVelocityDueToCollision(float a_TimeStep)
	{

		float range = 400;
		for (int i = 0; i < mCurNumGameObj; ++i) {
			GameObject *g = mGameObjArr[i];
			vector3 p = g->getPosition();
			if (p.x < -range) {
				g->negVelocity_X();
				g->update_X(a_TimeStep);
			} else if (p.x > range) 
			{
				g->negVelocity_X();
				g->update_X(a_TimeStep);
			}
			if (p.y < -range) {
				g->negVelocity_Y();
				g->update_Y(a_TimeStep);
			} else if (p.y > range) 
			{
				g->negVelocity_Y();
				g->update_Y(a_TimeStep);
			}
			if (p.z < -range) {
				g->negVelocity_Z();
				g->update_Z(a_TimeStep);
			} else if (p.z > range) 
			{
				g->negVelocity_Z();
				g->update_Z(a_TimeStep);
			}
		}
		for (int i = 0; i < mCurNumGameObj-1; ++i) {
			GameObject *g0 = mGameObjArr[i];

			for (int j = i+1; j < mCurNumGameObj; ++j)
			{
				GameObject *g1 = mGameObjArr[j];
				adjustVelocityDueToCollision(a_TimeStep, g0, g1);
			}
		}
	}

	void PhysEngine::forward()
	{
		float timeStep = mTimeStep;
		for (int i = 0; i < mCurNumGameObj; ++i) {
			//std::cout << i << std::endl;
			GameObject *gameObj = mGameObjArr[i];
			gameObj->update(timeStep);
			//gameObj->showPosition();
		}
		adjustVelocityDueToCollision(timeStep);
	}

	void PhysEngine::backward()
	{
	}
	void PhysEngine::forwardWithSteps(int nStep)
	{
	}
	void PhysEngine::backwardWithSteps(int nStep)
	{
	}
	void PhysEngine::forwardToStep(int step)
	{
	}
	void PhysEngine::backwardToStep(int step)
	{
	}

	int PhysEngine::getNumOfObjs() const
	{
		return mCurNumGameObj;
	}

	int PhysEngine::addObj(float x, float y, float z)
	{
		int objID = mCurNumGameObj;
		++mCurNumGameObj;
		//
		GameObject *gameObj = new GameObject(x, y, z);
		mGameObjArr[objID] = gameObj;
		//
		return objID;
	}
	int PhysEngine::addObj(float x, float y, float z, float vx, float vy, float vz)
	{
		int objID = mCurNumGameObj;
		++mCurNumGameObj;
		//
		GameObject *gameObj = new GameObject(x, y, z);
		gameObj->setVelocity(vx, vy, vz);
		mGameObjArr[objID] = gameObj;
		//
		return objID;
	}

	int PhysEngine::addObj(float x, float y, float z, float vx, float vy, float vz, float radius)
	{
		int objID = mCurNumGameObj;
		++mCurNumGameObj;
		//
		GameObject *gameObj = new GameObject(x, y, z);
		gameObj->setVelocity(vx, vy, vz);
		gameObj->setRadius(radius);
		mGameObjArr[objID] = gameObj;
		//
		return objID;
	}
	GameObject *PhysEngine::getObj(int a_ID) const
	{
		return mGameObjArr[a_ID];
	}
};