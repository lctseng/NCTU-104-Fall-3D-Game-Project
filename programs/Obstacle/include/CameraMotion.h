#ifndef __CAMERA_MOTION_H
#define __CAMERA_MOTION_H

#include <deque>
#include <OgreCamera.h>

class CameraMotion{
public:
	static const int MAX_RECORD = 10;
	static const int REQ_COUNT = 8;
	void record(const Ogre::Vector3& v);
	bool isDown() const;
private:
	std::deque<bool> motionData;
	bool result;
};


#endif