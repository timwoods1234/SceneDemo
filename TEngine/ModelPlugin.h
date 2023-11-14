#ifndef __MODELPLUGIN_H__
#define __MODELPLUGIN_H__

#ifndef __TRENDERABLEINTERFACE_H__
#include "TRenderableInterface.h"
#endif

#ifndef __MODELPLUGINDEFINITION_H__
#include "ModelPluginDefinition.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

#ifndef __TMATRIX_H__
#include "TMatrix.h"
#endif

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

class TMesh;

class ModelPlugin : public TRenderableInterface,
					public TEventListener
{
public:
	static void Register();

	ModelPlugin(TEntity* entity, TPluginDefinition* definition);
	~ModelPlugin();

	void OnRender();
	void ComputeBounds(TAABB& box);

	TMesh* GetMesh() const;

	void SetMesh(TMesh* mesh);

private:
	TMesh* m_mesh;
};

#endif