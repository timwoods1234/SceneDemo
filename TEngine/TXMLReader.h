#ifndef __TXMLREADER_H__
#define __TXMLREADER_H__

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

class TXMLFile;

class TXMLReader
{
public:
	TXMLReader(const char* filename, TXMLObject& rootObject);

	bool WasError() const;
private:
	void ParseFile(TXMLFile& file);
	void ReadEndElement();

	TDynamicSet<TXMLObject*> m_loadStack;

	bool m_error;
	TXMLObject* m_rootObject;
	TXMLObject* m_currentObject;
};

#endif
