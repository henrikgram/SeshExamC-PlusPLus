#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ray.h"
#include "LightSource.h"

#include <stdlib.h>
#include <time.h>
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

	vector<VertexArray> walls[5];

	srand(time(NULL));

	for (int i = 0; i < 5; i++)
	{
		int x1 = rand() % 600+ 1;
		int y1 = rand() % 800 + 1;

		int x2 = rand() % 600 + 1;
		int y2 = rand() % 800 + 1;

		VertexArray tmp = VertexArray(sf::LinesStrip, 2);
		tmp[0].position = Vector2f(x1, y1);
		tmp[1].position = Vector2f(x2, y2);

		walls->push_back(tmp);
	}

	LightSource light(Vector2f(250,250));
	
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

		//ray.LookAt(worldPos);

		//light.Move(worldPos);

		window.draw(box);
		//window.draw(*ray.GetVertexArray());

		vector<Ray*>::iterator it;

		vector<Vector2f> vray = light.Look(walls);

		vector<Vector2f>::iterator vrayIt;

		for (vrayIt = vray.begin(); vrayIt < vray.end(); vrayIt++)
		{
			VertexArray tmp = VertexArray(sf::LinesStrip, 2);
			tmp[0].position = light.GetPosition();
			tmp[1].position = *vrayIt;
			window.draw(tmp);
		}

		vector<VertexArray>::iterator It;

		for (It = walls->begin(); It < walls->end(); It++)
		{
			window.draw(*It);
		}


		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}

