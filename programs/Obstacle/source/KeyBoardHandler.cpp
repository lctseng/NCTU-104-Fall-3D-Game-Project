#include "KeyBoardHandler.h"
#include<iostream>

using namespace std;
KeyBoardHandler::KeyBoardHandler(void)
{
	for(int i = 0 ; i < ALL_KEY ; i++){
		key_data[i].pressed = false;
		key_data[i].triggered = false;
		key_data[i].time_pressed = 0;
	}
}


KeyBoardHandler::~KeyBoardHandler(void)
{
}


void KeyBoardHandler::keyPressed( const OIS::KeyEvent &arg ){

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

void KeyBoardHandler::keyReleased( const OIS::KeyEvent &arg ){

	key_data[arg.key].pressed = false;
	key_data[arg.key].triggered = false;
	
}

bool KeyBoardHandler::isKeyPressing(const unsigned char key){

	if(key < ALL_KEY)
		return key_data[key].pressed;
	else
		return false;
}

bool KeyBoardHandler::isKeyTriggered(const unsigned char key){
	
	if(key < ALL_KEY)
		if(key_data[key].triggered){
			key_data[key].triggered = false;
			return true;
		}
	return false;
}

bool KeyBoardHandler::isKeyPressedLong(const unsigned char key, float time /* = 1.0 */){

	if(key_data[key].pressed){

		if(((clock() - key_data[key].time_pressed)) > time * CLOCKS_PER_SEC)
			return true;

	}
	return false;
}

bool KeyBoardHandler::isKeyEntered(const unsigned char key){

	if(isKeyTriggered(key))
		return true;
	if(isKeyPressedLong(key, 0.7))
		return true;

	return false;

}

void KeyBoardHandler::updateData(){

	for(int i = 0 ; i < ALL_KEY ; i++){
		if(key_data[i].triggered){

			if((clock() - key_data[i].time_pressed) >TOL)
				key_data[i].triggered = false;
		}
	}

}