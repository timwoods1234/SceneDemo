#include "FractalData.h"

//-------------------------------------------------------------------------------
FractalData::FractalData()
:	m_min(DBL_MAX)
,	m_max(0)
{

}

//-------------------------------------------------------------------------------
double FractalData::Get(unsigned int x, unsigned int y) const
{
	unsigned int index = y * m_width + x;

	if (index < m_values.GetSize())
	{
		return m_values[index];
	}

	return 0;
}

//-------------------------------------------------------------------------------
void FractalData::Set(unsigned int x, unsigned int y, double val)
{
	unsigned int index = y * m_width + x;

	if (index < m_values.GetSize())
	{
		m_values[index] = val;

		if (val < m_min)
		{
			m_min = val;
		}

		if (val > m_max)
		{
			m_max = val;
		}
	}
}

//-------------------------------------------------------------------------------
void FractalData::Clear()
{
	for (unsigned int index = 0; index < m_values.GetSize(); index++)
	{
		m_values[index] = 0;
	}
}

//-------------------------------------------------------------------------------
void FractalData::SetSize(unsigned int x, unsigned int y)
{
	m_width = x;
	m_height = y;

	m_values.Resize(x * y);
}

//-------------------------------------------------------------------------------
unsigned int FractalData::GetSize() const
{
	return m_width * m_height;
}

//-------------------------------------------------------------------------------
unsigned int FractalData::GetWidth() const
{
	return m_width;
}

//-------------------------------------------------------------------------------
unsigned int FractalData::GetHeight() const
{
	return m_height;
}

//-------------------------------------------------------------------------------
double FractalData::GetMin() const
{
	return m_min;
}

//-------------------------------------------------------------------------------
double FractalData::GetMax() const
{
	return m_max;
}

//-------------------------------------------------------------------------------
void FractalData::Finalize()
{
	if (m_min < 0.0)
	{
		for (unsigned int index = 0; index < m_values.GetSize(); index++)
		{
			m_values[index] -= m_min;
		}

		m_max -= m_min;
		m_min -= m_min;
	}
}