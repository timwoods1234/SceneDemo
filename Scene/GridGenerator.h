#ifndef __GRIDGENERATOR_H__
#define __GRIDGENERATOR_H__

#ifndef __TENGINEINCLUDED_H__
#include "TEngine.h"
#endif

struct TVertex;

class GridGenerator
{
public:
	static void CreateGrid(TDynamicArray<TVertex>& verts, TDynamicArray<unsigned short>& indices, int numVertRows, int numVertCols, float dx, float dz);
};

#endif
