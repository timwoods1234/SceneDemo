#include "TWindowsFileSystem.h"
#include "TWindowsApplication.h"
#include "TString.h"
#include "TStringHelper.h"

//-------------------------------------------------------------------------------
TWindowsFileSystem::TWindowsFileSystem(HWND window)
:	m_window(window)
{
}

//-------------------------------------------------------------------------------
TWindowsFileSystem::~TWindowsFileSystem()
{
}

//-------------------------------------------------------------------------------
void TWindowsFileSystem::OpenFileBrowser(bool fileMustExist, TString& result)
{
	char szFileName[MAX_PATH] = "";

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_window;
	ofn.lpstrFilter = "Save Files (*.bin)\0*.bin\0Text Files (*.txt)\0*.txt\0XML Files (*.xml)\0*.xml\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "bin";
	
	if (fileMustExist)
	{
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

		if(GetOpenFileName(&ofn))
		{
			result = szFileName;
		}
	}
	else
	{
		ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

		if (GetSaveFileName(&ofn))
		{
			result = szFileName;
		}
	}
}

//-------------------------------------------------------------------------------
void TWindowsFileSystem::GetFileList(const char* path, const char* extension, TDynamicSet<TString>& filenames)
{
	filenames.Clear();

	TString strFindParam = path;
	strFindParam += "/*.";
	strFindParam += extension;

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA findFileData;

	hFind = FindFirstFile(strFindParam.GetPointer(), &findFileData);

	char filename[1024];
    
	do
	{
        if (hFind != INVALID_HANDLE_VALUE)
        {
            // skip the /.. and /.
            if (TStringHelper::TStrLen(findFileData.cFileName) > 2)
            {
                sprintf_s(filename, 1024, "%s/%s", path, findFileData.cFileName);

                filenames.Add(filename);
            }
        }
        else
        {
            TDebugPrint(("[TWindowsFileSystem::GetFileList] Invalid folder: %s", path));
        }
	}
	while(FindNextFile(hFind, &findFileData));

	FindClose(hFind);
}

//-------------------------------------------------------------------------------
bool TWindowsFileSystem::FileExists(const char* filepath)
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA findFileData;
	
	hFind = FindFirstFile(filepath, &findFileData);

	bool found = hFind != INVALID_HANDLE_VALUE;

	if (found)
	{
		FindClose(hFind);
	}

	return found;
}