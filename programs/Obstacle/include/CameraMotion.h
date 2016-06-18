#ifndef __CAMERA_MOTION_H
#define __CAMERA_MOTION_H

#include <deque>
#include <OgreCamera.h>

/*!
\brief A class that stores and indicates that the player motion
*/
class CameraMotion{
public:
	/*!
	\brief how many motion record stored interally
	*/
	static const int MAX_RECORD = 10;
	/*!
	\brief threshold for motion jugdement
	*/
	static const int REQ_COUNT = 8;
	/*!
	\brief record the motion information from Vector3
	*/
	void record(const Ogre::Vector3& v);
	/*!
	\brief return whether the motion is down or not
	*/
	bool isDown() const;
private:
	std::deque<bool> motionData;
	bool result;
};


#endif