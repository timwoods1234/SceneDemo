#include "LightPluginDefinition.h"
#include "LightPlugin.h"
#include "TPluginRegister.h"

//-------------------------------------------------------------------------------
RegisterPluginType("Light", LightPluginDefinition, LightPlugin);

//-------------------------------------------------------------------------------
LightPluginDefinition::LightPluginDefinition()
{
	m_name = "Light";
}

//-------------------------------------------------------------------------------
LightPluginDefinition::~LightPluginDefinition()
{

}
