#ifndef __TXMLSTREAM_H__
#define __TXMLSTREAM_H__

// Stream to xml file

#ifndef __TFILESTREAM_H__
#include "TFileStream.h"
#endif

#ifndef __TXMLATTRIBUTE_H__
#include "TXMLAttribute.h"
#endif

class TXMLStream : public TFileStream
{
public:
				TXMLStream();

				~TXMLStream();

	void		SetIndentLevel(int level);

	int			GetIndentLevel() const;

	const char*	ReadString();

	bool		WriteString(const char* str);

private:
	int m_indentLevel;
};

#endif
