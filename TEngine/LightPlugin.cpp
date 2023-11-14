#include "LightPlugin.h"
#include "TLightManager.h"

//-------------------------------------------------------------------------------
LightPlugin::LightPlugin(TEntity* entity, TPluginDefinition* definition)
:	TPlugin(entity, definition),
	m_direction(0.f, 0.f, 0.f),
	m_attenuation(0.f, 0.f, 0.f),
	m_position(0.f, 0.f, 0.f),
	m_power(0.f) 
{
	m_ambient.Set(0.f, 0.f, 0.f, 0.f);
	m_diffuse.Set(0.f, 0.f, 0.f, 0.f);
	m_specular.Set(0.f, 0.f, 0.f, 0.f);

	m_type = LightType_Unknown;
}

//-------------------------------------------------------------------------------
LightPlugin::~LightPlugin()
{
	TLightManager::Get()->RemoveLight(this);
}

//-------------------------------------------------------------------------------
void LightPlugin::Apply(TPointLight& light)
{
	light.ambient = m_ambient;
	light.diffuse = m_diffuse;
	light.specular = m_specular;

	light.position = m_position;
	light.attenuation = m_attenuation;
}

//-------------------------------------------------------------------------------
void LightPlugin::Apply(TDirectionalLight& light)
{
	light.ambient = m_ambient;
	light.diffuse = m_diffuse;
	light.specular = m_specular;

	light.direction = m_direction;
}

//-------------------------------------------------------------------------------
void LightPlugin::Apply(TSpotLight& light)
{
	light.ambient = m_ambient;
	light.diffuse = m_diffuse;
	light.specular = m_specular;

	light.power = m_power;

	light.direction = m_direction;
	light.attenuation = m_attenuation;
	light.position = m_position;
}

//-------------------------------------------------------------------------------
TXMLObject* LightPlugin::HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects)
{
	if (strID == "Ambient")
	{
		m_ambient.r = TDataVariant::Find("r", objects).GetFloat();
		m_ambient.g = TDataVariant::Find("g", objects).GetFloat();
		m_ambient.b = TDataVariant::Find("b", objects).GetFloat();
		m_ambient.a = TDataVariant::Find("a", objects).GetFloat();
	}
	else if (strID == "Diffuse")
	{
		m_diffuse.r = TDataVariant::Find("r", objects).GetFloat();
		m_diffuse.g = TDataVariant::Find("g", objects).GetFloat();
		m_diffuse.b = TDataVariant::Find("b", objects).GetFloat();
		m_diffuse.a = TDataVariant::Find("a", objects).GetFloat();
	}
	else if (strID == "Specular")
	{
		m_specular.r = TDataVariant::Find("r", objects).GetFloat();
		m_specular.g = TDataVariant::Find("g", objects).GetFloat();
		m_specular.b = TDataVariant::Find("b", objects).GetFloat();
		m_specular.a = TDataVariant::Find("a", objects).GetFloat();
	}
	else if (strID == "Direction")
	{
		m_direction.x = TDataVariant::Find("x", objects).GetFloat();
		m_direction.y = TDataVariant::Find("y", objects).GetFloat();
		m_direction.z = TDataVariant::Find("z", objects).GetFloat();

		m_direction.Normalize();
	}
	else if (strID == "Attenuation")
	{
		m_attenuation.x = TDataVariant::Find("x", objects).GetFloat();
		m_attenuation.y = TDataVariant::Find("y", objects).GetFloat();
		m_attenuation.z = TDataVariant::Find("z", objects).GetFloat();
	}
	else if (strID == "Position")
	{
		m_position.x = TDataVariant::Find("x", objects).GetFloat();
		m_position.y = TDataVariant::Find("y", objects).GetFloat();
		m_position.z = TDataVariant::Find("z", objects).GetFloat();
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void LightPlugin::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_id = TDataVariant::Find("id", objects).GetString();
	m_power = TDataVariant::Find("power", objects).GetFloat();

	TString lightTypeName = TDataVariant::Find("type", objects).GetString();

	if (lightTypeName == "DirectionalLight")
	{
		m_type = LightType_DirectionalLight;
	}
	else if (lightTypeName == "SpotLight")
	{
		m_type = LightType_SpotLight;
	}
	else if (lightTypeName == "PointLight")
	{
		m_type = LightType_PointLight;
	}
}

//-------------------------------------------------------------------------------
void LightPlugin::FinaliseLoad()
{
	switch (m_type)
	{
		case LightType_SpotLight:
			{
				Apply(m_spotLight);
			}
			break;

		case LightType_PointLight:
			{
				Apply(m_pointLight);
			}
			break;

		case LightType_DirectionalLight:
			{
				Apply(m_directionalLight);
			}
			break;

		default:
			{
				TDebugPrint(("[LightPlugin::FinaliseLoad] Unrecognised light type"));
			}
			break;
	}

	if (m_type != LightType_Unknown)
	{
		TLightManager::Get()->AddLight(this);
	}
}

//-------------------------------------------------------------------------------
LightType LightPlugin::GetType() const
{
	return m_type;
}

//-------------------------------------------------------------------------------
const TSpotLight& LightPlugin::GetSpotLight() const
{
	return m_spotLight;
}

//-------------------------------------------------------------------------------
const TPointLight& LightPlugin::GetPointLight() const
{
	return m_pointLight;
}

//-------------------------------------------------------------------------------
const TDirectionalLight& LightPlugin::GetDirectionalLight() const
{
	return m_directionalLight;
}

//-------------------------------------------------------------------------------
const TString& LightPlugin::GetId() const
{
	return m_id;
}