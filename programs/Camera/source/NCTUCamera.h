
#ifndef NCTUCamera_H
#define NCTUCamera_H


#define turnRight 0
#define turnLeft 1

#include <OgreCamera.h>
#include <math.h>
#include <OgreSceneManager.h>

using namespace Ogre;

class NCTUCamera{

private:
	Camera *mCamera;
	SceneManager *mSceneMgr;
	Vector3 mCameraIniPosition;
	Vector3 mTargetIniPosition;
	SceneNode *Parent;

public:
	NCTUCamera(Camera *camera, SceneManager *SceneMgr);
	~NCTUCamera(void);
	void TurnCamera(bool direction, Vector3 Target);

};


#endif