#include "RandomNumberGenerator.h"
#include "TEngine.h"

RandomNumberGenreator::RandomNumberGenreator()
{
	m_seed = (unsigned int)TLocator::GetTimer()->GetSystemTime();

	m_arand = (int)pow(2.0, 31.0) - 1;

	m_addition = (float)sqrt(12.0);

	m_numerator = m_addition + m_addition;

	m_denominator = (float)(4.0 * m_arand);
}

float RandomNumberGenreator::GetRandomNumber()
{
	float sum = 0.f;

	for (unsigned int index = 0; index <= 4; index++)
	{
		sum += (FastRandom(&m_seed, 0.f, 1.f) * m_arand);
	}

	return ((sum * m_numerator / m_denominator) - m_addition);
}
