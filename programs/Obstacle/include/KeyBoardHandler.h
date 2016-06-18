
#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#define ALL_KEY  240
#define TOL 2

#include <time.h>
#include <OISEvents.h>
#include <OISKeyboard.h>

/*! 
\brief store complete key-press data
*/
struct KeyData{
	bool pressed;
	bool triggered;
	clock_t time_pressed;
};
/*! 
\brief keyboard handler class
*/
class KeyBoardHandler
{
private:
	/*! 
	\brief store all key data
	*/
	KeyData key_data[ALL_KEY];
public:
	/*! 
	\brief constructor
	*/
	KeyBoardHandler(void);
	/*! 
	\brief destructor
	*/
	~KeyBoardHandler(void);
	
	//For key press
	/*! 
	\brief check if a key is pressed?
	*/
	bool isKeyPressing(const unsigned char key);
	/*! 
	\brief check if a key is triggered?
	*/
	bool isKeyTriggered(const unsigned char key);
	/*! 
	\brief check if a key is pressed for a long time?
	*/
	bool isKeyPressedLong(const unsigned char key, float time = 1.0); 
	/*! 
	\brief check if a key is entered?
	*/
	bool isKeyEntered(const unsigned char key);
	/*! 
	\brief handler for OIS keyPresssed
	*/
	void keyPressed( const OIS::KeyEvent &arg );
	/*! 
	\brief handler fir OIS keyReleased
	*/
	void keyReleased( const OIS::KeyEvent &arg );
	/*! 
	\brief update the handler
	*/
	void updateData();
};

#endif