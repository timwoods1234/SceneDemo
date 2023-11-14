#include "Heightmap.h"

//-------------------------------------------------------------------------------
Heightmap::Heightmap(const TString& filename, float heightScale, int width, int height)
{
	m_width = width;
	m_height = height;

	Load(filename, heightScale);
}

//-------------------------------------------------------------------------------
Heightmap::~Heightmap()
{
}

//-------------------------------------------------------------------------------
float Heightmap::GetHeight(int x, int z)
{
	unsigned int index = z * m_width + x;

	if (index < m_values.GetSize())
	{
		return m_values[index];
	}
	
	return -1.f;
}

//-------------------------------------------------------------------------------
void Heightmap::Load(const TString& filename, float heightScale)
{
	m_values.Resize(m_width * m_height);
	TDynamicArray<unsigned char> inValues(m_values.GetSize());

	TFileStream stream;
	stream.OpenRead(filename.GetPointer());
	stream.Read(inValues.GetSize(), &(inValues[0]));
	stream.Close();

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			int index = (y * m_width) + x;

			m_values[index] = ((float)inValues[index] * heightScale);
		}
	}

	// maybe make the type and power of the filter data driven
	ApplyFilter();
}

//-------------------------------------------------------------------------------
bool Heightmap::InBounds(int x, int y)
{
	return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

//-------------------------------------------------------------------------------
void Heightmap::ApplyFilter()
{
	TDynamicArray<float> tempValues(m_values.GetSize());

	m_minHeight = FLT_MAX;
	m_maxHeight = 0.f;

	for (int height = 0; height < m_height; height++)
	{
		for (int width = 0; width < m_width; width++)
		{
			float averageHeight = Sample3x3(width, height);
			tempValues[m_width * height + width] = averageHeight;

			if (averageHeight > m_maxHeight)
			{
				m_maxHeight = averageHeight;
			}
			if (averageHeight < m_minHeight)
			{
				m_minHeight = averageHeight;
			}
		}
	}

	m_values = tempValues;
}

//-------------------------------------------------------------------------------
float Heightmap::Sample3x3(int x, int y)
{
	float average = 0.f;
	float count = 0.f;

	for (int height = y - 1; height <= y + 1; height++)
	{
		for (int width = x - 1; width <= x + 1; width++)
		{
			if (InBounds(width, height))
			{
				average += GetHeight(width, height);

				count++;
			}
		}
	}

	TASSERT((count != 0.f), "[Heightmap::Sample3x3] Bad filter values");

	return average / count;
}

//-------------------------------------------------------------------------------
float Heightmap::GetMinHeight() const
{
	return m_minHeight;
}

//-------------------------------------------------------------------------------
float Heightmap::GetMaxHeight() const
{
	return m_maxHeight;
}