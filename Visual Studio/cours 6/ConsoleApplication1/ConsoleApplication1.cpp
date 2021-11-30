
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
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include "imgui.h"
#include "imgui-SFML.h"

void writeFile(FILE* file, Command* cmd) {



}

int main()
{
	float wHeight = 720;
	float wWidth = 1280;
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Tortue du turfu");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(144);

	ImGui::SFML::Init(window);

	sf::Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))	
		cout << "font not loaded" << endl;
	sf::Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(sf::Color::White);
	tDt.setCharacterSize(45);

	

	Texture textureDuck;
	if (!textureDuck.loadFromFile("res/duck.png"))
		return EXIT_FAILURE;
		

	Turtle turtle;
	turtle.textureTurtle = textureDuck;
	turtle.createTextureInWindow(window.getSize().x, window.getSize().y);
	turtle.trs.translate(680, 360);
	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();
	float penColor[3] = { 0 , 0 , 0 };
	

	bool mouseLeftWasPressed = false;
	bool enterWasPressed = false;

	struct _stat buf;
	int result;
	const char* filename = "res/ui.txt";
	char time[26];
	errno_t err;
	bool automatic = false;
	result = _stat(filename, &buf);

	// Check if statistics are valid:
	if (result != 0)
	{
		perror("Problem getting information");
		switch (errno)
		{
		case ENOENT:
			printf("File %s not found.\n", filename);
			break;
		case EINVAL:
			printf("Invalid parameter to _stat.\n");
			break;
		default:
			printf("Unexpected error in _stat.\n");
		}
	}
	else {
		printf("File size :  %ld\n", buf.st_size);
		ctime_s(time, 26, &buf.st_mtime);
		printf("Last Modif :  %s", time);
	}
	auto lastTime = buf.st_mtime;
	float timer = 0.0f;
	bool doReinterpret = false;
	//----------------------------------------  IMGUI STUFF  -------------------------------------------------------------
	bool activeTool = true;
	Clock clock;
	while (window.isOpen()){
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		while (window.pollEvent(event)){
			ImGui::SFML::ProcessEvent(event);
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
					turtle.color = turtle.changeColor();

				if (event.key.code == sf::Keyboard::F)
					turtle.automatik = !turtle.automatik;
				break;
				
			default:
				break;
			}
		}
		//auto pos = turtle->getPosition();
		float deltaX = dt * 360;
		float deltaY = dt * 360;
		bool keyHit = false;

		if (!automatic) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				turtle.translate(-7 * dt * 80);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				turtle.translate(7 * dt * 80);
			}
		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				turtle.rotate(5 * dt * 60);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				turtle.rotate(-5 * dt * 60);
			}
		}


		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		bool enterIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
		bool enterIsReleased = (!enterIsPressed && enterWasPressed);
		static bool enterWasPressed = false;

		if (enterIsPressed && !enterWasPressed && turtle.automatik || doReinterpret && turtle.automatik) {
			FILE* f = nullptr;
			fopen_s(&f, "res/ui.txt", "rb");
			if (f && !feof(f)) {
				char line[256] = {};
				while (true) {
					int64_t nb = 0;
					fscanf_s(f, "%s %lld\n",line,256,&nb);
					std::string s = line;
					if (s == "Advance"){
						turtle.translate(nb);

					}
					else if (s == "Rotate") {
						turtle.rotate(nb);

					}
					else if (s == "PenDown") {
						turtle.draw(true);

					}
					else if (s == "PenUp") {
						turtle.draw(false);

					}
					else if (s == "Clear") {
						turtle.appendCmd(new Command(Clear,0.0f));

					}
					if (feof(f))
						break;
				}
				fclose(f);
				turtle.writeCommands("res/uiWrite.txt");

			}
			enterWasPressed = true;
			doReinterpret = false;
		}

		if (enterIsPressed) 
			enterWasPressed = true;
		else
			enterWasPressed = false;

		if (timer > 0.1f) {
			_stat("res/ui.txt", &buf);

			if (lastTime < buf.st_mtime ) {
				doReinterpret = true;
				lastTime = buf.st_mtime;
			}
			timer = 0.0f;
		}



		tDt.setString( to_string(dt)+" FPS:"+ to_string((int)(1.0f / dt)));

		ImGui::SFML::Update(window, clock.restart());

		ImGui::Begin("ImGui works",&activeTool,ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Close", "Ctrl + W"))
					activeTool = false;
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::Text("Text");
		ImGui::ColorEdit3("Pen Color!", penColor);
		if (ImGui::Button("Load File")) {
			printf("oeeeeeeeee");
		}
		ImGui::End();

		ImGui::ShowDemoWindow(&activeTool);

		turtle.color = Color(
			penColor[0] * 255,
			penColor[1] * 255,
			penColor[2] * 255
		);

		////////////////////
		turtle.drawTexture.display();
		//CLEAR
		window.clear(Color::Cyan);
		
		////////////////////
		//UPDATE
		turtle.update(dt);
		timer += dt;
		////////////////////
		//DRAW
		sf::Sprite sprite(turtle.drawTexture.getTexture());
		turtle.draw(window);
		window.draw(sprite);
		//game elems

		

		//ui
		if(turtle.isDrawing)
			window.draw(tDt);

		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();
	}
	ImGui::SFML::Shutdown();

	return 0;
}