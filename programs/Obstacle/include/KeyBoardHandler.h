
#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#define ALL_KEY  240
#define TOL 2

#include <time.h>
#include <OISEvents.h>
#include <OISKeyboard.h>

struct KeyData{
	bool pressed;
	bool triggered;
	clock_t time_pressed;
};

class KeyBoardHandler
{
private:
	KeyData key_data[ALL_KEY];

public:
	KeyBoardHandler(void);
	~KeyBoardHandler(void);
	
	//For key press
	bool isKeyPressing(const unsigned char key);
	bool isKeyTriggered(const unsigned char key);
	bool isKeyPressedLong(const unsigned char key, float time = 1.0); 
	bool isKeyEntered(const unsigned char key);
	void keyPressed( const OIS::KeyEvent &arg );
	void keyReleased( const OIS::KeyEvent &arg );
	void updateData();

};

#endif