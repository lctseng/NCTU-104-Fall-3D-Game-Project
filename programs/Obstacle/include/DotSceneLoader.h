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
 
	/*!
	\brief store properties for a node
	*/
	class nodeProperty
	{
	public:
		/*!
		\brief name of node
		*/
		String nodeName;
		/*!
		\brief property name
		*/
		String propertyNm;
		/*!
		\brief value name
		*/
		String valueName;
		/*!
		\brief value name
		*/
		String typeName;
 		/*!
		\brief constructor
		*/
		nodeProperty(const String &node, const String &propertyName, const String &value, const String &type)
			: nodeName(node), propertyNm(propertyName), valueName(value), typeName(type) {}
	};
 	/*!
	\brief value type indicator
	*/
	enum VarType{
		typeNONE, typeINT, typeSTR, typeFLOAT, typeBOOL
	};
 	/*!
	\brief general property for game
	*/
	class GeneralProperty{
	public:
	 	/*!
		\brief string value
		*/
		String valStr;
	 	/*!
		\brief integer value
		*/
		int valInt;
		/*!
		\brief floating point number value
		*/
		Real valFloat;
		/*!
		\brief boolean value
		*/
		bool valBool;
		/*!
		\brief value type
		*/
		VarType valType;
		/*!
		\brief constructor
		*/
		GeneralProperty():valType(typeNONE){}
	};

	/*!
	\brief store properties for a obstacle
	*/
	class ObstacleProperty{
	public:
		/*!
		\brief type of obstacle
		*/
		String obstacle_type;
		/*!
		\brief mass for physics
		*/
		Real mass;
		/*!
		\brief friction for physics
		*/
		Real friction;
		/*!
		\brief restitution for physics
		*/
		Real restitution;
		/*!
		\brief hit point of this obstacle
		*/
		int hitPoint;
		/*!
		\brief type of hit point(HP)
		*/
		NCTU::HpType hpType;
		/*!
		\brief speed for bumping bed
		*/
		Real bumpSpeed;
		/*!
		\brief turn type (left or right) for turing plane
		*/
		String turnType;
		/*!
		\brief lots of condition vectors
		*/
		std::deque<std::pair<Ogre::Vector3,Ogre::Real> > conditionVectors;
		/*!
		\brief material names for different hp point
		*/
		propMap<int,String> hpChangeMaterials;
		/*!
		\brief constructor
		*/
		ObstacleProperty():obstacle_type("None"),mass(1.0f),friction(1.0f),restitution(1.0f),hitPoint(-1),hpType(NCTU::typeBoth),bumpSpeed(0.0f){}
	};
	/*!
	\brief main class for DotScene reading
	*/
	class DotSceneLoader
	{
	public:
		/*!
		\brief contructor
		*/
		DotSceneLoader() : mSceneMgr(0) {}
		/*!
		\brief destructor
		*/
		virtual ~DotSceneLoader() {}
		/*!
		\brief parse the given DotScene file
		*/
		void parseDotScene(const String &SceneName, const String &groupName, SceneManager *yourSceneMgr, NCTU::ObstacleManager* obstacleMgr, SceneNode *pAttachNode = NULL, const String &sPrependNode = "");
		/*!
		\brief get property of a node
		*/
		String getProperty(const String &ndNm, const String &prop);
		/*!
		\brief destory the scene nodes without physics objects
		*/
		void destroyDedicatedSceneNodes();
		/*!
		\brief load a dummy scene with player only
		*/
		void loadDummyScene();
		/*!
		\brief array of node properties
		*/
		std::vector<nodeProperty> nodeProperties;
		/*!
		\brief array of static objects
		*/
		std::vector<String> staticObjects;
		/*!
		\brief array of dynamic objects
		*/
		std::vector<String> dynamicObjects;
		/*!
		\brief general properties
		*/
		propMap<String,GeneralProperty> mGeneralProps;
	protected:
		/*!
		\brief process a scene section
		*/
		void processScene(TiXmlElement *XMLRoot);
		/*!
		\brief process a nodes section
		*/
		void processNodes(TiXmlElement *XMLNode);
		/*!
		\brief process a externals section
		*/
		void processExternals(TiXmlElement *XMLNode);
		/*!
		\brief process a environment section
		*/
		void processEnvironment(TiXmlElement *XMLNode);
		/*!
		\brief process a terrian section
		*/
		void processTerrain(TiXmlElement *XMLNode);
		/*!
		\brief process user data reference
		*/
		void processUserDataReference(TiXmlElement *XMLNode, SceneNode *pParent = 0);
		/*!
		\brief process user data reference
		*/
		void processUserDataReference(TiXmlElement *XMLNode, Entity *pEntity);
		/*!
		\brief process octree
		*/
		void processOctree(TiXmlElement *XMLNode);
		/*!
		\brief process a light section
		*/
		void processLight(TiXmlElement *XMLNode, SceneNode *pParent = 0);
		/*!
		\brief process a camera section
		*/
		void processCamera(TiXmlElement *XMLNode, SceneNode *pParent = 0);
		/*!
		\brief process a node section
		*/
		void processNode(TiXmlElement *XMLNode, SceneNode *pParent = 0);
		/*!
		\brief process look target
		*/
		void processLookTarget(TiXmlElement *XMLNode, SceneNode *pParent);
		/*!
		\brief process track target
		*/
		void processTrackTarget(TiXmlElement *XMLNode, SceneNode *pParent);
		/*!
		\brief process entity
		*/
		Entity * processEntity(TiXmlElement *XMLNode, SceneNode *pParent, const String& namePrefix = "");
		/*!
		\brief process particle system
		*/
		void processParticleSystem(TiXmlElement *XMLNode, SceneNode *pParent);
		/*!
		\brief process billboard set
		*/
		void processBillboardSet(TiXmlElement *XMLNode, SceneNode *pParent);
		/*!
		\brief process plane
		*/
		void processPlane(TiXmlElement *XMLNode, SceneNode *pParent);
 		/*!
		\brief process fog
		*/
		void processFog(TiXmlElement *XMLNode);
		/*!
		\brief process skybox
		*/
		void processSkyBox(TiXmlElement *XMLNode);
		/*!
		\brief process sky dome
		*/
		void processSkyDome(TiXmlElement *XMLNode);
		/*!
		\brief process sky plane
		*/
		void processSkyPlane(TiXmlElement *XMLNode);
		/*!
		\brief process clipping
		*/
		void processClipping(TiXmlElement *XMLNode);
		/*!
		\brief process light range
		*/
		void processLightRange(TiXmlElement *XMLNode, Light *pLight);
		/*!
		\brief process light attenuation
		*/
		void processLightAttenuation(TiXmlElement *XMLNode, Light *pLight);
		/*!
		\brief process obstacle property
		*/
		bool processObstacleProperty(TiXmlElement *XMLNode, const String& name, SceneNode* node, Entity* ent);
		/*!
		\brief process process extra field for obstacle
		*/
		void processObstacleExtraField(TiXmlElement *XMLNode, ObstacleProperty& prop, bool saveAsGeneral = false);
		/*! 
		\brief get string attribute
		*/
		String getAttrib(TiXmlElement *XMLNode, const String &parameter, const String &defaultValue = "");
		/*! 
		\brief get floating point number attribute
		*/
		Real getAttribReal(TiXmlElement *XMLNode, const String &parameter, Real defaultValue = 0);
		/*! 
		\brief get boolean attribute
		*/
		bool getAttribBool(TiXmlElement *XMLNode, const String &parameter, bool defaultValue = false);
 
		/*! 
		\brief parse vector3
		*/
		Vector3 parseVector3(TiXmlElement *XMLNode);
		/*! 
		\brief parse quaternion
		*/
		Quaternion parseQuaternion(TiXmlElement *XMLNode);
		/*! 
		\brief parse color
		*/
		ColourValue parseColour(TiXmlElement *XMLNode);
		/*! 
		\brief store list of dedicated scene nodes
		*/
		std::deque<SceneNode*> mDedicatedSceneNodes;
 
		/*! 
		\brief pointer of scene manager
		*/
		SceneManager *mSceneMgr;
		/*! 
		\brief pointer of attach node
		*/
		SceneNode *mAttachNode;
		/*! 
		\brief group name
		*/
		String m_sGroupName;
		/*! 
		\brief prepend node 
		*/
		String m_sPrependNode;
		/*! 
		\brief pointer of our obstacle manager
		*/
		NCTU::ObstacleManager* mObstacleMgr;
	};
}
 
#endif // DOT_SCENELOADER_H