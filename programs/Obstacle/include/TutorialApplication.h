//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_
 
#include "BaseApplication.h"
#include "NCTUObstacleCommon.h"




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

	// [NEW]
	NCTU::ObstacleManager* mObstacleMgr;

	// [NEW]
	// Games
	Vector3 mInitVelocity;
	Vector3 mInitPosition;
	NCTU::PlayerObstacle* mPlayerObstacle;
	Light *mLight;

	// settings
	bool mEnableCollision;
	bool mEnableFreeMode;


	// internal offset
	Vector3 mLightOffset;
	Vector3 mCameraPositionOffset;
	Vector3 mCameraLookAtOffset;
	Vector3 mCameraInitLookAt;
	Vector3 mCameraInitPosition;

public:
	BasicTutorial_00(void);
	~BasicTutorial_00(void);
	virtual void createScene(void);



};
 
#endif // #ifndef __BasicTutorial_00_h_