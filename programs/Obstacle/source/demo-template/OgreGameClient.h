/*
Author: Sai-Keung Wong

Date: 2010/9/25
National Chiao-Tung University
*/
#ifndef __OgreGameClient_H__
#define __OgreGameClient_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include "GameClient.h"

namespace ns_phys {
	class OgreGameClient : public GameClient{
public:
	OgreGameClient();
protected:
private:
};
};
#endif