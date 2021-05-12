#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ray.h"
#include "LightSource.h"
using namespace sf;
using namespace std;


int main()
{
	CircleShape intersectCircle;
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	VertexArray box = VertexArray(sf::LinesStrip, 2);

	box[0].position.x = 500;
	box[0].position.y = 500;

	box[1].position.x = 500;
	box[1].position.y = 100;


	//LightSource light(Vector2f(250,250));
	Ray ray(Vector2f(250, 250), Vector2f(50, 0));

	//cout << ray.Cast(box);

	//if (ray.Cast(box))
	//{
	//	intersectCircle.setPosition(*ray.GetIntersectionPoint());
	//	intersectCircle.setOrigin(10, 10);
	//	intersectCircle.setRadius(10);
	//	intersectCircle.setFillColor(Color::Red);
	//}

	  // Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Clear screen
		window.clear();

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

		ray.LookAt(worldPos);

		window.draw(box);
		window.draw(*ray.GetVertexArray());

		if (ray.Cast(box))
		{
			intersectCircle.setPosition(*ray.GetIntersectionPoint());
			intersectCircle.setOrigin(10, 10);
			intersectCircle.setRadius(10);
			intersectCircle.setFillColor(Color::Red);	
			window.draw(intersectCircle);
		}
	
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}

