#include <iostream>
#include <cstdio>
#include <cstdlib>
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

void drawGrid(World& data) {
	for (size_t i = 0; i < 40; i++)
	{
		for (size_t j = 0; j < 21; j++)
		{
			RectangleShape* grid = new RectangleShape(Vector2f(32, 32));
			grid->setOrigin(1, 1);
			grid->setFillColor(Color(0,0,0,0));
			grid->setOutlineThickness(1);
			grid->setOutlineColor(Color(150,150,150,150));
			grid->setPosition(Vector2f(i * 32, j * 32));
			data.grid.push_back(grid);
		}
		
	}
}


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
	World::player = new Entity(heroSprite, 15, 15);
	

	


	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();


	bool mouseLeftWasPressed = false;
	bool hasJumped = false;
	//bool enterWasPressed = false;
	World data;
	data.objects.push_back(World::player);
	drawGrid(data);
	World::dij.init(Vector2i(World::player->cx, World::player->cy));
	//----------------------------------------  IMGUI STUFF  -------------------------------------------------------------
	float bgCol[3] = { 0,0,0 };
	Clock clock;
	int click = 0;
	while (window.isOpen()) {
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp(); //calculer le temps entre chaque frame pour les vitesses
		bool shifIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);//Intégration IMGUI

			if (event.type == sf::Event::MouseButtonPressed) {

				if (shifIsPressed) {
					auto cx = event.mouseButton.x / Entity::stride;
					auto cy = event.mouseButton.y / Entity::stride;

					auto& p = World::currentPath;
					World::currentPath.clear();
					sf::Vector2i start = sf::Vector2i(World::player->cx, World::player->cy);
					sf::Vector2i end = sf::Vector2i(cx, cy);

					sf::Vector2i cur = end;
					World::currentPath.push_back(end);
					while (cur != start) {
						auto pos = World::dij.pred.find(cur);
						if (pos != World::dij.pred.end()) {
							cur = World::dij.pred[cur];
							World::currentPath.push_back(cur);
						}
						else {
							World::currentPath.clear();
							break;
						}
					}
					std::reverse(p.begin(), p.end());
					World::player->curPath = p;
				}
				else {
					auto cx = event.mouseButton.x / Entity::stride;
					auto cy = event.mouseButton.y / Entity::stride;

					int pos = -1;
					int idx = 0;
					for (auto& v : World::walls) {
						if (v.x == cx && v.y == cy)
							pos = idx;
						idx++;
					}

					if (pos < 0)
						World::walls.push_back(sf::Vector2i(cx, cy));
					else
						World::walls.erase(World::walls.begin() + pos);
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Enter) {
					World::dij.compute(sf::Vector2i(World::player->cx, World::player->cy));
				}
			}
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

		

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !hasJumped && player->isGrounded) {
			player->dy -= 30;
			hasJumped = true;
			player->isGrounded = false;
		}
		else
			hasJumped = false;*/


		
		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);
		



		if (mouseLeftIsPressed)
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;

		auto player = World::player;

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