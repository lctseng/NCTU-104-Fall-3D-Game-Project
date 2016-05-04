//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_
 
#include "BaseApplication.h"

// OpenAL & alut
#include "NCTUAudio.h"


#include "DotSceneLoader.h"

//[KEYBOARD]
#include "KeyBoardHandler.h"


using namespace Ogre;

class BasicTutorial_00 : public BaseApplication
{
private:
protected:
	virtual void createCamera(void);
	virtual bool frameStarted(const FrameEvent& evt);
	// [NEW]
	virtual bool processUnbufferedKeyInput(const FrameEvent& evt);
	
	// [NEW]
	virtual Real speedAdjustment(const Vector3& old,const Vector3& go);
	// [NEW]
	virtual void checkCollision(const FrameEvent& evt);

	// [NEW]
	virtual void updateLightPosition(const FrameEvent& evt);
	virtual void updateCameraPosition(const FrameEvent& evt);

	// [NEW]
	virtual void equalizeSpeed(const FrameEvent& evt);
	virtual void fixOrientation(const FrameEvent& evt);

	// [NEW]
	NCTU::ObstacleManager* mObstacleMgr;

	// [NEW]
	// Games
	Vector3 mInitVelocity;
	Vector3 mInitPosition;
	Quaternion mInitOrientation;
	NCTU::PlayerObstacle* mPlayerObstacle;
	Light *mLight;

	//[KEYBOARD]
	KeyBoardHandler *keyboardhandler;

	// settings
	bool mEnableCollision;
	bool mEnableFreeMode;
	bool mDisableLose;

	int mNearClipMin;
	int mNearClipMax;

	bool mGameStarted;
	

	Real mBulletLifeTime;
	Real mBulletSpeedFactor;

	Real mAirJumpSpeed;
	int mAirJumpLeft;
	int mAirJumpMax;

	// internal offset
	Vector3 mLightOffset;
	Vector3 mCameraPositionOffset;
	Vector3 mCameraLookAtOffset;
	Vector3 mCameraInitLookAt;
	Vector3 mCameraInitPosition;

	// dotScene
	DotSceneLoader mDotScene;

public:
	BasicTutorial_00(void);
	~BasicTutorial_00(void);
	virtual void createScene(void);

	//[KEYBOARD]
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );

};
 
#endif // #ifndef __BasicTutorial_00_h_