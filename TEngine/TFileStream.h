#ifndef __TFILESTREAM_H__
#define __TFILESTREAM_H__

// Binary stream to file system

#include <stdio.h>

#ifndef __TSTREAMINTERFACE_H__
#include "TStreamInterface.h"
#endif

class TFileStream : public TStreamInterface
{
public:
	TFileStream();
	virtual ~TFileStream();

	virtual int  Read (int bytes, void * buffer);
    virtual int  Write (int bytes, const void * buffer);

    virtual bool OpenRead (const char* filename);
    virtual bool OpenWrite (const char* filename);
    virtual void Close ();

	bool EndOfFile() const;

protected:
    FILE*  m_file;
    bool   m_readMode;
    bool   m_writeMode;
	bool   m_endOfFile;
};

#endif