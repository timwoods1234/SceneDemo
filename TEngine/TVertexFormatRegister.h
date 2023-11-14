#ifndef __TVERTEXFORMATREGISTER_H__
#define __TVERTEXFORMATREGISTER_H__

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TVertexFormat;

class TVertexFormatRegister
{
public:
	TVertexFormatRegister();

	virtual ~TVertexFormatRegister();

	void LoadAllFormats();

	TVertexFormat* GetVertexFormat(const TString& formatName);

protected:
	virtual TVertexFormat* CreateVertexFormat(const char* filepath) = 0;

	TDynamicSet<TVertexFormat*> m_vertexFormats;
};

#endif
