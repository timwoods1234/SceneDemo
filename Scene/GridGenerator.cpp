#include "TEngine.h"
#include "GridGenerator.h"
#include "TVertex.h"

//-------------------------------------------------------------------------------
void GridGenerator::CreateGrid(TDynamicArray<TVertex>& verts, TDynamicArray<unsigned short>& indices, int numVertRows, int numVertCols, float dx, float dz)
{
	int numCellRows = numVertRows - 1;
	int numCellCols = numVertCols - 1;

	int numTris = numCellRows * numCellCols * 2;

	float width = (float)numCellCols * dx;
	float depth = (float)numCellRows * dz;

	int numVertices = numVertRows * numVertCols;
	verts.Resize(numVertices);

	int k = 0;

	for (float i = 0; i < numVertRows; ++i)
	{
		for (float j = 0; j < numVertCols; ++j)
		{
			verts[k].position.x = j * dx - (width/2);
			verts[k].position.z = -i * dz + (depth/2);
			verts[k].position.y = 0.0f;

			verts[k].normal.Set(0.f, 1.f, 0.f);

			++k;
		}
	}

	int numIndices = numCellRows * numCellCols * 2 * 3;
	indices.Resize(numIndices);

	k = 0;
	for (int i = 0; i < numCellRows; ++i)
	{
		for (int j = 0; j < numCellCols; ++j)
		{
			indices[k] = i   * numVertCols + j;
			indices[k + 1] = i   * numVertCols + j + 1;
			indices[k + 2] = (i + 1) * numVertCols + j;

			indices[k + 3] = (i + 1) * numVertCols + j;
			indices[k + 4] = i   * numVertCols + j + 1;
			indices[k + 5] = (i + 1) * numVertCols + j + 1;

			k += 6;
		}
	}
}