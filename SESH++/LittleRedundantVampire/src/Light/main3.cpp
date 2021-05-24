//#include <SFML/Audio.hpp>
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "Ray.h"
//#include "LightSource.h"
//#include "PointLight.h"
//#include "DirectionalLight.h"
//
//#include <stdlib.h>
//#include <time.h>
//using namespace sf;
//using namespace std;
//
//
//int main()
//{
//	CircleShape intersectCircle;
//	// Create the main window
//	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
//	vector<VertexArray> walls;
//
//	srand(time(NULL));
//
//	//Random walls
//	for (int i = 0; i < 5; i++)
//	{
//		int x1 = rand() % 600+ 1;
//		int y1 = rand() % 800 + 1;
//
//		int x2 = rand() % 600 + 1;
//		int y2 = rand() % 800 + 1;
//
//		VertexArray tmp = VertexArray(sf::LinesStrip, 2);
//		tmp[0].position = Vector2f(x1, y1);
//		tmp[0].color = Color::Red;
//		tmp[1].color = Color::Red;
//		tmp[1].position = Vector2f(x2, y2);
//
//		walls.push_back(tmp);
//	}
//
//
//	VertexArray tmp4 = VertexArray(sf::LinesStrip, 2);
//	tmp4[0].position = Vector2f(0, 0);
//	tmp4[0].color = Color::Red;
//	tmp4[1].color = Color::Red;
//	tmp4[1].position = Vector2f(800, 0);
//
//	walls.push_back(tmp4);
//
//	VertexArray tmp5 = VertexArray(sf::LinesStrip, 2);
//	tmp5[0].position = Vector2f(0, 595);
//	tmp5[0].color = Color::Red;
//	tmp5[1].color = Color::Red;
//	tmp5[1].position = Vector2f(800, 595);
//
//	walls.push_back(tmp5);
//
//
//	VertexArray tmp6 = VertexArray(sf::LinesStrip, 2);
//	tmp6[0].position = Vector2f(5, 0);
//	tmp6[0].color = Color::Red;
//	tmp6[1].color = Color::Red;
//	tmp6[1].position = Vector2f(5, 750);
//
//	walls.push_back(tmp6);
//
//	VertexArray tmp7 = VertexArray(sf::LinesStrip, 2);
//	tmp7[0].position = Vector2f(750, 0);
//	tmp7[0].color = Color::Red;
//	tmp7[1].color = Color::Red;
//	tmp7[1].position = Vector2f(750, 750);
//
//	walls.push_back(tmp7);
//	
//	Ray r1(Vector2f(250, 250), Vector2f(40, 0));
//	Ray r2(Vector2f(250, 260), Vector2f(40, 0));
//	Ray r3(Vector2f(250, 270), Vector2f(40, 0));
//	Ray r4(Vector2f(250, 280), Vector2f(40, 0));
//
//	DirectionalLight light(Vector2f(500, 250), Vector2f(500, 450),0,5);
//	//PointLight light(Vector2f(250, 250),&walls);
//
//	// Start the game loop
//	while (window.isOpen())
//	{
//		// Process events
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			// Close window: exit
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		// Clear screen
//
//		//r1.Cast(tmp4);
//		Color c(255, 255, 255);
//		window.clear(c);
//
//		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
//		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
//
//
//		vector<Ray*>::iterator it;
//		//light.Move(worldPos);
//		vector<Vector2f> vray = light.CastRays(&walls);
//
//		vector<Vector2f>::iterator vrayIt;
//
//		ConvexShape lightCone;
//		lightCone.setFillColor(Color::Yellow);
//		lightCone.setPointCount(vray.size());
//
//		//A list of triangles, because sfml cant draw concave shapes
//		vector<VertexArray> lightCone2 = light.GetLightCone();
//		
//		vector<VertexArray>::iterator triIt;
//
//		for (triIt = lightCone2.begin(); triIt < lightCone2.end(); triIt++)
//		{
//			window.draw(*triIt);
//		}
//
//		vector<VertexArray> FUCKINGLORT = light.GetRayLines();
//		vector<VertexArray>::iterator itttt;
//
//		for (itttt = FUCKINGLORT.begin(); itttt < FUCKINGLORT.end(); itttt++)
//		{
//			window.draw(*itttt);
//		}
//
//		vector<VertexArray>::iterator It;
//
//		for (It = walls.begin(); It < walls.end(); It++)
//		{
//			window.draw(*It);
//		}
//
//
//		// Update the window
//		window.display();
//	}
//	return EXIT_SUCCESS;
//}
//
//TODO: The heck is this?!
