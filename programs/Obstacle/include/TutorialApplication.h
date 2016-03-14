//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_
 
#include "BaseApplication.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h" // for static planes
#include "Shapes/OgreBulletCollisionsBoxShape.h"       // for Boxes


using namespace Ogre;
class BasicTutorial_00 : public BaseApplication
{
private:
	Entity *mEntity;
	AnimationState *mAnimationState;
protected:
	virtual bool frameStarted(const FrameEvent& evt);
	virtual bool frameEnded(const FrameEvent& evt);
	virtual bool processUnbufferedKeyInput(const FrameEvent& evt);
	virtual void setupOgreBullet();

	// For Bullet
	AxisAlignedBox  mBulletBox;
	Vector3 mGravityVector;
	OgreBulletDynamics::DynamicsWorld *mWorld;   // OgreBullet World
	OgreBulletCollisions::DebugDrawer *mDebugDrawer;
	int mNumEntitiesInstanced;
	std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
	std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;


public:
	BasicTutorial_00(void);
	~BasicTutorial_00(void);
	virtual void createScene(void);



};
 
#endif // #ifndef __BasicTutorial_00_h_