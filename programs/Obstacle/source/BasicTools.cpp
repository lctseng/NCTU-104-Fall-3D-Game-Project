#include "BasicTools.h"

void genNameUsingIndex(const Ogre::String & prefix, int index, Ogre::String &out_name)
{
	out_name= prefix + Ogre::StringConverter::toString(static_cast<int>(index));
}
void logMessage(const  Ogre::String &msg)
{
	Ogre::LogManager::getSingletonPtr()->logMessage(msg);
}

void logMessage(const Ogre::Vector3 &v)
{
	Ogre::String msg;
	std::stringstream out0;
	std::stringstream out1;
	std::stringstream out2;
	out0 << v.x;
	out1 << v.y;
	out2 << v.z;

	msg = out0.str() + "\t\t" + out1.str() + "\t\t" + out2.str();

	Ogre::LogManager::getSingletonPtr()->logMessage(msg);
}

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