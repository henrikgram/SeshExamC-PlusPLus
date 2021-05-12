#include "Ray.h"

Ray::Ray(Vector2f position, Vector2f direction)
{
    (*ray)[0].position = position;
    (*ray)[1].position = Vector2f((position.x + direction.x),position.y+direction.y);
}

Ray::Ray()
{
}

bool Ray::Cast(VertexArray& wall)
{
    float x1 = (wall)[0].position.x;
    float y1 = (wall)[0].position.y;

    float x2 = (wall)[1].position.x;
    float y2 = (wall)[1].position.y;

    float x3 = (*ray)[0].position.x;
    float y3 = (*ray)[0].position.y;

    float x4 = (*ray)[1].position.x;
    float y4 = (*ray)[1].position.y;

    float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    //If lines are parallel they will never collide. 
    if (denominator == 0)
    {
        return false;
    }

    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;

    //if there is intersection point return true
    if (t > 0 && t < 1 && u > 0)
    {
        //cout << "intersect!!!";

        intersection->x = x1 + t * (x2 - x1);
        intersection->y = y1 + t * (y2 - y1);


        return true;
    }
    else
    {
       // cout << "No :(";
        return false;
    }
}

void Ray::LookAt(Vector2f position)
{
    (*ray)[1].position = position;
}


VertexArray* Ray::GetVertexArray()
{
    return ray;
}

Vector2f* Ray::GetIntersectionPoint()
{
    return intersection;
}
