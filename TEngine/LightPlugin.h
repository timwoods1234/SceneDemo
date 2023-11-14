#ifndef __LIGHTPLUGIN_H__
#define __LIGHTPLUGIN_H__

#ifndef __TPLUGIN_H__
#include "TPlugin.h"
#endif

#ifndef __LIGHTPLUGINDEFINITION_H__
#include "LightPluginDefinition.h"
#endif

#ifndef __TPOINTLIGHT_H__
#include "TPointLight.h"
#endif

#ifndef __TDIRECTIONALLIGHT_H__
#include "TDirectionalLight.h"
#endif

#ifndef __TSPOTLIGHT_H__
#include "TSpotLight.h"
#endif

#ifndef __LIGHTTYPE_H__
#include "LightType.h"
#endif

class LightPlugin : public TPlugin
{
public:
	static void Register();

	LightPlugin(TEntity* entity, TPluginDefinition* definition);
	~LightPlugin();

	TXMLObject* HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects);
	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();

	LightType GetType() const;
	const TString& GetId() const;

	const TSpotLight& GetSpotLight() const;
	const TPointLight& GetPointLight() const;
	const TDirectionalLight& GetDirectionalLight() const;

private:
	void Apply(TPointLight& light);
	void Apply(TDirectionalLight& light);
	void Apply(TSpotLight& light);

	LightType m_type;
	TString m_id;

	TColor m_ambient;
	TColor m_diffuse;
	TColor m_specular;

	TVector3 m_direction;
	TVector3 m_attenuation;
	TVector3 m_position;

	float m_power;

	union
	{
		TSpotLight m_spotLight;
		TPointLight m_pointLight;
		TDirectionalLight m_directionalLight;
	};
};

#endif
