#include "TDebugRenderer.h"
#include "TLocator.h"
#include "TRendererInterface.h"
#include "TMaterial.h"
#include "TSkin.h"
#include "TMesh.h"
#include "TMatrix.h"
#include "TSkin.h"
#include "TScreenOutputStream.h"
#include "TTimerInterface.h"
#include "TEventRender.h"
#include "TEventUIRender.h"
#include "TEventUIUpdate.h"

//-------------------------------------------------------------------------------
DefineSingleton(TDebugRenderer);

//-------------------------------------------------------------------------------
TDebugRenderer::TDebugRenderer()
:	m_initialized(false),
	m_mesh(NULL)
{
	m_color.Set(1.f, 1.f, 1.f, 1.f);
	m_screenOutputStream = TNew TScreenOutputStream();

	TEventRender::Get()->Register(this, &TDebugRenderer::OnRender);
	TEventUIRender::Get()->Register(this, &TDebugRenderer::OnRenderUI);
	TEventUIUpdate::Get()->Register(this, &TDebugRenderer::OnUpdate);
}

//-------------------------------------------------------------------------------
TDebugRenderer::~TDebugRenderer()
{
	TEventRender::Get()->Unregister(this, &TDebugRenderer::OnRender);
	TEventUIRender::Get()->Unregister(this, &TDebugRenderer::OnRenderUI);
	TEventUIUpdate::Get()->Unregister(this, &TDebugRenderer::OnUpdate);

	TSafeDelete(m_screenOutputStream);
	TMesh::Release(m_mesh);
}

//-------------------------------------------------------------------------------
void TDebugRenderer::Initialize()
{
	TMaterial mat;

	mat.diffuseColor = m_color;

	TSkin* skin = TSkin::Acquire();
	skin->SetMaterial(mat);

	m_mesh = TMesh::Acquire();
	m_mesh->SetShaderByName("DiffuseRGB");
	m_mesh->MarkDynamic();
	m_mesh->SetSkin(skin);

	TSkin::Release(skin);

	m_initialized = true;
}

//-------------------------------------------------------------------------------
void TDebugRenderer::SetColor(const TColor& color)
{
	if (!m_initialized)
	{
		Initialize();
	}

	if (!TColorEqual(m_color, color))
	{
		m_color = color;

		TSkin* skin = m_mesh->GetSkin(0);

		TMaterial material = skin->GetMaterial();
		material.diffuseColor = m_color;

		skin->SetMaterial(material);
	}
}

//-------------------------------------------------------------------------------
void TDebugRenderer::DrawLine(const TVector3& start, const TVector3& end)
{
	if (!m_initialized)
	{
		Initialize();
	}

	TVertex positions[2];

	positions[0].position = start;
	positions[1].position = end;

	m_mesh->SetVertices(&positions, 2);

	TLocator::GetRenderer()->DrawLineList(*m_mesh);
}

//-------------------------------------------------------------------------------
void TDebugRenderer::DrawCube(const TVector3& min, const TVector3& max)
{
	if (!m_initialized)
	{
		Initialize();
	}

	TVector3 positions[8];

	positions[0] = min;
	positions[1].Set(min.x, max.y, min.z);
	positions[2].Set(max.x, max.y, min.z);
	positions[3].Set(max.x, min.y, min.z);
	positions[4].Set(min.x, min.y, max.z);
	positions[5].Set(max.x, min.y, max.z);
	positions[6] = max;
	positions[7].Set(min.x, max.y, max.z);

	TVertex vertices[24];

	vertices[0].position = positions[0];
	vertices[1].position = positions[1];
	vertices[2].position = positions[1];
	vertices[3].position = positions[2];
	vertices[4].position = positions[2];
	vertices[5].position = positions[3];
	vertices[6].position = positions[3];
	vertices[7].position = positions[0];

	vertices[8].position = positions[4];
	vertices[9].position = positions[5];
	vertices[10].position = positions[5];
	vertices[11].position = positions[6];
	vertices[12].position = positions[6];
	vertices[13].position = positions[7];
	vertices[14].position = positions[7];
	vertices[15].position = positions[4];

	vertices[16].position = positions[0];
	vertices[17].position = positions[4];
	vertices[18].position = positions[3];
	vertices[19].position = positions[5];
	vertices[20].position = positions[1];
	vertices[21].position = positions[7];
	vertices[22].position = positions[2];
	vertices[23].position = positions[6];

	m_mesh->SetVertices(&vertices, 24);

	TLocator::GetRenderer()->DrawLineList(*m_mesh);
}

//-------------------------------------------------------------------------------
void TDebugRenderer::DrawSphere(const TVector3& middle, float radius)
{
	TVertex vertices[50];

	for (int index = 0; index < 24; index++)
	{
		float fraction = TWO_PI * ((float)index / 24);

		vertices[index].position.Set(cosf(fraction) * radius, sinf(fraction) * radius, 0.f);

		//vertices[index + 25].position.Set(0.f, sinf(fraction) * radius, cosf(fraction) * radius);

		vertices[index + 25].position.Set(cosf(fraction) * radius, 0.f, sinf(fraction) * radius);
	}

	vertices[24].position = vertices[0].position;
	vertices[49].position = vertices[25].position;

	for (int index = 0; index < 50; index++)
	{
		vertices[index].position += middle;
	}

	m_mesh->SetVertices(&vertices[0], 50);

	TLocator::GetRenderer()->DrawLineStrip(*m_mesh);
}

//-------------------------------------------------------------------------------
void TDebugRenderer::DrawTextLine(const char* text, int x, int y, const TColor& color)
{
	m_screenOutputStream->SetColor(color);
	m_screenOutputStream->SetPosition(x, y);
	m_screenOutputStream->WriteString(text);
}

//-------------------------------------------------------------------------------
void TDebugRenderer::AddLine(const TVector3& start, const TVector3& end, const TColor& color, float duration)
{
	TDebugRenderEntry entry;
	entry.type = TDebugRenderEntryType::Line;
	entry.start = start;
	entry.end = end;
	entry.color = color;
	entry.expiryTime = TLocator::GetTimer()->GetAppTime() + duration;

	m_renderEntries.Add(entry);
}

//-------------------------------------------------------------------------------
void TDebugRenderer::AddCube(const TVector3& min, const TVector3& max, const TColor& color, float duration)
{
	TDebugRenderEntry entry;
	entry.type = TDebugRenderEntryType::Cube;
	entry.start = min;
	entry.end = max;
	entry.color = color;
	entry.expiryTime = TLocator::GetTimer()->GetAppTime() + duration;

	m_renderEntries.Add(entry);
}

//-------------------------------------------------------------------------------
void TDebugRenderer::AddSphere(const TVector3& middle, float radius, const TColor& color, float duration)
{
	TDebugRenderEntry entry;
	entry.type = TDebugRenderEntryType::Sphere;
	entry.start = middle;
	entry.radius = radius;
	entry.color = color;
	entry.expiryTime = TLocator::GetTimer()->GetAppTime() + duration;

	m_renderEntries.Add(entry);
}

//-------------------------------------------------------------------------------
void TDebugRenderer::AddText(const char* text, const TColor& color, float duration)
{
	TDebugTextEntry textEntry;
	textEntry.text = text;
	textEntry.color = color;
	textEntry.expiryTime = TLocator::GetTimer()->GetAppTime() + duration;
	
	m_textEntries.Add(textEntry);
}

//-------------------------------------------------------------------------------
void TDebugRenderer::OnUpdate()
{
	float currentAppTime = TLocator::GetTimer()->GetAppTime();

	for (int index = m_textEntries.GetSize() - 1; index >= 0; index--)
	{
		if (currentAppTime >= m_textEntries[index].expiryTime)
		{
			m_textEntries.RemoveAt(index);
		}
	}

	for (int index = m_renderEntries.GetSize() - 1; index >= 0; index--)
	{
		if (currentAppTime >= m_renderEntries[index].expiryTime)
		{
			m_renderEntries.RemoveAt(index);
		}
	}
}

//-------------------------------------------------------------------------------
void TDebugRenderer::OnRender()
{
	for (unsigned int index = 0; index < m_renderEntries.GetSize(); index++)
	{
		SetColor(m_renderEntries[index].color);

		switch (m_renderEntries[index].type)
		{
			case TDebugRenderEntryType::Cube:
			{
				DrawCube(m_renderEntries[index].start, m_renderEntries[index].end);
			}
			break;

			case TDebugRenderEntryType::Line:
			{
				DrawLine(m_renderEntries[index].start, m_renderEntries[index].end);
			}
			break;
			
			case TDebugRenderEntryType::Sphere:
			{
				DrawSphere(m_renderEntries[index].start, m_renderEntries[index].radius);
			}
			break;
		}
	}
}

//-------------------------------------------------------------------------------
void TDebugRenderer::OnRenderUI()
{
	m_screenOutputStream->SetPosition(10, 10);

	for (unsigned int index = 0; index < m_textEntries.GetSize(); index++)
	{
		m_screenOutputStream->SetColor(m_textEntries[index].color);

		m_screenOutputStream->WriteString(m_textEntries[index].text.GetPointer());
	}
}