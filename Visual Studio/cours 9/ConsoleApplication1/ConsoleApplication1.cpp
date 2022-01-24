#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iosfwd>
#include <iostream>

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
#include "HotReloadShader.hpp"

#include "imgui.h"
#include "imgui-SFML.h"


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


sf::Shader g_MainShaderNoTex;
sf::Shader g_MainShaderTex;

HotReloadShader g_bgShader;

bool loadFile(const char* path, std::string& res) {
	FILE* f = 0;
	fopen_s(&f, path, "r");
	if (!f)
		return false;
	fseek(f, 0L, SEEK_END);
	size_t sz = ftell(f);
	res.resize(sz);
	fseek(f, 0L, SEEK_SET);
	size_t read = fread(res.data(), sz, 1, f);
	if (f)
		fclose(f);
	else
		return false;
	return true;
}

int main()
{
	float wHeight = 720;
	float wWidth = 1280;
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Moteur à Case");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(144);

	ImGui::SFML::Init(window);

	if (!sf::Shader::isAvailable())
	{
		// les shaders ne sont pas dispo...
		printf("shader pas dispo");
	}
	std::string vertContent;
	std::string fragContent;
	bool vertOK = loadFile("res/shader_exo.vert", vertContent);
	bool fragOK = loadFile("res/shader_exo.frag",fragContent);

	if (!vertOK) {
		printf("can't load vert");
	}


	//fragContent = "#define HAS_UNIFORM_COLOR\\n" + fragContent;

	{
		if (!g_MainShaderTex.loadFromMemory(vertContent.c_str(), (std::string("#define HAS_TEXTURE \\n") + fragContent).c_str())) {
			cout << "cannot load shaders with tex\n";
			return 1;
		}
	}
	{
		if (!g_MainShaderNoTex.loadFromMemory(vertContent.c_str(), fragContent.c_str())) {
			cout << "cannot load shaders without tex\n";
			return 1;
		}
	}



	g_bgShader.vtxPath = "res/bg.vert";
	g_bgShader.fragPath = "res/bg.frag";
	g_bgShader.eval();

	sf::Texture bg;
	if (!bg.loadFromFile("res/bg.jpg")) {
		printf("fail load bg");
		return 1;
	}

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
	float bgCol[4] = { 0,0,0,1 };
	float multiplier = 0.1f;
	Clock clock;
	Clock time;
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
		
		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);

		if (mouseLeftIsPressed)
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;
		




		

		auto player = World::player;

		


			
		ImGui::SFML::Update(window, clock.restart());

		ImGui::Begin("Coordonates");
		static bool modified;
		modified = ImGui::SliderInt("CX", &player->cx, 0.0f, wWidth / player->stride);
		modified = ImGui::SliderInt("CY", &player->cy, 0.0f, wHeight / player->stride - 2);
		modified = ImGui::SliderFloat("RX", &player->rx, 0.0f, 1.0f);
		modified = ImGui::SliderFloat("RY", &player->ry, 0.0f, 1.0f);
		modified = ImGui::Checkbox("Enable Gravity", &player->gravity);

		ImGui::Value("Coord X", player->sprite->getPosition().x);
		ImGui::Value("Coord Y", player->sprite->getPosition().y);
		ImGui::Value("Speed X", player->dx);
		ImGui::Value("Speed Y", player->dy);
		ImGui::Value("IsGrounded", player->isGrounded);

		ImGui::SliderFloat("Friction", &player->friction, 0.0f, 1.0f);
		if (modified)
			player->syncSprite();
		ImGui::End();

		static sf::Glsl::Vec4 colAdd = sf::Glsl::Vec4(0, 0, 0, 0);
		static sf::Glsl::Vec4 colMul = sf::Glsl::Vec4(1, 1, 1, 1);

		float id[] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1,
		};
		static sf::Glsl::Mat4 colTrans = sf::Glsl::Mat4(
			id
		);

		if (ImGui::Begin("Shader", 0)) {
			if (ImGui::TreeNode("Add")) {
				ImGui::ColorEdit4("colAdd", &colAdd.x);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Mul")) {
				ImGui::ColorEdit4("colMul", &colMul.x);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Trans")) {
				ImGui::ColorEdit4("r", &colTrans.array[0]);
				ImGui::ColorEdit4("g", &colTrans.array[4]);
				ImGui::ColorEdit4("b", &colTrans.array[8]);
				ImGui::ColorEdit4("a", &colTrans.array[12]);
				ImGui::TreePop();
			}
		}
		ImGui::End();

		g_bgShader.update(dt);

		if (multiplier > 0) {

			bgCol[0] += multiplier * dt * 2;
			bgCol[1] += multiplier * dt * 2;
			bgCol[2] += multiplier * dt * 2;
			if (bgCol[0] >= 1) {
				multiplier = -multiplier;
			}
		}

		/*if (multiplier < 0) {
			bgCol[0] += multiplier * dt * 2;
			bgCol[1] += multiplier * dt * 2;
			bgCol[2] += multiplier * dt * 2;
			g_MainShaderTex.setUniform("colAdd", Glsl::Vec4(
				bgCol[0],
				bgCol[1],
				bgCol[2],
				bgCol[3]));

			if (bgCol[0] <= 0) {
				multiplier = -multiplier;
			}
		}*/

		//ImGui::ShowDemoWindow(&activeTool);
		  
		//CLEAR
		window.clear(Color::Blue);

		////////////////////
		//UPDATE
		data.update(dt);
		////////////////////
		//DRAW
		sf::RectangleShape rectBg;
		rectBg.setTexture(&bg);
		rectBg.setSize(sf::Vector2f(1280, 720));
		auto v = sf::Glsl::Vec4(1.0f, 1.0f, 1.0f, 1.0f);

		{
			auto& sh = g_bgShader.sh;
			sh.setUniform("dt", time.getElapsedTime().asSeconds());
			sh.setUniform("col", v);
			sh.setUniform("colAdd", colAdd);
			sh.setUniform("colMul", colMul);
			sh.setUniform("colTrans", colTrans);
			sf::RenderStates rs;
			rs.shader = &sh;
			window.draw(rectBg, rs);
		}
		/*sf::RenderStates rs;
		rs.shader = &g_MainShaderTex;
		window.draw(rectBg, rs);*/


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