#include "TUtil.h"
#include "TMemory.h"

//-------------------------------------------------------------------------------
TString TUtil::GetFilePath(const char* filename)
{
	TString strFilename(filename);
	TString strDirectory;

	int indexOfSlash = strFilename.LastIndexOf('\\');

	if (indexOfSlash == -1)
	{
		indexOfSlash = strFilename.LastIndexOf('/');
	}

	if (indexOfSlash == -1)
	{
		strDirectory = ".";
	}
	else if (indexOfSlash == 0)
	{
		strDirectory = "/";
	}
	else
	{
		strDirectory = strFilename.SubString(0, indexOfSlash + 1);
	}

	return strDirectory;
}
