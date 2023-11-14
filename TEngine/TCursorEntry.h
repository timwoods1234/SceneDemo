#ifndef __TCURSORENTRY_H__
#define __TCURSORENTRY_H__

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

//-------------------------------------------------------------------------------
enum TouchPhase
{
	Began,		// A finger touched the screen.
	Moved,		// A finger moved on the screen.
	Stationary,	// A finger is touching the screen but hasn't moved.
	Ended,		// A finger was lifted from the screen. This is the final phase of a touch.
	Canceled,	// The system cancelled tracking for the touch.
};

//-------------------------------------------------------------------------------
struct TCursorEntry
{
	TVector2 position;
	TVector2 oldPosition;
	int id;
	bool down;
	bool wasDown;
	bool dead;

	bool IsPressed()
	{
		return (down && !wasDown);
	}

	bool IsReleased()
	{
		return (wasDown && !down);
	}
};

#endif
