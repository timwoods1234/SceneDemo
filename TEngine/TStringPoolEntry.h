#ifndef __TSTRINGPOOLENTRY_H__
#define __TSTRINGPOOLENTRY_H__

struct TStringPoolEntry
{
	// string length + 1 for null terminator
	short blockLength;

	short blockOffset;
	short stringLength;

	unsigned int refCount;

	TStringPoolEntry* prevEntry;
	TStringPoolEntry* nextEntry;
};

#endif
