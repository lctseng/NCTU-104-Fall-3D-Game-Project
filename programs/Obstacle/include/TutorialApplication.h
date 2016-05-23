//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_
 
#include "BaseApplication.h"
#include "BasicTools.h"

// OpenAL & alut
#include "NCTUAudio.h"
#include "NCTUGUIManager.h"
#include "NCTUCamera.h"


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

	virtual void updateBasic(const FrameEvent& evt);
	virtual void updatePlayingGame(const FrameEvent& evt);
	virtual void updatePausedGame(const FrameEvent& evt);
	virtual void processInputBasic(const FrameEvent& evt);
	virtual void processInputPlayingGame(const FrameEvent& evt);
	virtual void processInputPausedGame(const FrameEvent& evt);
	
	// [NEW]
	virtual Real speedAdjustment(const Vector3& old,const Vector3& go);
	// [NEW]
	virtual void checkCollision(const FrameEvent& evt);

	// [NEW]
	virtual void updateLightPosition(const FrameEvent& evt);

	// [NEW]
	virtual void equalizeSpeed(const FrameEvent& evt);
	virtual void fixOrientation(const FrameEvent& evt);

	virtual Vector3 getFrontDirection();

	void loadLevelFromScene(const String& sceneName);

	void onLoseGame();


	// [NEW]
	NCTU::ObstacleManager* mObstacleMgr;

	// [NEW]
	// Games
	Vector3 mInitVelocity;
	Vector3 mInitPosition;
	Quaternion mInitOrientation;
	NCTU::PlayerObstacle* mPlayerObstacle;
	NCTU::FloorObstacle* mFloor;
	Light *mLight;

	//[KEYBOARD]
	KeyBoardHandler *keyboardhandler;

	// settings
	bool mEnableCollision;
	bool mEnableFreeMode;
	bool mDisableLose;

	bool mGameStarted;
	bool mGamePaused;
	bool mGameOvered;

	Real mSpeedRate;
	

	Real mBulletLifeTime;
	Real mBulletSpeedFactor;

	Real mAirJumpSpeed;
	int mAirJumpLeft;
	int mAirJumpMax;
	int mScore;
	Real mTimeScoreTemp;
	double mTimeElapsed;

	Real mPauseTimeInterval;
	Real mPauseTimeIntervalMax;

	// internal offset
	Vector3 mLightOffset;

	int currentDirection;
	Vector3 mDirectionVectors[4];


	// dotScene
	DotSceneLoader mDotScene;
	// GUI
	NCTU::GUIManager* mGUI;

	NCTUCamera* mCameraCtrl;

	String mCurrentLevelName;
	String mCurrentBGM;


public:
	BasicTutorial_00(void);
	~BasicTutorial_00(void);
	virtual void createScene(void);
	//[State]
	virtual inline bool isStarted(){return mGameStarted;}
	virtual inline bool isPaused(){return mGamePaused;}
	virtual inline bool isOvered(){return mGameOvered;}
	//[Get component]
	virtual inline NCTU::PlayerObstacle* getPlayer(){return mPlayerObstacle;}
	//[KEYBOARD]
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	//[Mouse]
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	// [Menu Control]
	virtual void startGame();
	virtual void exitGame();
	virtual void pauseGame();
	virtual void resumeGame();
	virtual void backToMainMenu();
	virtual void resetGame();
	virtual void enterLevelMenu();
	virtual void exitLevelMenu();
	// GUI
	void refreshScore();
	int& score() {return mScore;};
	void changeScore(int val);
	virtual inline const String& getCurrentLevelName() const {return mCurrentLevelName;}
	virtual void setCurrentLevelName(const String&);

	void onPickupGet();
};
 
#endif // #ifndef __BasicTutorial_00_h_