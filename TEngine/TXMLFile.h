#ifndef __TXMLFILE_H__
#define __TXMLFILE_H__

#ifndef __TXMLATTRIBUTE_H__
#include "TXMLAttribute.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TXMLFile
{
public:
	TXMLFile();
	TXMLFile(const char* filename);
	~TXMLFile();

	// read
	void Rewind();
	bool HasMoreAttributes() const;
	bool WasError() const;
	const TXMLAttribute& GetNextAttribute();

	// write
	void Save(const char* filename);
	void AddXMLAttribute(const TXMLAttribute& newAttribute);

private:
	void Read(const char* filename);
	void ParseLine(const char* line);

	void ParseElementAttributes(const TString& line);
	void ParseElementStart(const TString& line);
	void ParseElementEnd(const TString& line);
	bool IsLineValid(const TString& line);

	TDynamicSet<TXMLAttribute> m_data;
	unsigned int m_currentIndex;
	bool m_error;
};

#endif
