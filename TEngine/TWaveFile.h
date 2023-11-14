#ifndef __TWAVEFILE_H__
#define __TWAVEFILE_H__

#ifndef __TPLATFORM_H__
#include "TPlatform.h"
#endif

class TWaveFile
{
public:
    TWaveFile(const char* fileName);
    ~TWaveFile();

    bool	isVaild() const;
    bool	Read(int size, unsigned char* data, unsigned int* sizeRead);
    bool	Reset();

    void*	GetWaveFormat();
    void*	GetWaveRiffChunk();

private:
    void	Close();

    bool	m_valid;
    void*	m_waveFormat;
    void*	m_mmIOHandle;
    int		m_ckIn[5];
    int		m_ckInRiff[5];
};

#endif