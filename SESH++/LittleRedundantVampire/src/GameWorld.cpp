#include <iostream>
#include <vector>
#include <SFML/graphics.hpp>

#include "Headers/Components/SpriteRenderer.h"
#include "Headers/GameObject.h"
#include "Headers/Asset.h"
#include "Enum/ObjectTag.h"
#include "Headers/Components/Player.h"
#include "Headers/Platform.h"
#include "Headers/LevelManager.h"
#include "Headers/Components/NPC.h"

using namespace std;
using namespace sf;
static const float VIEW_HEIGHT = 1024.0f;

RenderWindow window(VideoMode(800, 800), "Little Redundant Vampire 2.0");
View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

//TODO: check if heap or stack
vector<GameObject> * gameObjects = new vector<GameObject>;
vector<GameObject>::iterator it;

bool textBoxOpen = false;

/// <summary>
/// https://www.youtube.com/watch?v=CpVbMeYryKo&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=13
/// S�rger for at det view scaler med vinduets st�rrelse. Forhindrer stretching af sprites og lignende.
/// </summary>
/// <param name="window">Spilvinduet.</param>
/// <param name="view">Det view som f�lger spilleren.</param>
void ResizeView(const RenderWindow& window, View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

//TODO: check if this is fine, or actual factory is needed
void BootlegFactory(ObjectTag tag)
{
    //TODO: tjek hvis den ryger ud af scope.
    GameObject * go = new GameObject();
    SpriteRenderer* sr = new SpriteRenderer();
    //Collider* colider = new Collider();

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
        sr->SetSprite(TextureTag::NPC);
        go->position = new Vector2<float>(150, 100);
        go->AddComponent(sr);
        break;
    case ObjectTag::WALL:
        sr->SetSprite(TextureTag::WALL);
        go->AddComponent(sr);
        go->position = new Vector2<float>(1, 1);
        *go->objectTag = ObjectTag::WALL;
        break;
    case ObjectTag::DOOR:
        sr->SetSprite(TextureTag::DOOR);
        go->AddComponent(sr);
        *go->objectTag = ObjectTag::DOOR;
        break;
    case ObjectTag::FLOOR:
        sr->SetSprite(TextureTag::FLOOR);
        go->AddComponent(sr);
        *go->objectTag = ObjectTag::FLOOR;
        break;
    case ObjectTag::BOOKCASE:
        sr->SetSprite(TextureTag::BOOKCASE);
        go->AddComponent(sr);
        *go->objectTag = ObjectTag::BOOKCASE;
        break;
    case ObjectTag::VASE:
        sr->SetSprite(TextureTag::VASE);
        go->AddComponent(sr);
        *go->objectTag = ObjectTag::VASE;
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
    BootlegFactory(ObjectTag::WALL);
    BootlegFactory(ObjectTag::NPC);
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
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    LevelManager lm;

    lm.InstantiateLevel();

    LoadContent();
    Initialize();

    //Her loader vi en texture til player.

    //Vi implementerer vores Animation-klasse, s� vi kan animere vores player.
    Player player(Asset::GetInstance()->GetTexture(TextureTag::OZZYSHEET),/* &attackTexture, */ Vector2u(4, 3), 0.13f, 5.0f);

    Platform p1(nullptr, Vector2f(100, 100), Vector2f(500.0f, 500.0f));

    //Vores deltaTime er den tid der er g�et siden sidste update.
    float deltaTime = 0.0f;
    //Vi skal bruge clock til at regne ud hvor lang tid der er g�et.
    Clock clock;


    // Used for fixed update. TimePerFrame needs to be set to the amount of frames you want it to run with.
    Time timePerFrame = seconds(1.f / 60.f);
    Clock deltaClock;
    Time timeSinceLastUpdate = Time::Zero;

    while (window.isOpen())
    {
        //Vi s�tter vores deltaTime i forhold til clock.
        deltaTime = clock.restart().asSeconds();
        // Shuts the game down when the window is closed.
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::Resized)
                ResizeView(window, view);
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
            player.Update(deltaTime);
            p1.GetCollider().CheckCollision(player.GetCollider(), 0.1f);
            view.setCenter(player.GetPosition());
        }   

        //Hvert gameloop korer vi Update paa vores animation.
       //Vi korer animationen for raekke 0 (1).
        NPC* npc = new NPC();
        //GameObject* npc = new GameObject();
        SpriteRenderer* npcSr = new SpriteRenderer();
        npcSr->SetSprite(TextureTag::NPC);
        npc->position = new Vector2<float>(150, 100);
        npc->AddComponent(npcSr);
        GameObject npcGo = npc->TextBoxPopup();
        //window.setView(view);

        Draw();
        //window.clear(Color(0, 0, 0, 0));
        if (Keyboard::isKeyPressed(Keyboard::F) && !textBoxOpen)
        {
            
            gameObjects->push_back(npcGo);
            textBoxOpen = true;
        }
        //// YOU ARE HERE
        //else if (Keyboard::isKeyPressed(Keyboard::F) && textBoxOpen)
        //{
        //    for (it = gameObjects->begin(); it < gameObjects->end(); it++)
        //    {
        //        if (*it->objectTag == ObjectTag::NPC)
        //        {
        //            gameObjects->pop_back();
        //        }
        //    }
        //    //gameObjects->pop_back();
        //    //npc->TextBoxRemoval();
        //    textBoxOpen = false;
        //}
        //window.clear();
        //player.Draw(window);
        //p1.Draw(window);
        //window.display();
    }

    return 0;
}