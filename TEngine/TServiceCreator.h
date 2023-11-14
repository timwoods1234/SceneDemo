#ifndef __TSERVICECREATOR_H__
#define __TSERVICECREATOR_H__

class TServiceCreator
{
public:
	static void CreateServices();

	static void DestroyServices();

private:
	static void CreatePlatformServices();
	static void CreatePlatformDependentServices();
	static void CreatePlatformIndependentServices();

	static void DestroyPlatformServices();
	static void DestroyPlatformDependentServices();
	static void DestroyPlatformIndependentServices();
};

#endif
