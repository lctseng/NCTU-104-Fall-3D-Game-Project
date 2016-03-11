/*
Author: Sai-Keung Wong

Date: 2010/9/25
National Chiao-Tung University
*/
#ifndef __OgrePhysEngine_H__
#define __OgrePhysEngine_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include "PhysEngine.h"

namespace ns_phys {
	class OgrePhysEngine : public PhysEngine {
public:
	OgrePhysEngine();
protected:
private:
};
};
#endif