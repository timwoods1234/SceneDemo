#ifndef __TSTREAMINTERFACE_H__
#define __TSTREAMINTERFACE_H__

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TStreamInterface
{
public:
    virtual ~TStreamInterface();

    virtual int			Read (int bytes, void * buffer) = 0;
    virtual int			Write (int bytes, const void * buffer) = 0;

	virtual int			ReadInt();
	virtual float		ReadFloat();
	virtual const char*	ReadString();	// TODO: feels risky to return char* instead off TString; where is the memory?

	virtual bool		WriteInt(int n);
	virtual bool		WriteFloat(float f);
	virtual bool		WriteString(const char* str);

	bool				WasError() const;

protected:
	static const int c_workingBufferSize = 512;

	char m_workingBuffer[c_workingBufferSize];

	bool m_error;
};

#endif
