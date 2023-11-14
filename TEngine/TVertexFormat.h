#ifndef __TVERTEXFORMAT_H__
#define __TVERTEXFORMAT_H__

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TVERTEXFORMATENTRY_H__
#include "TVertexFormatEntry.h"
#endif

class TVertexFormat : public TXMLObject
{
public:
	TVertexFormat(const char* filename);
	virtual ~TVertexFormat();

	const TString& GetId() const;

	unsigned int GetStride() const;

	virtual void Setup() = 0;

	TXMLObject* HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects);
	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();
	void Write(TXMLWriter& writer);

protected:
	TDynamicSet<TVertexFormatEntry> m_formatEntries;

	unsigned int m_stride;
	TString m_id;

private:
	void ComputeStride();
};

#endif
