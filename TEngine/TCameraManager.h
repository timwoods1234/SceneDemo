#ifndef __TCAMERAMANAGER_H__
#define __TCAMERAMANAGER_H__

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TCamera;

class TCameraManager : public TSingleton<TCameraManager>
{
public:
    TCameraManager();

    ~TCameraManager();

    void OnRender();

	TCamera* GetCamera(const char* name);

private:
    void LoadCameras();

    TDynamicSet<TCamera*> m_cameras;
};

#endif

