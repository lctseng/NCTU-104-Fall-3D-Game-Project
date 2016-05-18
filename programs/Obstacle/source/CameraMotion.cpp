#include "CameraMotion.h"
#include <iostream>
using namespace std;

void CameraMotion::record(const Ogre::Vector3& v){
	if(motionData.size()>=MAX_RECORD){
		motionData.pop_front();
	}
	motionData.push_back(v.y < 0.0f);
	int count = 0; // count for negative
	for(int i=0;i<motionData.size();i++){
		if(motionData[i]){
			++count;
		}
	}
	result = count >= REQ_COUNT;	
}

bool CameraMotion::isDown() const{
	return result;
}