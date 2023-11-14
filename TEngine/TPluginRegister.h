#ifndef __TPLUGINREGISTER_H__
#define __TPLUGINREGISTER_H__

#ifndef __TPLUGINREGISTERENTRY_H__
#include "TPluginRegisterEntry.h"
#endif

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TPluginRegister : public TSingleton<TPluginRegister>
{
public:
	TPluginRegister();

	~TPluginRegister();

	void Register(const char* typeName, CreatePluginDefinitionFunction definitionCallback, CreatePluginFunction instanceCallback);

	TPluginDefinition* CreateDefinition(const char* typeName);

	TPlugin* CreatePlugin(const char* typeName, TEntity* entity, TPluginDefinition* definition);

private:
	TDynamicSet<TPluginRegisterEntry*> m_registerEntries;
};

//-------------------------------------------------------------------------------
#define RegisterPluginType(type, PluginDefinitionType, PluginType) \
	\
	TPlugin* Create##PluginType(TEntity* entity, TPluginDefinition* definition) \
	{ \
		PluginType* instance = TNew PluginType(entity, definition); \
		return instance; \
	} \
	\
	\
	TPluginDefinition* CreateDefinition##PluginType() \
	\
	{ \
		PluginDefinitionType* instance = TNew PluginDefinitionType(); \
		return instance; \
	} \
	\
	\
	void PluginType::Register() \
	{ \
		TPluginRegister::Get()->Register(type, CreateDefinition##PluginType, Create##PluginType); \
	}

#endif
