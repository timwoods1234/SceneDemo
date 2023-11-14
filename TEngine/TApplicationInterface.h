#ifndef __TAPPLICATIONINTERFACE_H__
#define __TAPPLICATIONINTERFACE_H__

class TApplicationInterface
{
public:
	TApplicationInterface();

	virtual ~TApplicationInterface();

	virtual void Run();

	virtual void Quit() = 0;

protected:
	void UpdateInput();

	void Render();
	
	bool m_initialized;
	bool m_paused;
};

#endif
