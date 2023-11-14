#include "TAudioInterface.h"

//-------------------------------------------------------------------------------
TAudioInterface::TAudioInterface()
    : m_soundAvailable(true)
{
}

//-------------------------------------------------------------------------------
TAudioInterface::~TAudioInterface()
{
}

//-------------------------------------------------------------------------------
bool TAudioInterface::IsSoundAvailable() const
{
    return m_soundAvailable;
}
