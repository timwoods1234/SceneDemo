//-------------------------------------------------------------------------------
inline TString& TString::operator=(const char* data)
{
	m_poolEntry = TStringPool::Reallocate(m_poolEntry, data);

	return *this;
}

//-------------------------------------------------------------------------------
bool TString::operator==(const TString& other) const
{
	if (m_poolEntry != 0 && other.m_poolEntry != 0)
	{
		return m_poolEntry->blockOffset == other.m_poolEntry->blockOffset;
	}
	else if (m_poolEntry == 0 && other.m_poolEntry == 0)
	{
		return true;
	}

	return false;
}
