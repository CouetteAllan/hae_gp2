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
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

#include "imgui.h"
#include "imgui-SFML.h"

int main()
{
	float wHeight = 720;
	float wWidth = 1280;
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Tortue du turfu");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(144);

	ImGui::SFML::Init(window);

	

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();


	//bool mouseLeftWasPressed = false;
	//bool enterWasPressed = false;


	//----------------------------------------  IMGUI STUFF  -------------------------------------------------------------
	float bgCol[3] = { 0,0,150 };
	Clock clock;
	while (window.isOpen()) {
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp(); //calculer le temps entre chaque frame pour les vitesses
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);//Intégration IMGUI
			switch (event.type)
			{

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;

			default:
				break;
			}
		}
		float deltaX = dt * 360;
		float deltaY = dt * 360;
		bool keyHit = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		}


		/*
		//bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		//bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);
		//sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
		//bool enterIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
		//bool enterIsReleased = (!enterIsPressed && enterWasPressed);
		*/
		ImGui::SFML::Update(window, clock.restart());

		
		ImGui::Begin("Background");
		ImGui::ColorEdit3("Background Color", bgCol);
			
		ImGui::End();

		//ImGui::ShowDemoWindow(&activeTool);

		////////////////////
		//CLEAR
		window.clear(Color(
			bgCol[0] * 255,
			bgCol[1] * 255,
			bgCol[2] * 255
		));

		////////////////////
		//UPDATE

		////////////////////
		//DRAW
		//game elems



		//ui

		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();
	}
	ImGui::SFML::Shutdown();

	return 0;
}