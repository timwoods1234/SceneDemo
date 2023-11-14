#include "TFileStream.h"

//-------------------------------------------------------------------------------
TFileStream::TFileStream()
:	m_file(NULL),
	m_readMode(false),
	m_writeMode(false),
	m_endOfFile(false)
{
}

//-------------------------------------------------------------------------------
TFileStream::~TFileStream()
{
	Close();
}

//-------------------------------------------------------------------------------
bool TFileStream::EndOfFile() const
{
	return m_endOfFile;
}

//-------------------------------------------------------------------------------
bool TFileStream::OpenRead(const char* filename)
{
    if (m_file != NULL)
	{
        return false;
	}

    fopen_s(&m_file, filename, "r");
    m_readMode = (m_file != NULL);

	m_endOfFile = false;

    return m_readMode;
}

//-------------------------------------------------------------------------------
bool TFileStream::OpenWrite(const char* filename)
{
    if (m_file != NULL)
	{
        return false;
	}

    fopen_s(&m_file, filename, "w");
    m_writeMode = (m_file != NULL);

	m_endOfFile = false;

    return m_writeMode;
}

//-------------------------------------------------------------------------------
void TFileStream::Close()
{
    if (m_file != NULL)
	{
        fclose(m_file);
	}

    m_writeMode = false;
    m_readMode  = false;
}

//-------------------------------------------------------------------------------
int TFileStream::Read(int bytes, void* buffer)
{
    if (!m_readMode)
	{
        return 0;
	}

    int readCount = fread(buffer, 1, bytes, m_file);

	if (readCount != bytes)
	{
		if (ferror(m_file) != 0)
		{
			m_error = true;

			return -1;
		}
	}

	if (feof(m_file) != 0)
	{
		m_endOfFile = true;
	}

	return readCount;
}

//-------------------------------------------------------------------------------
int TFileStream::Write(int bytes, const void* buffer)
{
    if (!m_writeMode)
	{
        return 0;
	}

    int writeCount = fwrite(buffer, 1, bytes, m_file);

	if (ferror(m_file) != 0)
	{
		m_error = true;

		return -1;
	}

	return writeCount;
}