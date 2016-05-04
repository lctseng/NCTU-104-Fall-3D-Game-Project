#ifndef __BASIC_TOOLS_H__
#define __BASIC_TOOLS_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <deque>

extern void genNameUsingIndex(const Ogre::String & prefix, int index, Ogre::String &out_name);
extern void logMessage(const  Ogre::String &msg);
extern void logMessage(const Ogre::Vector3 &v);

class CameraMotion{
public:
	static const int MAX_RECORD = 5;
	static const int REQ_COUNT = 3;
	void record(const Ogre::Vector3& v);
	bool isDown() const;
private:
	std::deque<bool> motionData;
	bool result;
};

#endif