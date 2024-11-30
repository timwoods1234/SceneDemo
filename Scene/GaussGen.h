#ifndef __GAUSSGEN_H__
#define __GAUSSGEN_H__

// Gaussian number generator

class GaussGen
{
public:
    GaussGen();

	~GaussGen();

    double GaussianNumber();

private:

    unsigned int m_seed;
    int m_arand;
    double m_gaussAdd;
	double m_numer;
	double m_denom;
};

#endif
