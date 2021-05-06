#include "GameWorld.h"

/// <summary>
/// Everything is run from here.
/// </summary>
/// <returns></returns>
int main()
{
	while (true)
	{
		GameWorld::GetInstance()->Run();
	}
}
