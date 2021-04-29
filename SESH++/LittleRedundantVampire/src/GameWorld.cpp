#include <iostream>
#include <vector>
#include <SFML/graphics.hpp>

#include "Headers/Components/SpriteRenderer.h"
#include "Headers/GameObject.h"
#include "Headers/Asset.h"
#include "Enum/ObjectTag.h"

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(800, 800), "Little Redundant Vampire 2.0");

//TODO: check if heap or stack
vector<GameObject> * gameObjects = new vector<GameObject>;
vector<GameObject>::iterator it;

//TODO: check if this is fine, or actual factory is needed
void BootlegFactory(ObjectTag tag)
{
    //TODO: tjek hvis den ryger ud af scope.
    GameObject * go = new GameObject();
    SpriteRenderer* sr = new SpriteRenderer();

    switch (tag)
    {
    case ObjectTag::PLAYER:
        sr->SetSprite(TextureTag::OZZY);
        go->position = new Vector2<float>(200, 1);
        go->AddComponent(sr);
        break;
    case ObjectTag::ENEMY:
        break;
    case ObjectTag::NPC:
        break;
    case ObjectTag::WALL:
        break;
    case ObjectTag::DOOR:
        break;
    case ObjectTag::FLOOR:
        break;
    case ObjectTag::BOOKCASE:
        break;
    case ObjectTag::VASE:
        break;
    case ObjectTag::WINDOW:
        break;
    case ObjectTag::CRATE:
        break;
    default:
        break;
    }

    go->Awake();
    go->Start();

    gameObjects->push_back(*go);
}

void LoadContent()
{  
    Asset::GetInstance()->LoadTextures();
}

void Initialize()
{
    BootlegFactory(ObjectTag::PLAYER);
}

// TODO: Pointer fix. Check if it works correctly. Check if double pointers necessary

/// <summary>
/// Update loop for all gameobjects
/// </summary>
/// <param name="timePerFrame"></param>
void Update(Time * timePerFrame)
{
    //iterates through the gameObjects and calls update
    for (it = gameObjects->begin(); it < gameObjects->end(); it++)
    {
        it->Update(timePerFrame);
    }
}

/// <summary>
/// Method for drawing all sprites into the game.
/// </summary>
void Draw()
{
    // Clears the window.
    window.clear();

    //it needs to point to something, otherwise it wont compile, because it cant delete an "empty pointer"
    //TODO: this needs to be deleted somewhere, but it dosen't work here, actually, check if it matters because its on stack.
    SpriteRenderer* sr;

    //iterates through the gameObjects and draws all gameobjects.
    for (it = gameObjects->begin(); it < gameObjects->end(); it++)
    {
        //TODO: downcasting is considered bad practice and dynamic casting is slow, check this for performance issues.
        sr = dynamic_cast<SpriteRenderer*>(it->GetComponent(ComponentTag::SPRITERENDERER));

        window.draw(sr->GetSprite());
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
        //it keeps updating until it's below the required amount, means the update is "up to date" with the game logic.
        //When it's up to date it will draw/render and refresh the display. This results in the update dosen't get behind.
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            Update(&timePerFrame);
        }   

        Draw();
    }

    return 0;
}