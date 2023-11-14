#ifndef __TSURFACE2D_H__
#define __TSURFACE2D_H__

class TTexture;
class TVector2;
class TVector4;

class TSurface2D
{
public:
	TSurface2D() {}

	virtual ~TSurface2D() {}

	virtual void AddSprite(TTexture* texture, const TVector2& position, const TVector4& texCoords, float rotation =0.f, float scaleX =1.f, float scaleY =1.f) = 0;

	virtual void Render() = 0;
};

#endif
