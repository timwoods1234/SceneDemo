
#include "GaussGen.h"
#include "TEngine.h"

//-------------------------------------------------------------------------------
GaussGen::GaussGen()
{
	m_seed = TLocator::GetTimer()->GetSystemTime();

	double two = 2;
	double thirtyone = 31;
	m_arand = (int)pow(two, thirtyone) - 1;

	double twelve = 12;
	m_gaussAdd = sqrt(twelve);

	m_numer = m_gaussAdd + m_gaussAdd;
	m_denom = (double)4 * m_arand;
}

//-------------------------------------------------------------------------------
GaussGen::~GaussGen()
{
}

//-------------------------------------------------------------------------------
double GaussGen::GaussianNumber()
{
    int index;
    double sum = 0;

    for (index = 1; index <= 4; index++)
	{
        sum += FastRandom(&m_seed, 0, 65535) * m_arand;
	}

    return ((sum * m_numer / m_denom) - m_gaussAdd);
}