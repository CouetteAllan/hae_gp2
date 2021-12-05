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
#include "World.hpp"
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

#include "imgui.h"
#include "imgui-SFML.h"

using namespace ImGui;

int main()
{
	float wHeight = 720;
	float wWidth = 1280;
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Moteur à Case");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(144);

	ImGui::SFML::Init(window);



	RectangleShape* heroSprite = new RectangleShape(Vector2f(15,35));
	heroSprite->setFillColor(Color::Red);
	heroSprite->setOrigin(heroSprite->getSize().x / 2, heroSprite->getSize().y);
	Entity* player = new Entity(heroSprite, 15, 15);
	

	


	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();


	bool mouseLeftWasPressed = false;
	bool hasJumped = false;
	//bool enterWasPressed = false;
	World data;
	data.objects.push_back(player);
	//----------------------------------------  IMGUI STUFF  -------------------------------------------------------------
	float bgCol[3] = { 0,0,0 };
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

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			player->dy -= 10;
			player->isGrounded = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player->dy += 1;
		}*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player->dx += 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			player->dx -= 2;

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !hasJumped && player->isGrounded) {
			player->dy -= 50;
			hasJumped = true;
		}
		else
			hasJumped = false;


		
		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);
		

		if (mouseLeftIsPressed && !mouseLeftWasPressed) {
			Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
			RectangleShape* wallShape = new RectangleShape(Vector2f(player->stride, player->stride));
			wallShape->setFillColor(Color::Blue);
			Entity* wall = new Entity(wallShape, mousePos.x/player->stride, mousePos.y / player->stride, Wall);
			data.objects.push_back(wall);
			//Faire apparaître un mur au niveau du clic

		}



		if (mouseLeftIsPressed)
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;

		ImGui::SFML::Update(window, clock.restart());

		
			

		Begin("Coordonates");
		static bool modified;
		modified = SliderInt("CX", &player->cx, 0.0f, wWidth / player->stride);
		modified = SliderInt("CY", &player->cy, 0.0f, wHeight / player->stride - 2);
		modified = SliderFloat("RX", &player->rx, 0.0f, 1.0f);
		modified = SliderFloat("RY", &player->ry, 0.0f, 1.0f);
		modified = Checkbox("Enable Gravity", &player->gravity);

		Value("Coord X", player->sprite->getPosition().x);
		Value("Coord Y", player->sprite->getPosition().y);
		Value("Speed X", player->dx);
		Value("Speed Y", player->dy);
		Value("IsGrounded", player->isGrounded);

		SliderFloat("Friction", &player->friction, 0.0f, 1.0f);
		if (modified)
			player->syncSprite();
		End();

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
		data.update(dt);
		////////////////////
		//DRAW
		data.draw(window);
		//game elems



		//ui

		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();
	}
	ImGui::SFML::Shutdown();

	return 0;
}