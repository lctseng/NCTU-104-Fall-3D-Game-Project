//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"


using namespace Ogre;
BasicTutorial_00::BasicTutorial_00(void) {
	mBulletBox = AxisAlignedBox ( //aligned box for Bullet
				Ogre::Vector3 (-10000, -10000, -10000), 
                Ogre::Vector3 (10000,  10000,  10000));
	mGravityVector = Vector3(0,-9.81,0);
	mNumEntitiesInstanced = 0;
	mWorld = nullptr;
	mDebugDrawer = nullptr;

}

BasicTutorial_00::~BasicTutorial_00(void) {
	// OgreBullet physic delete - RigidBodies
	std::deque<OgreBulletDynamics::RigidBody *>::iterator itBody = mBodies.begin();
	while (mBodies.end() != itBody)
	{   
		delete *itBody;
		++itBody;
	}   
	// OgreBullet physic delete - Shapes
	std::deque<OgreBulletCollisions::CollisionShape *>::iterator itShape = mShapes.begin();
	while (mShapes.end() != itShape)
	{   
		delete *itShape;
		++itShape;
	}
	mBodies.clear();
	mShapes.clear();
	delete mWorld->getDebugDrawer();
	mWorld->setDebugDrawer(0);
	delete mWorld;
}


void BasicTutorial_00::createScene(void) 
{
	setupOgreBullet();
	mSceneMgr->setAmbientLight( ColourValue( 0.5, 0.5, 0.5 ) ); //bright
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE); 
	//mSceneMgr->setAmbientLight( ColourValue( 0, 0, 0 ) );  //dark
	// create a plane
	// plane
	
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		15000,15000, // width, height
		20,20, // x- and y-segments
		true, // normal
		1, // num texture sets
		100,100, // x- and y-tiles
		Vector3::UNIT_Z // upward vector
		); 
	// plane entity
	Entity* ground_ent = mSceneMgr->createEntity(
				"GroundEntity", "ground"); 
	ground_ent->setMaterialName("Examples/BumpyMetal");
	mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode()
		->attachObject(ground_ent); 
	
	// plane collision
	OgreBulletCollisions::CollisionShape *shape;
	shape = new OgreBulletCollisions::StaticPlaneCollisionShape(Ogre::Vector3(0,1,0), 0); // (normal vector, distance)
	OgreBulletDynamics::RigidBody *defaultPlaneBody = new OgreBulletDynamics::RigidBody(
			"ground",
			mWorld);
	defaultPlaneBody->setStaticShape(shape, 0.1, 0.8); // (shape, restitution, friction)
	// push the created objects to the deques
	
	mShapes.push_back(shape);
	mBodies.push_back(defaultPlaneBody);
	
	// Ball
	// obj 
	Entity* ball_ent
		= mSceneMgr
		->createEntity( "sphere", "sphere.mesh" ); 
	ball_ent->setCastShadows(true);

	SceneNode *ball_node
		= mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		"BallNode", Vector3( 50, 40, 30 ) ); 
	ball_node->scale(0.3,0.3,0.3);
	ball_node->attachObject( ball_ent );
	ball_ent->setMaterialName("Examples/SphereMappedRustySteel");
	
	/*
	//
	mEntity 
		= mSceneMgr
		->createEntity( "Robot", "robot.mesh" ); 

	SceneNode *sNode 
		= mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		"RobotNode", Vector3( 50, 0, 0 ) ); 

	sNode->attachObject( mEntity ); 


	mAnimationState = mEntity->getAnimationState( "Idle" );
	mAnimationState->setLoop( true );
	mAnimationState->setEnabled( true );
	*/

	Light *light = mSceneMgr->createLight("Light1"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(100, 200, 250)); 
	light->setDiffuseColour(0.3, 0.3, 1.3);		
	light->setSpecularColour(1.0, 1.0, 1.0);	
}
bool BasicTutorial_00::frameStarted(const FrameEvent &evt)
{
	/*
	mAnimationState->addTime(evt.timeSinceLastFrame);
	if ( mKeyboard->isKeyDown(OIS::KC_S) ) {
		mAnimationState = mEntity->getAnimationState( "Walk" );
		mAnimationState->setLoop( true );
		mAnimationState->setEnabled( true );
	}
	*/
	processUnbufferedKeyInput(evt);


	bool ret = BaseApplication::frameStarted(evt);
    mWorld->stepSimulation(evt.timeSinceLastFrame);   // update Bullet Physics animation
    return ret;
}

bool BasicTutorial_00::frameEnded(const FrameEvent& evt)
{
    bool ret = BaseApplication::frameEnded(evt);
    mWorld->stepSimulation(evt.timeSinceLastFrame);   // update Bullet Physics animation
    return ret;
}

bool BasicTutorial_00::processUnbufferedKeyInput(const FrameEvent& evt)
{
	static Real timeUntilNextToggle = 0.0f;
	timeUntilNextToggle += evt.timeSinceLastFrame;

	if(mKeyboard->isKeyDown(OIS::KC_B) && timeUntilNextToggle > 1.0f)
	{
		timeUntilNextToggle = 0.0f;
		Vector3 size = Vector3::ZERO;   // size of the box
		// starting position of the box
		Vector3 position = (mCamera->getDerivedPosition() + mCamera->getDerivedDirection().normalisedCopy() * 10);
		// create an ordinary, Ogre mesh with texture
		Entity *entity = mSceneMgr->createEntity(
			"Box" + StringConverter::toString(mNumEntitiesInstanced),
			"cube.mesh");            
		entity->setCastShadows(true);
		// we need the bounding box of the box to be able to set the size of the Bullet-box
		AxisAlignedBox boundingB = entity->getBoundingBox();
		size = boundingB.getSize(); size /= 2.0f; // only the half needed
		size *= 0.96f;   // Bullet margin is a bit bigger so we need a smaller size
						// (Bullet 2.76 Physics SDK Manual page 18)
		entity->setMaterialName("Examples/BumpyMetal");
		SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		node->attachObject(entity);
		node->scale(0.05f, 0.05f, 0.05f);   // the cube is too big for us
		size *= 0.05f;                  // don't forget to scale down the Bullet-box too
		// after that create the Bullet shape with the calculated size
		OgreBulletCollisions::BoxCollisionShape *sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape(size);
		// and the Bullet rigid body
		OgreBulletDynamics::RigidBody *defaultBody = new OgreBulletDynamics::RigidBody(
			"defaultBoxRigid" + StringConverter::toString(mNumEntitiesInstanced),
			mWorld);
		defaultBody->setShape(   node,
						sceneBoxShape,
						0.6f,         // dynamic body restitution
						0.6f,         // dynamic body friction
						1.0f,          // dynamic bodymass
						position,      // starting position of the box
						Quaternion(0,0,0,1));// orientation of the box
		mNumEntitiesInstanced++;            
		defaultBody->setLinearVelocity(
				mCamera->getDerivedDirection().normalisedCopy() * 7.0f ); // shooting speed
			// push the created objects to the deques
		mShapes.push_back(sceneBoxShape);
		mBodies.push_back(defaultBody);            
	}
	return true;
}
void BasicTutorial_00::setupOgreBullet()
{	
	mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, mBulletBox, mGravityVector);
	mDebugDrawer = new OgreBulletCollisions::DebugDrawer();
	mDebugDrawer->setDrawWireframe(true);   // we want to see the Bullet containers
	mWorld->setDebugDrawer(mDebugDrawer);
	mWorld->setShowDebugShapes(true);      // enable it if you want to see the Bullet containers
	SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
	node->attachObject(static_cast <SimpleRenderable *> (mDebugDrawer));

}