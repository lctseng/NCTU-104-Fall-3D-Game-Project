#include "MouseHandler.h"
#include<iostream>

using namespace std;
MouseHandler::MouseHandler(void)
{
	for(int i = 0 ; i < ALL_KEY ; i++){
		key_data[i].pressed = false;
		key_data[i].triggered = false;
		key_data[i].time_pressed = 0;
	}
}


MouseHandler::~MouseHandler(void)
{
}


void MouseHandler::keyPressed( const OIS::KeyEvent &arg ){

	if(!key_data[arg.key].pressed){
		key_data[arg.key].pressed = true;
		key_data[arg.key].triggered = true;
		key_data[arg.key].time_pressed = clock();
	}
	else{
		cout << "else" << arg.key << " " << endl;
		key_data[arg.key].triggered = false;
	}

}

void MouseHandler::keyReleased( const OIS::KeyEvent &arg ){

	key_data[arg.key].pressed = false;
	key_data[arg.key].triggered = false;
	
}

bool MouseHandler::isKeyPressing(const unsigned char key){

	if(key < ALL_KEY)
		return key_data[key].pressed;
	else
		return false;
}

bool MouseHandler::isKeyTriggered(const unsigned char key){
	
	if(key < ALL_KEY)
		if(key_data[key].triggered){
			key_data[key].triggered = false;
			return true;
		}
	return false;
}

bool MouseHandler::isKeyPressedLong(const unsigned char key, float time /* = 1.5 */){

	if(key_data[key].pressed){

		if(((clock() - key_data[key].time_pressed)) > time * CLOCKS_PER_SEC)
			return true;

	}
	return false;
}

void MouseHandler::updateData(){

	for(int i = 0 ; i < ALL_KEY ; i++){
		if(key_data[i].triggered){

			if((clock() - key_data[i].time_pressed) >TOL)
				key_data[i].triggered = false;
		}
	}

}