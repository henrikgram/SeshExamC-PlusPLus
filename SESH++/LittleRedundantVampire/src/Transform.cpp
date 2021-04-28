#include "Headers/Transform.h"

void Transform::Translate(Vector2<float> * translation)
{
    //if (!float.IsNaN(translation.X) /*&& !Vector2<float>.IsNaN(translation.Y)*/)
    //{
    //    Position += translation;
    //}
    // 
    // TODO: Check if this is a good enough way to assure there will be no null exceptions (Look at above code from C# project).
    if (translation != nullptr)
    {
        kylling += *translation;
    }
}
