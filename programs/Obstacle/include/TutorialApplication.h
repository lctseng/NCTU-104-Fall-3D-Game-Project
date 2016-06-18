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

/*! 
\brief main class for the application
*/
class BasicTutorial_00 : public BaseApplication
{
private:
protected:
	/*! 
	\brief create camera
	*/
	virtual void createCamera(void);
	/*! 
	\brief process for frameStarted
	*/
	virtual bool frameStarted(const FrameEvent& evt);
	/*! 
	\brief update basic game functionallity
	*/
	virtual void updateBasic(const FrameEvent& evt);
	/*! 
	\brief update routine for playing game
	*/
	virtual void updatePlayingGame(const FrameEvent& evt);
	/*! 
	\brief update routine for paused game
	*/
	virtual void updatePausedGame(const FrameEvent& evt);
	/*! 
	\brief process input event for all cases
	*/
	virtual void processInputBasic(const FrameEvent& evt);
	/*! 
	\brief process extra input event for playing game
	*/
	virtual void processInputPlayingGame(const FrameEvent& evt);
	/*! 
	\brief process extra input evnet for paused game
	*/
	virtual void processInputPausedGame(const FrameEvent& evt);
	
	/*! 
	\brief adjust the moving speed (manual control only)
	*/
	virtual Real speedAdjustment(const Vector3& old,const Vector3& go);
	/*! 
	\brief check collision
	*/
	virtual void checkCollision(const FrameEvent& evt);
	/*! 
	\brief update the light position
	*/
	virtual void updateLightPosition(const FrameEvent& evt);
	/*! 
	\brief equalize the moving speed of player
	*/
	virtual void equalizeSpeed(const FrameEvent& evt);
	/*! 
	\brief fix the orientation of player
	*/
	virtual void fixOrientation(const FrameEvent& evt);
	/*! 
	\brief get the front direction
	*/
	virtual Vector3 getFrontDirection();
	/*! 
	\brief load scene from scene name
	*/
	void loadLevelFromScene(const String& sceneName);
	/*! 
	\brief process when player lose
	*/
	void onLoseGame();


	/*! 
	\brief pointer to the obstacle manager
	*/
	NCTU::ObstacleManager* mObstacleMgr;

	/*! 
	\brief initial velocity for player
	*/
	Vector3 mInitVelocity;
	/*! 
	\brief initial position for player
	*/
	Vector3 mInitPosition;
	/*! 
	\brief inital orientation for player
	*/
	Quaternion mInitOrientation;
	/*! 
	\brief pointer to the player obstacle
	*/
	NCTU::PlayerObstacle* mPlayerObstacle;
	/*! 
	\brief pointer to the floor obstacle
	*/
	NCTU::FloorObstacle* mFloor;
	/*! 
	\brief pointer to the light
	*/
	Light *mLight;

	/*! 
	\brief pointer to the keyboard handler
	*/
	KeyBoardHandler *keyboardhandler;

	/*! 
	\brief is the collision enabled?
	*/
	bool mEnableCollision;
	/*! 
	\brief is the free view mode enabled?
	*/
	bool mEnableFreeMode;
	/*! 
	\brief is the lose disabled?
	*/
	bool mDisableLose;
	/*! 
	\brief is game started?
	*/
	bool mGameStarted;
	/*! 
	\brief is game paused?
	*/
	bool mGamePaused;
	/*! 
	\brief is game overed?
	*/
	bool mGameOvered;
	/*! 
	\brief the speed rate for player
	*/
	Real mSpeedRate;
	

	/*! 
	\brief bullet lift time
	*/
	Real mBulletLifeTime;
	/*! 
	\brief bullet speed factor
	*/
	Real mBulletSpeedFactor;
	/*! 
	\brief player air jump speed (currently not used)
	*/
	Real mAirJumpSpeed;
	/*! 
	\brief air jump time left
	*/
	int mAirJumpLeft;
	/*! 
	\brief max air jmup time
	*/
	int mAirJumpMax;
	/*! 
	\brief score
	*/
	int mScore;
	/*! 
	\brief score temp variable 
	*/
	Real mTimeScoreTemp;
	/*! 
	\brief time elapsed
	*/
	double mTimeElapsed;
	/*! 
	\brief pause time interval
	*/
	Real mPauseTimeInterval;
	/*! 
	\brief max pause time interval
	*/
	Real mPauseTimeIntervalMax;

	// internal offset
	/*! 
	\brief light offset
	*/
	Vector3 mLightOffset;
	/*! 
	\brief current direction
	*/
	int currentDirection;
	/*! 
	\brief direction vectors
	*/
	Vector3 mDirectionVectors[4];


	/*! 
	\brief pointer to dotScene loader
	*/
	DotSceneLoader mDotScene;
	/*! 
	\brief pointer to GUI manager
	*/
	NCTU::GUIManager* mGUI;
	/*! 
	\brief pointer to camera controller
	*/
	NCTUCamera* mCameraCtrl;
	/*! 
	\brief current level name
	*/
	String mCurrentLevelName;
	/*! 
	\brief current bgm
	*/
	String mCurrentBGM;
public:
	/*! 
	\brief constructor
	*/
	BasicTutorial_00(void);
	/*! 
	\brief destructor
	*/
	~BasicTutorial_00(void);
	/*! 
	\brief create the scene
	*/
	virtual void createScene(void);
	/*! 
	\brief is game started?
	*/
	virtual inline bool isStarted(){return mGameStarted;}
	/*! 
	\brief is game paused?
	*/
	virtual inline bool isPaused(){return mGamePaused;}
	/*! 
	\brief is game overed?
	*/
	virtual inline bool isOvered(){return mGameOvered;}
	/*! 
	\brief get the player obstacle
	*/
	virtual inline NCTU::PlayerObstacle* getPlayer(){return mPlayerObstacle;}
	/*! 
	\brief OIS - keyPressed
	*/
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	/*! 
	\brief OIS - keyReleased
	*/
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	/*! 
	\brief OIS - mouseMoved
	*/
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
	/*! 
	\brief OIS - mousePressed
	*/
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	/*! 
	\brief OIS - mouseReleased
	*/
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	// [Menu Control]
	/*! 
	\brief start the game
	*/
	virtual void startGame();
	/*! 
	\brief exit game
	*/
	virtual void exitGame();
	/*! 
	\brief pause game
	*/
	virtual void pauseGame();
	/*! 
	\brief resume game
	*/
	virtual void resumeGame();
	/*! 
	\brief back to main menu
	*/
	virtual void backToMainMenu();
	/*! 
	\brief reset game to starting state
	*/
	virtual void resetGame();
	/*! 
	\brief go to level selection menu
	*/
	virtual void enterLevelMenu();
	/*! 
	\brief exit level selection menu
	*/
	virtual void exitLevelMenu();
	// GUI
	/*! 
	\brief refresh the score
	*/
	void refreshScore();
	/*! 
	\brief get current score
	*/
	int& score() {return mScore;};
	/*! 
	\brief change score
	*/
	void changeScore(int val);
	/*! 
	\brief get current level name
	*/
	virtual inline const String& getCurrentLevelName() const {return mCurrentLevelName;}
	/*! 
	\brief set current level name
	*/
	virtual void setCurrentLevelName(const String&);
	/*! 
	\brief process when get a pickup object
	*/
	void onPickupGet();
};
 
#endif // #ifndef __BasicTutorial_00_h_