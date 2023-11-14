#include "ModelPluginDefinition.h"
#include "ModelPlugin.h"
#include "TPluginRegister.h"

//-------------------------------------------------------------------------------
RegisterPluginType("Model", ModelPluginDefinition, ModelPlugin);

//-------------------------------------------------------------------------------
ModelPluginDefinition::ModelPluginDefinition()
{
	m_name = "Model";
}

//-------------------------------------------------------------------------------
void ModelPluginDefinition::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_filename = TDataVariant::Find("filename", objects).GetString();
}

//-------------------------------------------------------------------------------
const TString& ModelPluginDefinition::GetFilename() const
{
	return m_filename;
}
