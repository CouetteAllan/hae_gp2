
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Tool.hpp"
#include <algorithm>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include "Entity.hpp"
#include "Turtle.hpp"




int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Tortue du turfu");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(144);

	sf::Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))	
		cout << "font not loaded" << endl;
	sf::Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(sf::Color::White);
	tDt.setCharacterSize(45);

	

	

	Turtle turtle;


	turtle.trs.translate(500, 500);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	bool mouseLeftWasPressed = false;

	Command* advance = nullptr;
	Command* moveBack = nullptr;

	while (window.isOpen()){
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		while (window.pollEvent(event)){
			switch (event.type)
			{
				// fenêtre fermée
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();

				if (event.key.code == sf::Keyboard::E)
					turtle.isDrawing = !turtle.isDrawing;

				if (event.key.code == sf::Keyboard::A)
					turtle.isDrawing = !turtle.isDrawing;
				break;
				
			default:
				break;
			}
		}
		//auto pos = turtle->getPosition();
		float deltaX = dt * 360;
		float deltaY = dt * 360;
		bool keyHit = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			turtle.trs.translate(0, -7 * dt * 60);
//			turtle.appendCmd(advance);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			turtle.trs.translate(0, 7 * dt * 60);
	//		turtle.appendCmd(moveBack);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			turtle.trs.rotate(5 * dt * 60);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			turtle.trs.rotate(-5 * dt * 60);
		}


		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			
		}

		if (mouseLeftIsPressed) 
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;


		float radToDeg = 57.2958;
		//float angleC2M = /*atan2()*/;

		tDt.setString( to_string(dt)+" FPS:"+ to_string((int)(1.0f / dt)));
		
		
		////////////////////

		//CLEAR
		window.clear();
		
		////////////////////
		//UPDATE
		turtle.update(dt);

		////////////////////
		//DRAW

		turtle.draw(window);

		//game elems

		

		//ui
		if(turtle.isDrawing)
			window.draw(tDt);
		window.display();
		tExitFrame = getTimeStamp();
	}

	return 0;
}