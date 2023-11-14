#ifndef __TAUDIOINTERFACE_H__
#define __TAUDIOINTERFACE_H__

// Base audio component.

class TSound;

class TAudioInterface
{
public:
                            TAudioInterface();

    virtual					~TAudioInterface();

	virtual TSound*			LoadSound(const char* filename) = 0;

    virtual void            UnloadSound(TSound* sound) = 0;

	virtual void			StopAllSounds() = 0;

	// volume between [0.0, 1.0]
	virtual void			SetVolume(float relativeVolume) = 0;

	virtual float			GetVolume() const = 0;

    bool                    IsSoundAvailable() const;

protected:
    bool                    m_soundAvailable;
};

#endif
