#ifndef __TPLUGINREGISTERENTRY_H__
#define __TPLUGINREGISTERENTRY_H__

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TEntity;
class TPluginDefinition;
class TPlugin;

typedef TPluginDefinition* (*CreatePluginDefinitionFunction)();
typedef TPlugin* (*CreatePluginFunction)(TEntity* entity, TPluginDefinition* definition);

class TPluginRegisterEntry
{
public:
	TPluginRegisterEntry(const char* typeName, CreatePluginDefinitionFunction definitionCallback, CreatePluginFunction instanceCallback);

	~TPluginRegisterEntry();

	const TString& GetTypeName() const;

	CreatePluginDefinitionFunction GetDefinitionFunction() const;

	CreatePluginFunction GetInstanceFunction() const;

private:
	TString m_typeName;

	CreatePluginDefinitionFunction m_createDefinitionFunction;
	CreatePluginFunction m_createPluginFunction;
};

#endif
