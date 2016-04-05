#include "NCTUObstacle.h"

using namespace NCTU;
using namespace Ogre;
using namespace OgreBulletCollisions;


Obstacle::Obstacle(ObstacleManager* mgmt,Real restitution,Real friction,Real mass)
	:mManager(mgmt),
	mFriction(friction),
	mRestitution(restitution),
	mMass(mass),
	mIsBumpObstacle(false),
	mScaleDifference(1.0f)
{

}
Obstacle::~Obstacle(){
	// delete shape and body
	delete mBody;
	delete mShape;
}

void Obstacle::setScale(const Ogre::Vector3& v){
	mNode->setScale(v * mScaleDifference);
	mShape->getBulletShape()->setLocalScaling(OgreBtConverter::to(v));
}

OgreBulletCollisions::CollisionShape* Obstacle::generateFittingShape(SceneNode* node, Entity* ent){
	/*
	�ϥ�OgreBullet��AnimatedMeshToShapeConverter
	�o�Ӫ��󪺧@�άO��JEntity���oMesh���ԲӸ�ơA
	�K���XConvexHull�Χ������GImpactCollision
	���Υt�@��StaticMeshToShapeConverter�]��A�ä��v�T���G
	*/
	OgreBulletCollisions::StaticMeshToShapeConverter *converter = 
		new OgreBulletCollisions::StaticMeshToShapeConverter(
		ent, //�ܳ�´N���JEntity�A�̭��|�h���o�һݭn��Mesh��T
		node->_getFullTransform()); /*���J��Entity��Matrix4�A
									�]�N�O���o�j�p�P��m�A
									�o�䪽����_getFullTransform()�qnode���o�̤�K*/

	//�ϥ�createConcave���ͧڭ̩ҭn��GImpactConcaveShape
	OgreBulletCollisions::GImpactConcaveShape *concaveMeshShape = converter->createConcave();
	return concaveMeshShape;
}