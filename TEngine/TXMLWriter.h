#ifndef __TXMLWRITER_H__
#define __TXMLWRITER_H__

class TString;
class TXMLObject;

class TXMLFile;

class TXMLWriter
{
public:
	TXMLWriter(const char* filename, const TString& strRootTagId, TXMLObject& rootObject);

	void WriteElement(const TString& strTagId, TXMLObject& saveObject);
	void WriteDummyElementStart(const TString& strTagId);
	void WriteDummyElementEnd(const TString& strTagId);

	void WriteAttribute(const TString& strTagId, const char* value);
	void WriteAttribute(const TString& strTagId, int value);
	void WriteAttribute(const TString& strTagId, float value);
	void WriteAttribute(const TString& strTagId, bool value);

private:
	static const int c_formatBufferSize = 32;
	char m_formatBuffer[c_formatBufferSize];

	TXMLFile* m_file;
};

#endif
