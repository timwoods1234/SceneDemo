#ifndef __TMESHLOADERINTERFACE_H__
#define __TMESHLOADERINTERFACE_H__

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TMesh;

class TMeshLoaderInterface
{
public:
	TMeshLoaderInterface();

	virtual ~TMeshLoaderInterface();

	virtual bool LoadMeshFromFile(const char* filename, TMesh& mesh) = 0;

protected:
	static const TString c_defaultTexturePath;
};

#endif
