#include "ModelPlugin.h"
#include "TRendererInterface.h"
#include "TLocator.h"
#include "TRendererInterface.h"
#include "TEntity.h"
#include "TSceneInterface.h"
#include "TMesh.h"
#include "TVector4.h"
#include "TShader.h"

//-------------------------------------------------------------------------------
ModelPlugin::ModelPlugin(TEntity* entity, TPluginDefinition* definition)
:	TRenderableInterface(entity, definition),
	m_mesh(NULL)
{
	ModelPluginDefinition* modelDefinition = static_cast<ModelPluginDefinition*>(definition);

	if (modelDefinition != NULL)
	{
		TMesh* mesh = TMesh::Acquire(modelDefinition->GetFilename().GetPointer());

		SetMesh(mesh);
	}
}

//-------------------------------------------------------------------------------
ModelPlugin::~ModelPlugin()
{
	TLocator::GetScene()->RemoveEntry(this);

	TMesh::Release(m_mesh);
}

//-------------------------------------------------------------------------------
void ModelPlugin::OnRender()
{
	TLocator::GetRenderer()->AddToRenderQueue(m_entity, m_mesh);
}

//-------------------------------------------------------------------------------
void ModelPlugin::ComputeBounds(TAABB &box)
{
	box = m_mesh->GetBoundingBox();

	TMatrix matTransform;
	matTransform.Translate(m_entity->GetPosition());

	box.Transform(matTransform);
}

//-------------------------------------------------------------------------------
TMesh* ModelPlugin::GetMesh() const
{
	return m_mesh;
}

//-------------------------------------------------------------------------------
void ModelPlugin::SetMesh(TMesh* mesh)
{
	if (m_mesh != NULL)
	{
		TMesh::Release(m_mesh);

		TLocator::GetScene()->RemoveEntry(this);
	}

	m_mesh = mesh;

	if (m_mesh != NULL)
	{
		TLocator::GetScene()->AddEntry(this);
	}
}