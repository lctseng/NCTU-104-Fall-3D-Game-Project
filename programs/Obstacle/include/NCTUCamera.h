
#ifndef NCTUCamera_H
#define NCTUCamera_H


#define turnRight 0
#define turnLeft 1

#include <OgreCamera.h>
#include "CameraMotion.h"
#include <math.h>
#include <deque>
#include <OgreSceneManager.h>

#include "NCTUPreRequisite.h"

using namespace Ogre;



class NCTUCamera{

private:
	Camera *mCamera;
	SceneManager *mSceneMgr;
	Vector3 mCameraIniPosition;
	Vector3 mTargetIniPosition;
	SceneNode *Parent;
	BasicTutorial_00* mApp;
	CameraMotion mCameraMotion;

public:
	NCTUCamera();
	~NCTUCamera(void){};
	void setup(Camera *camera, SceneManager *SceneMgr, BasicTutorial_00 *app);
	void TurnCamera(bool direction, Vector3 Target);
	void updateBasic(const FrameEvent& evt);
	void updatePlayingGame(const FrameEvent& evt);
	void setupCamera();

	CameraMotion& getMotion(){return mCameraMotion;}

	Vector3 mCameraPositionOffset;
	Vector3 mCameraLookAtOffset;
	Vector3 mCameraInitLookAt;
	Vector3 mCameraInitPosition;

	Quaternion mInitOrientation;

	int mNearClipMin;
	int mNearClipMax;
};


#endif