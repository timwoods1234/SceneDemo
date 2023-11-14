#ifndef __TUISCENEENTRY_H__
#define __TUISCENEENTRY_H__

class TRenderableInterface;

struct TUISceneEntry
{
	TUISceneEntry()
	:	renderable(NULL),
		depth(0.f),
		nextEntry(NULL)
	{
	}

	TRenderableInterface* renderable;

	float depth;

	TUISceneEntry* nextEntry;
};

#endif
