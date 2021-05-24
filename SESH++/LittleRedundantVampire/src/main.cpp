#include "GameWorld.h"

/// <summary>
/// Everything is run from here.
/// </summary>
/// <returns>the exit code //TODO: is this correct?</returns>
int main()
{
	GameWorld::GetInstance()->Run();
}
