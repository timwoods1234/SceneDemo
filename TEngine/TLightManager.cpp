#include "TLightManager.h"
#include "TShader.h"
#include "LightPlugin.h"

//-------------------------------------------------------------------------------
DefineSingleton(TLightManager);

//-------------------------------------------------------------------------------
TLightManager::TLightManager()
{
}

//-------------------------------------------------------------------------------
TLightManager::~TLightManager()
{
}

//-------------------------------------------------------------------------------
void TLightManager::AddLight(LightPlugin* plugin)
{
	m_lights.Add(plugin);
}

//-------------------------------------------------------------------------------
void TLightManager::RemoveLight(LightPlugin* plugin)
{
	m_lights.Remove(plugin);
}

//-------------------------------------------------------------------------------
LightPlugin* TLightManager::GetLight(const char* name) const
{
	LightPlugin* result = NULL;

	for (unsigned int index = 0; index < m_lights.GetSize(); index++)
	{
		if (m_lights[index]->GetId() == name)
		{
			result = m_lights[index];
			break;
		}
	}

	return result;
}

//-------------------------------------------------------------------------------
void TLightManager::ApplyLighting(TShader* shader)
{
	for (unsigned int index = 0; index < m_lights.GetSize(); index++)
	{
		switch (m_lights[index]->GetType())
		{
			case LightType_SpotLight:
			{
				shader->SetLight(m_lights[index]->GetId().GetPointer(), &(m_lights[index]->GetSpotLight()));
			}
			break;

			case LightType_PointLight:
			{
				shader->SetLight(m_lights[index]->GetId().GetPointer(), &(m_lights[index]->GetPointLight()));
			}
			break;

			case LightType_DirectionalLight:
			{
				shader->SetLight(m_lights[index]->GetId().GetPointer(), &(m_lights[index]->GetDirectionalLight()));
			}
			break;

			default:
			{
			}
			break;
		}
	}
}