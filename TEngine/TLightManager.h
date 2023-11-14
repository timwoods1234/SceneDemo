#ifndef __TLIGHTMANAGER_H__
#define __TLIGHTMANAGER_H__

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class LightPlugin;
class TShader;

class TLightManager : public TSingleton<TLightManager>
{
public:
	TLightManager();

	~TLightManager();

	void AddLight(LightPlugin* plugin);

	void RemoveLight(LightPlugin* plugin);

	LightPlugin* GetLight(const char* name) const;

	void ApplyLighting(TShader* shader);

private:
	TDynamicSet<LightPlugin*> m_lights;
};

#endif
