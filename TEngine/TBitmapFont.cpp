#include "TBitmapFont.h"
#include "TShader.h"
#include "TLocator.h"
#include "TRendererInterface.h"
#include "TTexture.h"
#include "TTextStream.h"

//-------------------------------------------------------------------------------
TBitmapFont::TBitmapFont(const char* filename)
:	TFont(filename)
{
	m_shader = TShader::Acquire("Standard2D");

	m_renderSize = (float)m_size / 14.f;

	LoadTexture(filename);
	LoadMetrics(filename);
}

//-------------------------------------------------------------------------------
TBitmapFont::~TBitmapFont()
{
	TShader::Release(m_shader);

	TTexture::Release(m_texture);
}

//-------------------------------------------------------------------------------
void TBitmapFont::PrintText(const TVector2& position, const char* formattedText, ...)
{
    char *args;
    args = (char*)&formattedText + sizeof(formattedText);

    vsprintf_s(m_formatBuffer, c_formatBufferSize, formattedText, args);

	TVector2 renderPosition = position;
	size_t length = TStringHelper::TStrLen(formattedText);

	char currentChar;
	TVector4 texCoords;

	for (unsigned int index = 0; index < length; index++)
	{
		currentChar = formattedText[index];
		
		texCoords.x = (currentChar % 16) / 16.f;
		texCoords.z = texCoords.x + (1 / 16.0f);

		texCoords.y = (currentChar - (currentChar % 16)) / 256.0f;
		texCoords.w = texCoords.y + 1 / 16.0f;

		TLocator::GetRenderer()->Draw2D(m_texture, renderPosition, texCoords, 0.f, m_characterWidth * m_renderSize, m_characterHeight * m_renderSize);
		
		renderPosition.x += m_widths[currentChar] * m_renderSize;
	}
}

//-------------------------------------------------------------------------------
void TBitmapFont::LoadTexture(const char* filename)
{
	TString textureFilename = filename;

	// TODO: implement replace
	textureFilename.Remove(textureFilename.LastIndexOf('.'));
	textureFilename += ".png";

	m_texture = TTexture::Acquire(textureFilename.GetPointer());

	TASSERT((m_texture != NULL), "[TBitmapFont::LoadResource] Failed to load Texture");

	m_characterWidth = m_texture->GetWidth() / 16.f;
	m_characterHeight = m_texture->GetHeight() / 16.f;
}

//-------------------------------------------------------------------------------
void TBitmapFont::LoadMetrics(const char* filename)
{
	TString metricsFilename = filename;

	// TODO: implement replace
	metricsFilename.Remove( metricsFilename.LastIndexOf('.') );
	metricsFilename += ".ini";

	FILE* metricsFile = NULL;
	fopen_s(&metricsFile, metricsFilename.GetPointer(), "rb");

	TASSERT((metricsFile != NULL), "[TBitmapFont::LoadResource] Metrics file missing");

	TTextStream stream;
	stream.OpenRead(metricsFilename.GetPointer());

	int index = 0;
	TString line = stream.ReadString();
	TDynamicSet<TString> parts;

	while (index < 256)
	{
		index++;

		line = stream.ReadString();

		line.Split('=', parts);

		int index = TStringHelper::ConvertToInt(parts[0].GetPointer());
		int value = TStringHelper::ConvertToInt(parts[1].GetPointer());

		m_widths[index] = value;
	}

	fclose(metricsFile);
}