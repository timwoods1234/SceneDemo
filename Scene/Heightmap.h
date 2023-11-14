#ifndef __HEIGHTMAP_H__
#define __HEIGHTMAP_H__

#ifndef __TENGINEINCLUDED_H__
#include "TEngine.h"
#endif

class Heightmap
{
public:
	Heightmap(const TString& filename, float heightScale, int width, int height);

	~Heightmap();

	float GetHeight(int x, int z);

	float GetMinHeight() const;

	float GetMaxHeight() const;

private:
	void Load(const TString& filename, float heightScale);

	bool InBounds(int x, int y);

	void ApplyFilter();

	float Sample3x3(int x, int y);

	TDynamicArray<float> m_values;

	int m_width;
	int m_height;

	float m_minHeight;
	float m_maxHeight;
};

#endif
