#include "NCTUCamera.h"
#include "TutorialApplication.h"
#include <iostream>
using namespace Ogre;
using namespace std;

NCTUCamera::NCTUCamera(){
	mSceneMgr = nullptr;
	mCamera = nullptr;
	mApp = nullptr;
	mNearClipMin = 5;
	mNearClipMax = 400;
	mCameraInitLookAt = Vector3(-1000,150,0);
	mCameraInitPosition = Vector3(-1600,350,0);
}

void NCTUCamera::setup(Camera *camera, SceneManager *SceneMgr, BasicTutorial_00 *app){
	mApp = app;
	mSceneMgr = SceneMgr;
	mCamera = camera;
	Parent = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Parent->attachObject(mCamera);
}

void NCTUCamera::TurnCamera(bool direction, Vector3 TargetPosition){

	//Parent->setPosition(TargetPosition);
	
	
	//cout <<"direction"<<  CameraDirection<<endl;

	if (direction == turnRight)//object turns right
	{	
		Parent->yaw(Degree(-90));
	}
	else if (direction == turnLeft){
		Parent->yaw(Degree(90));
	}
//	mCamera->lookAt(TargetPosition);
	//cout << "camera position = "<<CameraCurrentPosition<<endl;
}


void NCTUCamera::updateBasic(const FrameEvent& evt){
	
	//playerPos[1] = mInitPosition[1];

	Parent->setPosition(mApp->getPlayer()->getPosition());
	//cout << "camera position = "<<mCamera->getPosition()<<endl;
	//Parent->setOrientation(mApp->getPlayer()->getOrientation());
	
}
void NCTUCamera::updatePlayingGame(const FrameEvent& evt){
	// clip
	mCameraMotion.record(mApp->getPlayer()->getVelocity());
	if(!mApp->isStarted() || mCameraMotion.isDown()){
		mCamera->setNearClipDistance(mNearClipMin);	
	}
	else{
		mCamera->setNearClipDistance(mNearClipMax);
	}
}


void NCTUCamera::setupCamera(){
	//mCamera->setPosition(mCameraInitPosition);
	//mCamera->lookAt(mCameraInitLookAt);
	//Parent->setPosition(0,0,0);
	Parent->setPosition(mApp->getPlayer()->getPosition());
	Parent->setOrientation(1,0,0,0);
	mCamera->setNearClipDistance(mNearClipMax);
	mCamera->setPosition(mCameraPositionOffset);
	mCamera->lookAt(mCameraLookAtOffset);
	cout << Parent->getOrientation() << endl;
	cout << Parent->getPosition() << endl;
	//cout << CameraNode->getOrientation() << endl;
	//CameraNode->setOrientation(0,0,0,1);
}