
#ifndef NCTUCamera_H
#define NCTUCamera_H


#include <OgreCamera.h>
#include "CameraMotion.h"
#include <math.h>
#include <deque>
#include <OgreSceneManager.h>

#include "NCTUPreRequisite.h"

using namespace Ogre;



/*!
\brief Camera controller for this project
*/
class NCTUCamera{
public:
	/*!
	\brief state declaration of turning / normal
	*/
	enum TurningState { STATE_TURNING, STATE_NORMAL};
	/*!
	\brief turning time 
	*/
	static const Real TURNING_TIME;
private:

	Camera *mCamera;
	SceneManager *mSceneMgr;
	Vector3 mCameraIniPosition;
	Vector3 mTargetIniPosition;
	SceneNode *Parent;
	BasicTutorial_00* mApp;
	CameraMotion mCameraMotion;

	TurningState mTurningState;
	std::deque<int> mAngleLeft;
	Real mTurningInterval;


public:
	/*!
	\brief constructor
	*/
	NCTUCamera();
	/*!
	\brief destructor
	*/
	~NCTUCamera(void){};
	/*!
	\brief initialize the camera controller with pointers
	*/
	void setup(Camera *camera, SceneManager *SceneMgr, BasicTutorial_00 *app);
	/*!
	\brief turn the camera
	*/
	void TurnCamera(bool direction, Vector3 Target);
	/*!
	\brief basic update routine
	*/
	void updateBasic(const FrameEvent& evt);
	/*!
	\brief update routine for playing game
	*/
	void updatePlayingGame(const FrameEvent& evt);
	/*!
	\brief setup controller
	*/
	void setupCamera();
	/*!
	\brief is turning ok for now?
	*/
	bool isTurnOK() const;
	/*!
	\brief get the camera motion instance
	*/
	CameraMotion& getMotion(){return mCameraMotion;}
	/*!
	\brief camera position offset
	*/
	Vector3 mCameraPositionOffset;
	/*!
	\brief camera lookAt offset
	*/
	Vector3 mCameraLookAtOffset;
	/*!
	\brief camera initial lookAt
	*/
	Vector3 mCameraInitLookAt;
	/*!
	\brief camera initial position
	*/
	Vector3 mCameraInitPosition;
	/*!
	\brief camera initial orientation
	*/
	Quaternion mInitOrientation;
	/*!
	\brief minimum near clip distance
	*/
	int mNearClipMin;
	/*!
	\brief maximum near clip distance
	*/
	int mNearClipMax;
};


#endif