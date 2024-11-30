#ifndef __FRACTALDATA_H__
#define __FRACTALDATA_H__

#ifndef __TENGINEINCLUDED_H__
#include "TEngine.h"
#endif

class FractalData
{
public:
	FractalData();

	double Get(unsigned int x, unsigned int y) const;

	void Set(unsigned int x, unsigned int y, double val);

	void Clear();

	void SetSize(unsigned int x, unsigned int y);

	unsigned int GetSize() const;

	unsigned int GetWidth() const;

	unsigned int GetHeight() const;

	double GetMin() const;

	double GetMax() const;

	void Finalize();

private:
	TDynamicArray<double> m_values;

	int m_width;
	int m_height;

	double m_min;
	double m_max;
};

#endif
