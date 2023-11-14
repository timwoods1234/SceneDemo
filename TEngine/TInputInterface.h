#ifndef __TINPUTINTERFACE_H__
#define __TINPUTINTERFACE_H__

class TVector2;

class TInputInterface
{
public:
	TInputInterface() {}
	virtual ~TInputInterface() {}

	virtual bool Update() = 0;

	virtual bool	IsDown(unsigned int nID) = 0;
	virtual bool	IsPressed(unsigned int nID) = 0;	// first press
	virtual bool	IsReleased(unsigned int nID) = 0;
	virtual bool	IsAnyKeyDown() = 0;
	virtual bool	IsAnyKeyPressed() = 0;

	virtual char	GetPressedChar() = 0;

	virtual void	GetMousePosition(TVector2& outputPosition) = 0;

	virtual long	GetXAmt() = 0;
	virtual long	GetYAmt() = 0;
};

#endif
