#ifndef __TD3DFONT_H__
#define __TD3DFONT_H__

#ifndef __TPLATFORM_H__
#include "TPlatform.h"
#endif

#ifndef __TDIRECT3D_H__
#include "TDirect3D.h"
#endif

#ifndef __TFONT_H__
#include "TFont.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

class TD3DFont : public TFont,
                 public TEventListener
{
public:
    TD3DFont(const char* filename, LPDIRECT3DDEVICE9 device);

    ~TD3DFont();

    void PrintText(const TVector2& position, const char* formattedText, ...);

    void OnLostDevice();

    void OnResetDevice();

private:
    ID3DXSprite* m_d3dSprite;

    LPD3DXFONT m_font;
};

#endif

