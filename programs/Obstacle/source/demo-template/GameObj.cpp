#include <iostream>
#include "GameObj.h"
namespace ns_phys {
	GameObject::GameObject()
	{
		init();
	}
	GameObject::GameObject(float x, float y, float z)
	{
		init();
		setPosition(x, y, z);
		mVelocity = vector3(0, 0, 0); 

	}
	void GameObject::init()
	{
		mRadius = 50.0;
		mPosition = vector3(0, 0, 0);
		mVelocity = vector3(0, 0, 0);
		mMass = 1.0;
	}

	void GameObject::setPosition(float x, float y, float z)
	{
		mPosition = vector3(x, y, z);
	}

	void GameObject::setVelocity_X(float v)
	{
mVelocity.x = v;
	}
	void GameObject::setVelocity_Y(float v)
	{
mVelocity.y = v;
	}
	void GameObject::setVelocity_Z(float v)
	{
mVelocity.z = v;
	}
	void GameObject::setVelocity(const vector3 &v)
	{
		mVelocity = v;
	}

	void GameObject::setVelocity(float x, float y, float z)
	{
		mVelocity = vector3(x, y, z);
	}

	void GameObject::setRadius(float r)
	{
		mRadius = r;
	}

	vector3 GameObject::getPosition() const
	{
		return mPosition;
	}

	vector3 GameObject::getVelocity() const
	{
		return mVelocity;
	}

	float GameObject::getMass() const
	{
		return mMass;
	}

	float GameObject::getRadius() const
	{
		return mRadius;
	}

	void GameObject::negVelocity()
	{
		mVelocity = -mVelocity;
	}

	void GameObject::negVelocity_X()
	{
		mVelocity.x = -mVelocity.x;
	}

	void GameObject::negVelocity_Y()
	{
		mVelocity.y = -mVelocity.y;
	}
	void GameObject::negVelocity_Z()
	{
		mVelocity.z = -mVelocity.z;
	}

	void GameObject::update(float a_TimeStep)
	{
		mPosition += mVelocity*a_TimeStep;
	}

	void GameObject::update_X(float a_TimeStep)
	{
		mPosition.x += mVelocity.x*a_TimeStep;
	}

	void GameObject::update_Y(float a_TimeStep)
	{
		mPosition.y += mVelocity.y*a_TimeStep;
	}
	void GameObject::update_Z(float a_TimeStep)
	{
		mPosition.z += mVelocity.z*a_TimeStep;
	}
	void GameObject::showPosition() const
	{
		std::cout << "Position:" 
			<< mPosition.x 
			<< "\t" << mPosition.y 
			<< "\t" << mPosition.z 
			<< std::endl;
	}
};