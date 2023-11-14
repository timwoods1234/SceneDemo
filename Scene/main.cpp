#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "TEngine.lib")

// Memory Management
#if defined(DEBUG) | defined(_DEBUG)
#	define _CRTDBG_MAP_ALLOC
#	include <stdlib.h>
#	include <crtdbg.h>
#	include <memory>
#endif

#include "TEngine.h"
#include "TWindowsApplication.h"
#include "Game.h"

//-------------------------------------------------------------------------------
TWindowsApplication* windowsApp = NULL;
Game* game = NULL;

//-------------------------------------------------------------------------------
void CheckMemoryLeaks()
{
	int heapAllocations, poolAllocations, heapedBytes, pooledBytes;

	TMemoryManager::GetSummary(heapAllocations, heapedBytes, poolAllocations, pooledBytes);

	if (heapAllocations > 0 || poolAllocations > 0)
	{
		TTextStream fileStream;
		fileStream.OpenWrite("MemLeakDump.txt");

		TMemoryManager::PrintAllocations(&fileStream);
		fileStream.Close();

		MessageBox(0, "Memory leaks were detected, see MemLeakDump.txt for details", "Leaks!", MB_OK | MB_ICONSTOP);
	}
}

//-------------------------------------------------------------------------------
void Init(HINSTANCE instance)
{
	TMemoryManager::Initialize();

	windowsApp = TNew TWindowsApplication(instance, "Game Window");

	game = TNew Game();
}

//-------------------------------------------------------------------------------
void Shutdown()
{
	TSafeDelete(game);

	TSafeDelete(windowsApp);

	CheckMemoryLeaks();
	TMemoryManager::ShutDown();
}

//-------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
#if defined(DEBUG) | defined(_DEBUG)
	// Enable run-time memory check for debug builds.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(317);
#endif

	Init(instance);

	windowsApp->Run();

	Shutdown();

	return 0;
}
