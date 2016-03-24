//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_
 
#include "BaseApplication.h"
#include "MouseHandler.h"

using namespace Ogre;
class BasicTutorial_00 : public BaseApplication
{
private:
	Entity *mEntity;
	AnimationState *mAnimationState;
	bool frameStarted(const FrameEvent &evt);
	MouseHandler *mousetest;
public:
	BasicTutorial_00(void);
	virtual void createScene(void);

protected:
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
};
 
#endif // #ifndef __BasicTutorial_00_h_