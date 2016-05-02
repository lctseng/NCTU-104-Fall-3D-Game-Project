//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_
 
#include "BaseApplication.h"
#include "NCTUCamera.h"
using namespace Ogre;
class BasicTutorial_00 : public BaseApplication
{
private:
	Entity *mEntity;
	AnimationState *mAnimationState;
	bool frameStarted(const FrameEvent &evt);
	NCTUCamera *NCamera;

public:
	BasicTutorial_00(void);
	virtual void createScene(void);
	//bool keyReleased( const OIS::KeyEvent &arg );
};
 
#endif // #ifndef __BasicTutorial_00_h_