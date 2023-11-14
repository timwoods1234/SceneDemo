#ifndef __TSUBMESHINFO_H__
#define __TSUBMESHINFO_H__

class TSkin;

struct TSubMeshInfo
{
	TSubMeshInfo()
		:	numIndices(0),
			startIndex(0),
			skin(NULL)
	{
	}

	unsigned int numIndices;
	unsigned int startIndex;

	TSkin* skin;
};

#endif
