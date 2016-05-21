#ifndef DOT_SCENELOADER_H
#define DOT_SCENELOADER_H
 
// Includes
#include <OgreString.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <vector>
#include <map>
#include <deque>

#include "NCTUObstacleManager.h"
#include "NCTUPlayerObstacle.h"
#include "NCTUCubeObstacle.h"
#include "NCTUSphereObstacle.h"
#include "NCTUFloorObstacle.h"
 
//#define VERBOSE_LOAD
#define SCENE_RESERVED_NAME "DataField"

// Forward declarations
class TiXmlElement;
 
namespace Ogre
{
	// Forward declarations
	class SceneManager;
	class SceneNode;
 
	class nodeProperty
	{
	public:
		String nodeName;
		String propertyNm;
		String valueName;
		String typeName;
 
		nodeProperty(const String &node, const String &propertyName, const String &value, const String &type)
			: nodeName(node), propertyNm(propertyName), valueName(value), typeName(type) {}
	};
 
	enum VarType{
		typeNONE, typeINT, typeSTR, typeFLOAT, typeBOOL
	};

	class GeneralProperty{
	public:
		String valStr;
		int valInt;
		Real valFloat;
		bool valBool;
		VarType valType;
		GeneralProperty():valType(typeNONE){}
	};


	class ObstacleProperty{
	public:
		String obstacle_type;
		Real mass;
		Real friction;
		Real restitution;
		int hitPoint;
		NCTU::HpType hpType;
		Real bumpSpeed;
		String turnType;
		std::deque<std::pair<Ogre::Vector3,Ogre::Real> > conditionVectors;
		propMap<int,String> hpChangeMaterials;
		ObstacleProperty():obstacle_type("None"),mass(1.0f),friction(1.0f),restitution(1.0f),hitPoint(-1),hpType(NCTU::typeBoth),bumpSpeed(0.0f){}
	};

	class DotSceneLoader
	{
	public:
		DotSceneLoader() : mSceneMgr(0) {}
		virtual ~DotSceneLoader() {}
 
		void parseDotScene(const String &SceneName, const String &groupName, SceneManager *yourSceneMgr, NCTU::ObstacleManager* obstacleMgr, SceneNode *pAttachNode = NULL, const String &sPrependNode = "");
		String getProperty(const String &ndNm, const String &prop);
		void destroyDedicatedSceneNodes();
		void loadDummyScene();

		std::vector<nodeProperty> nodeProperties;
		std::vector<String> staticObjects;
		std::vector<String> dynamicObjects;

		propMap<String,GeneralProperty> mGeneralProps;
 


	protected:
		void processScene(TiXmlElement *XMLRoot);
 
		void processNodes(TiXmlElement *XMLNode);
		void processExternals(TiXmlElement *XMLNode);
		void processEnvironment(TiXmlElement *XMLNode);
		void processTerrain(TiXmlElement *XMLNode);
		void processUserDataReference(TiXmlElement *XMLNode, SceneNode *pParent = 0);
		void processUserDataReference(TiXmlElement *XMLNode, Entity *pEntity);
		void processOctree(TiXmlElement *XMLNode);
		void processLight(TiXmlElement *XMLNode, SceneNode *pParent = 0);
		void processCamera(TiXmlElement *XMLNode, SceneNode *pParent = 0);
 
		void processNode(TiXmlElement *XMLNode, SceneNode *pParent = 0);
		void processLookTarget(TiXmlElement *XMLNode, SceneNode *pParent);
		void processTrackTarget(TiXmlElement *XMLNode, SceneNode *pParent);
		Entity * processEntity(TiXmlElement *XMLNode, SceneNode *pParent, const String& namePrefix = "");
		void processParticleSystem(TiXmlElement *XMLNode, SceneNode *pParent);
		void processBillboardSet(TiXmlElement *XMLNode, SceneNode *pParent);
		void processPlane(TiXmlElement *XMLNode, SceneNode *pParent);
 
		void processFog(TiXmlElement *XMLNode);
		void processSkyBox(TiXmlElement *XMLNode);
		void processSkyDome(TiXmlElement *XMLNode);
		void processSkyPlane(TiXmlElement *XMLNode);
		void processClipping(TiXmlElement *XMLNode);
 
		void processLightRange(TiXmlElement *XMLNode, Light *pLight);
		void processLightAttenuation(TiXmlElement *XMLNode, Light *pLight);


		bool processObstacleProperty(TiXmlElement *XMLNode, const String& name, SceneNode* node, Entity* ent);
		void processObstacleExtraField(TiXmlElement *XMLNode, ObstacleProperty& prop, bool saveAsGeneral = false);


		String getAttrib(TiXmlElement *XMLNode, const String &parameter, const String &defaultValue = "");
		Real getAttribReal(TiXmlElement *XMLNode, const String &parameter, Real defaultValue = 0);
		bool getAttribBool(TiXmlElement *XMLNode, const String &parameter, bool defaultValue = false);
 

		Vector3 parseVector3(TiXmlElement *XMLNode);
		Quaternion parseQuaternion(TiXmlElement *XMLNode);
		ColourValue parseColour(TiXmlElement *XMLNode);
			
		std::deque<SceneNode*> mDedicatedSceneNodes;
 

		SceneManager *mSceneMgr;
		SceneNode *mAttachNode;
		String m_sGroupName;
		String m_sPrependNode;
		NCTU::ObstacleManager* mObstacleMgr;
		

	};
}
 
#endif // DOT_SCENELOADER_H