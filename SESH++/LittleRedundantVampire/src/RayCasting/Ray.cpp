#include "Ray.h"

Ray::Ray(Vector2f position, Vector2f direction)
{
    this->direction = direction;
    this->position = position;

    (*ray)[0].color = Color::Black;
    (*ray)[1].color = Color::Black;

    (*ray)[0].position = position;
    (*ray)[1].position = Vector2f((position.x + direction.x),position.y+direction.y);
}


Ray::Ray()
{
}

Ray::~Ray()
{
    delete ray;
    ray = nullptr;

   /* delete intersection;
    intersection = nullptr;*/
}

bool Ray::Cast(VertexArray& wall)
{
    //Uses the folowing formula from wikipedia.
    //https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection

    //All values are saved as x1x2 etc.. to make it easier to follow the formula.
    float x1 = (wall)[0].position.x;
    float y1 = (wall)[0].position.y;

    float x2 = (wall)[1].position.x;
    float y2 = (wall)[1].position.y;

    float x3 = (*ray)[0].position.x;
    float y3 = (*ray)[0].position.y;

    float x4 = (*ray)[1].position.x;
    float y4 = (*ray)[1].position.y;

    float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    //If the deniminator is 0, it meaans that the lines are parallel and will never collide. 
    if (denominator == 0)
    {
        return false;
    }
  
    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;

    //if there is intersection point return true
    //"The intersection point falls within the first line segment if 0.0 ≤ t ≤ 1.0,"
    //The reason u is only check for > 0 is that they ray is thought of an endless line. 
    //and it only needs to check if it intersects with t eventually, and not only between the to given points. 
    if (t > 0 && t < 1 && u > 0)
    {
        intersection.x = x1 + t * (x2 - x1);
        intersection.y = y1 + t * (y2 - y1);

        return true;
    }
    else
    {
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

Vector2f Ray::GetIntersectionPoint()
{
    return intersection;
}

Vector2f Ray::GetPosition()
{
    return position;
}

void Ray::SetIntersection(Vector2f position)
{
    intersection = position;
}

void Ray::Move(Vector2f position)
{
    (*ray)[0].position = position;
    (*ray)[1].position = Vector2f(position.x + direction.x, position.y + direction.y);
}


