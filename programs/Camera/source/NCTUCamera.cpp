#include "NCTUCamera.h"
#include <iostream>
using namespace Ogre;
using namespace std;

 NCTUCamera::NCTUCamera(Camera *camera, SceneManager *SceneMgr){
	mSceneMgr = SceneMgr;
	mCamera = camera;
	Parent = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Parent->createChildSceneNode()->attachObject(mCamera);
}

void NCTUCamera::TurnCamera(bool direction, Vector3 TargetPosition){

	Parent->setPosition(TargetPosition);
	
	//cout << "camera position = "<<CameraCurrentPosition<<endl;
	//cout <<"direction"<<  CameraDirection<<endl;

	if (direction == turnRight)//object turns right
	{	
		Parent->yaw(Degree(90));
	}
	else if (direction == turnLeft){
		Parent->yaw(Degree(-90));
	}
//	mCamera->lookAt(TargetPosition);
	//cout << "camera position = "<<CameraCurrentPosition<<endl;
}
