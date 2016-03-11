/*
Author: Sai-Keung Wong

Date: 2010/9/25
National Chiao-Tung University
*/
#ifndef __GameObject_H__
#define __GameObject_H__
#include "./maths/vector3.h"
namespace ns_phys {
class GameObject {
public:
	GameObject();
	GameObject(float x, float y, float z);
//
	void setPosition(float x, float y, float z);
	void setVelocity(float x, float y, float z);
	void setVelocity(const vector3 &v);
	void setVelocity_X(float v);
	void setVelocity_Y(float v);
	void setVelocity_Z(float v);

	void setRadius(float r);
	vector3 getPosition() const;
	vector3 getVelocity() const;
	float getRadius() const;
	float getMass() const;
	//
	void negVelocity();
	void negVelocity_X();
	void negVelocity_Y();
	void negVelocity_Z();


	void update(float a_TimeStep);
	void update_X(float a_TimeStep);
	void update_Y(float a_TimeStep);
	void update_Z(float a_TimeStep);
	void showPosition() const;
protected:
	float mRadius;
	float mMass;
	vector3 mPosition;
	vector3 mVelocity;
	void init();
private:
	
	//

private:
	
};
};
#endif