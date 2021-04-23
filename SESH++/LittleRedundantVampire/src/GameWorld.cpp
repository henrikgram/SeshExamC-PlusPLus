#include <iostream>
#include <SFML/graphics.hpp>
#include "Header/GameObject.h"
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(800, 800), "Little Redundant Vampire 2.0");
GameObject gameObject;

void LoadContent();

void Update(Time timePerFrame)
{
    gameObject.Update(timePerFrame);
}

void Initialize()
{

}

/// <summary>
/// Method for drawing all sprites into the game.
/// </summary>
/// <param name="sprite"></param>
void Draw(Sprite sprite)
{
    // Clears the window.
    window.clear();
    // Draws the sprite(s).
    window.draw(sprite);
    // Displays everything in the window.
    window.display();
}

/// <summary>
/// Everything is run from here.
/// </summary>
/// <returns></returns>
int main()
{
    Sprite sprite;
    Texture texture;
    texture.loadFromFile("Asset_2/VampireOzzyStill.png");
    sprite.setTexture(texture);

    // Used for fixed update. TimePerFrame needs to be set to the amount of frames you want it to run with.
    Time timePerFrame = seconds(1.f / 60.f);
    Clock deltaClock;
    Time timeSinceLastUpdate = Time::Zero;

    while (window.isOpen())
    {
        // Shuts the game down when the window is closed.
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // For fixed update and 60 frames per second.
        // Clock is restarted to make sure we start from 0 every time.      
        timeSinceLastUpdate += deltaClock.restart();
        // Once we reach 60 frames, we reset timeSinceLastUpdate, run Update(), and move the character.
        // This is to make sure the character movement speed never changes.

        //When the timesincelastUpdate is over the required amount, it runs the update, and subtracts the desired time pr frame.
        //it keeps updating until, its below the required amount, means the update is "up to date" with the game logic.
        //When it's up to date it will draw/render and refresh the display. This results in the update dosen't get behind.
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            sprite.move(Vector2f(0, 0.1f * timePerFrame.asMilliseconds()));
            Update(timePerFrame);
        }   

        //TODO: sprite er en kopi, fix, pointer.
        Draw(sprite);
    }

    return 0;
}