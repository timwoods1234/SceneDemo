#include "GameWorld.h"
#include "GrassBatcher.h"
#include "Terrain.h"

//-------------------------------------------------------------------------------
GameWorld::GameWorld(const Terrain* terrain)
{
	m_terrain = terrain;

	TXMLReader reader("Assets/Data/World.xml", *this);
}

//-------------------------------------------------------------------------------
GameWorld::~GameWorld()
{
	for (unsigned int index = 0; index < m_scenery.GetSize(); index++)
	{
		TSafeDelete(m_scenery[index]);
	}

	m_scenery.Clear();
}

//-------------------------------------------------------------------------------
TXMLObject* GameWorld::HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects)
{
	if (strID == "Entity")
	{
		TString definitionName = TDataVariant::Find("definition", objects).GetString();

		TEntityDefinition* definition = TEntityDefinition::Acquire(definitionName.GetPointer());
		
		if (definition != NULL)
		{
			TEntity* entity = TNew TEntity(definition);
			m_scenery.Add(entity);

			TEntityDefinition::Release(definition);

			return entity;
		}
	}
	else if (strID == "GrassPosition")
	{
		TVector3 grassPosition;

		grassPosition.x = TDataVariant::Find("x", objects).GetFloat();
		grassPosition.z = TDataVariant::Find("z", objects).GetFloat();

		BuildGrassPatch(grassPosition);
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void GameWorld::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
}

//-------------------------------------------------------------------------------
void GameWorld::FinaliseLoad()
{
	GrassBatcher::Get()->RebuildMesh();

	for (unsigned int index = 0; index < m_scenery.GetSize(); index++)
	{
		TVector3 position = m_scenery[index]->GetPosition();

		position.y = m_terrain->GetHeight(position.x, position.z);

		m_scenery[index]->SetPosition(position);
	}
}

//-------------------------------------------------------------------------------
void GameWorld::Write(TXMLWriter& writer)
{
}

//-------------------------------------------------------------------------------
void GameWorld::GetAngularDistance(float distance, float angle, TVector3& result)
{
	result.Set((float)cos(angle) * distance, 0.f, -1.f * (float)sin(angle) * distance);
}

//-------------------------------------------------------------------------------
void GameWorld::BuildGrassPatch(const TVector3& center)
{
	unsigned int numGrassPositions = 6;
	TVector3 grassPosition;
	float angleIncrement = (2 * PI) / numGrassPositions;

	for (unsigned int index = 0; index < numGrassPositions; index++)
	{
		GetAngularDistance(3.f, index * angleIncrement, grassPosition);

		grassPosition = grassPosition + center;
		grassPosition.y = m_terrain->GetHeight(grassPosition.x, grassPosition.z);

		GrassBatcher::Get()->AddGrassPosition(grassPosition);
	}
}