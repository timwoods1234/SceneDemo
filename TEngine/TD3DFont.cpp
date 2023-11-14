#include "TD3DFont.h"
#include "TVector2.h"
#include "TD3DEventDeviceReset.h"
#include "TD3DEventDeviceLost.h"

//-------------------------------------------------------------------------------
TD3DFont::TD3DFont(const char* filename, LPDIRECT3DDEVICE9 device)
:   TFont(filename)
{
    if (FAILED(D3DXCreateSprite(device, &m_d3dSprite)))
    {
        TDebugPrint(("[TD3DTextPrinter::CreateFont] Failed to create sprite"));
    }

    HDC hDC;
    int height;

    TString fontFaceName = filename;
    int lastIndexOfSlash = fontFaceName.LastIndexOf('/');
    int indexOfExtension = fontFaceName.LastIndexOf('.') - 1;

	int count = fontFaceName.GetLength() - lastIndexOfSlash - (fontFaceName.GetLength() - indexOfExtension);

    fontFaceName = fontFaceName.SubString(lastIndexOfSlash + 1, count);

    unsigned long size = m_size;

    hDC = GetDC(NULL);
    height = -MulDiv(size, GetDeviceCaps(hDC, LOGPIXELSY), 72);
    ReleaseDC(NULL, hDC);

    if (FAILED(D3DXCreateFont(
        device,
        height, (height / 2), FW_SEMIBOLD, 1,
        false, DEFAULT_CHARSET,
        OUT_STROKE_PRECIS, ANTIALIASED_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, fontFaceName.GetPointer(),
        &m_font)))
    {
        TDebugPrint(("[TD3DTextPrinter::CreateFont] Couldn't create font for %s", filename));
    }

    TD3DEventDeviceLost::Get()->Register(this, &TD3DFont::OnLostDevice);
    TD3DEventDeviceReset::Get()->Register(this, &TD3DFont::OnResetDevice);
}

//-------------------------------------------------------------------------------
TD3DFont::~TD3DFont()
{
    TD3DEventDeviceLost::Get()->Unregister(this, &TD3DFont::OnLostDevice);
    TD3DEventDeviceReset::Get()->Unregister(this, &TD3DFont::OnResetDevice);

    SafeRelease(m_font);
    SafeRelease(m_d3dSprite);
}

//-------------------------------------------------------------------------------
void TD3DFont::PrintText(const TVector2& position, const char* formattedText, ...)
{
    char *args;
    args = (char*)&formattedText + sizeof(formattedText);

    vsprintf_s(m_formatBuffer, c_formatBufferSize, formattedText, args);

    m_d3dSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

    RECT rc = { (long)position.x, (long)position.y, 0, 0 };

    unsigned char r = (unsigned char)m_color.r * 255;
    unsigned char g = (unsigned char)m_color.g * 255;
    unsigned char b = (unsigned char)m_color.b * 255;

    D3DCOLOR color = D3DCOLOR_ARGB(255, r, g, b);

    m_font->DrawText(m_d3dSprite, formattedText, -1, &rc, DT_NOCLIP, color);

    m_d3dSprite->End();
}

//-------------------------------------------------------------------------------
void TD3DFont::OnLostDevice()
{
    m_d3dSprite->OnLostDevice();

    m_font->OnLostDevice();
}

//-------------------------------------------------------------------------------
void TD3DFont::OnResetDevice()
{
    m_d3dSprite->OnResetDevice();

    m_font->OnResetDevice();
}