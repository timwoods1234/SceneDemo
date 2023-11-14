#ifndef __TXMLTAGTYPE_H__
#define __TXMLTAGTYPE_H__

enum TXMLTagType
{
	TagType_ElementStart = 0,
	TagType_ElementEnd = 1,
	TagType_Attribute = 2,
	TagType_Stream = 3,
	TagType_SaveHeader = 4,
};

#endif
