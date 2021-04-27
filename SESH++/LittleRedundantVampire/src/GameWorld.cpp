#include <iostream>
#include <vector>
#include <SFML/graphics.hpp>
#include "Headers/Components/SpriteRenderer.h"
#include "Headers/GameObject.h"
#include "Headers/Asset.h"
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(800, 800), "Little Redundant Vampire 2.0");
//GameObject gameObject; 

//TODO: check if heap or stack
vector<GameObject> gameObjects;
vector<GameObject>::iterator it;

Asset asset;

void Initialize()
{
    //Texture* texture = new Texture;

    //texture = asset.GetTexture(TextureTag::Ozzy);

    //GameObject gameObject = GameObject(texture);

    //gameObjects.push_back(gameObject);

    GameObject go = GameObject();
    SpriteRenderer * sr = new SpriteRenderer();
    go.AddComponent(sr);
    gameObjects.push_back(go);
}

void LoadContent()
{  
    Asset::GetInstance()->LoadTextures();
    (SpriteRenderer)(gameObjects[0].GetComponent(Tag::SPRITERENDERER)).GetSprite();
}

// TODO: Pointer fix. Check if it works correctly. Check if double pointers necessary
void Update(Time * timePerFrame)
{
    //iterates through the gameObjects and calls update
    for (it = gameObjects.begin(); it < gameObjects.end(); it++)
    {
        it->Update(timePerFrame);
    }

}


/// <summary>
/// Method for drawing all sprites into the game.
/// </summary>
/// <param name="sprite"></param>
void Draw()
{
    // Clears the window.
    window.clear();
    // Draws the sprite(s).

      //iterates through the gameObjects and calls update
    for (it = gameObjects.begin(); it < gameObjects.end(); it++)
    {
        window.draw(it->GetSprite());
    }
   
    // Displays everything in the window.
    window.display();
}

/// <summary>
/// Everything is run from here.
/// </summary>
/// <returns></returns>
int main()
{
    LoadContent();
    Initialize();


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
            //sprite.move(Vector2f(0, 0.1f * timePerFrame.asMilliseconds()));
            Update(&timePerFrame);
        }   

        //TODO: sprite er en kopi, fix, pointer.
        Draw();
    }

    return 0;
}