#include <iostream>
#include <SFML/graphics.hpp>
#include "Animation.h"
#include "Player.h"
using namespace sf;
using namespace std;

static const float VIEW_HEIGHT = 1024.0f;


/// <summary>
/// https://www.youtube.com/watch?v=CpVbMeYryKo&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=13
/// Sørger for at det view scaler med vinduets størrelse. Forhindrer stretching af sprites og lignende.
/// </summary>
/// <param name="window">Spilvinduet.</param>
/// <param name="view">Det view som følger spilleren.</param>
void RezizeView(const RenderWindow& window, View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


int main()
{
    RenderWindow window(sf::VideoMode(1024, 1024), "SFML works!");
    View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));


    //Her loader vi en texture til player.
    Texture playerTexture;
    playerTexture.loadFromFile("OzzySheet.png");

    //Vi implementerer vores Animation-klasse, så vi kan animere vores player.
    Player player(&playerTexture, Vector2u(4, 3), 0.13f, 300.0f);

    //Vores deltaTime er den tid der er gået siden sidste update.
    float deltaTime = 0.0f;
    //Vi skal bruge clock til at regne ud hvor lang tid der er gået.
    Clock clock;


    while (window.isOpen())
    {
        //Vi sætter vores deltaTime i forhold til clock.
        deltaTime = clock.restart().asSeconds();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::Resized)
                RezizeView(window, view);
        }

        //Hvert gameloop kører vi Update på vores animation.
        //Vi kører animationen for række 0 (1).
        player.Update(deltaTime); 
        view.setCenter(player.GetPosition());

        window.clear(Color(255, 255, 255, 255));
        window.setView(view);
        player.Draw(window);
        window.display();
    }

    return 0;
}


//Ektrea kode:
//Vi behøver ikke delen herunder når vi bruger Animation-klassen.
// 
//Vi skal have størrelsen på vores texture (png-fil).
//Vector2u textureSize = playerTexture.getSize();

////Vores png-fil er et sprite sheet. Her definerer vi mængden af sprites (kolonner og rækker).
////Der er 6 sprites på x-aksen og kun 1 række af sprites (y-aksen).
//textureSize.x /= 6;
//textureSize.y /= 1;

////Nu bestemmer vi hvilken af de 6 sprites vi vil tegne som vores player.
////De første 2 variabler i IntRect definerer hvor vores sprite ligger på x- og y-aksen.
////Den sprite du ønsker skal der trækkes -1 fra. 
////Så hvis du vil have sprite 1 på række 1, skal du skrive (textureSize.x* 0, textureSize.y* 0).
////Så hvis du vil have sprite 6 på række 1, skal du skrive (textureSize.x* 5, textureSize.y* 0).
//player.setTextureRect(IntRect(textureSize.x * 1, textureSize.y * 0, textureSize.x, textureSize.y));