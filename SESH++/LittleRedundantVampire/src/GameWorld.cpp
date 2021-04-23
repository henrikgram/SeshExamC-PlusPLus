#include <iostream>
#include <SFML/graphics.hpp>
using namespace std;
using namespace sf;

void LoadContent();
void Update(Time deltaTime);
void Initialize()
{

}
void Draw(Time deltaTime);

int main()
{
//counting all the assholes in the room
    RenderWindow window(VideoMode(800, 800), "Little Redundant Vampire 2.0");

    Sprite sprite;
    Texture texture;
    texture.loadFromFile("Asset_2/VampireOzzyStill.png");
    sprite.setTexture(texture);

    // Used for fixed update.
    Time timePerFrame = seconds(1.f / 60.f);
    Clock deltaClock;
    Time timeSinceLastUpdate = Time::Zero;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        //Time elapsedTime = deltaClock.restart();
        // For fixed update and 60 frames per second.
        timeSinceLastUpdate += deltaClock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            sprite.move(Vector2f(0, 0.1f * timePerFrame.asMilliseconds()));
            //Update(timePerFrame);
            //Draw(timePerFrame);
        }  
        //deltaClock.restart().asMilliseconds();
        


        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}