
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Int64Array.hpp"
#include "Tool.hpp"
#include "List.hpp"
#include <algorithm>
#include <vector>
#include "Tree.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include "Curve.hpp"
#include "Bullet.hpp"
#include "Entity.hpp"
#include "World.hpp"

float catmull(float p0 , float p1 , float p2,float p3 , float t ) {
	auto q = 2.0f * p1;
	auto t2 = t * t;

	q += (-p0 + p2) * t;
	q += (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2;
	q += (-p0 + 3 * p1 - 3 * p2 + p3) * t2 * t;

	return 0.5f * q;
}

void drawMountain(sf::RenderWindow& window) {

	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LineStrip);
	sf::Color col = sf::Color::Green;

	float baseline = 350;

	sf::Vector2f a(0, baseline+50);
	sf::Vector2f b(400, baseline-150);
	sf::Vector2f c(1100, baseline +32);
	sf::Vector2f d(window.getSize().x, baseline);
	col.a = 100;

	col = sf::Color::Magenta;
	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(a.x, a.x, b.x, c.x, t);
		float y = catmull(a.y, a.y, b.y, c.y, t);
		arr.append(sf::Vertex(sf::Vector2f(x, y), col));
	}
	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(a.x, b.x, c.x, d.x, t);
		float y = catmull(a.y, b.y, c.y, d.y, t);
		arr.append(sf::Vertex( sf::Vector2f(x,y), col));
	}

	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(b.x, c.x, d.x, d.x, t);
		float y = catmull(b.y, c.y, d.y, d.y, t);
		arr.append(sf::Vertex(sf::Vector2f(x, y), col));
	}
	window.draw(arr);
}

void drawGround(sf::RenderWindow& window) {
	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LineStrip);
	sf::Color col = sf::Color::Yellow;

	float baseline = 690;

	sf::Vector2f a(0, baseline);
	sf::Vector2f b(window.getSize().x, baseline);

	arr.append(sf::Vertex(a, col));
	arr.append(sf::Vertex(b, col));

	window.draw(arr);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Coin Coin Casse Brick");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(144);

	sf::RectangleShape shape(sf::Vector2f(135,30));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(800, 650);

	/*sf::RectangleShape gun(sf::Vector2f(8, 32));
	gun.setFillColor(sf::Color(	0xFF,0x00,0x00));
	gun.setOrigin(4,0);
	gun.setPosition(800, 600);*/

	sf::Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))	
		cout << "font not loaded" << endl;
	sf::Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(sf::Color::White);
	tDt.setCharacterSize(45);

	sf::CircleShape ptr(8);
	ptr.setFillColor(sf::Color::Cyan);
	ptr.setOrigin(4, 4);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	bool mouseLeftWasPressed = false;
	//-----------TEXTURES-----------------------
	sf::Texture textureWeeb;
	if (!textureWeeb.loadFromFile("res/violet.png"))
		return EXIT_FAILURE;

	sf::Texture textureDuck;
	if (!textureDuck.loadFromFile("res/duck.png"))
		return EXIT_FAILURE;

	sf::Texture textureBall;
	if (!textureBall.loadFromFile("res/ball.png"))
		return EXIT_FAILURE;

	sf::Texture textureWall;
	if (!textureWall.loadFromFile("res/wall.png"))
		return EXIT_FAILURE;

	textureWall.setRepeated(true);

	//----------CREATION DU PADDLE--------------
	const int widthPaddle = 135;
	const int heightPaddle = 30;
	PlayerPaddle* paddle = new PlayerPaddle(PlayerObject,textureWeeb, widthPaddle, heightPaddle);
	paddle->setPosition(800, 650);


	//-----------CREATION DE LA BALLE---------------
	Entity* ball = new Entity(Ball, textureBall, 20, 20);
	paddle->currentBall = ball;
	ball->setPosition(paddle->getPosition() + Vector2f(0, -35));


	//-----------CREATION DES MURS-----------------
	Entity* wallLeft = new Entity(Wall,textureWall, 20, 720);
	wallLeft->setPosition(Vector2f(10, 720/2));
	Entity* wallRight = new Entity(Wall,textureWall, 20, 720);
	wallRight->setPosition(Vector2f(1270, 720/2));
	Entity* wallTop = new Entity(Wall,textureWall, 1280, 20);
	wallTop->setPosition(Vector2f(1280/2, 10));
	Entity* wallBottom = new Entity(Wall,textureWall, 1280, 40);
	wallBottom->setPosition(Vector2f(1280/2, 700));

	
	World world;
	world.data.push_back(paddle);
	world.data.push_back(ball);
	world.data.push_back(wallLeft);
	world.data.push_back(wallRight);
	world.data.push_back(wallTop);
	world.data.push_back(wallBottom);
	//----------CREATION DES BRIQUES---------------
	for (size_t i = 1; i < 7; i++)
	{
		Color randomColor;
		randomColor.r = rand() % 255 + 1;
		randomColor.g = 0;
		randomColor.b = rand() % 255 + 1;
		Entity* brick = new Entity(Brick, textureDuck, 120, 35, randomColor);

		for (size_t j = 1; j < 8; j++)
		{
			//faire la brique
			
			float brickWidth = 120;
			float brickHeight = 35;
			Entity* brick = new Entity(Brick, textureDuck, 120, 35, randomColor);
			//placer la brique
			auto pos = brick->getPosition();
			pos.x = j * (brickWidth + 40);
			pos.y = i * 60;
			brick->setPosition(pos);

			//faire un offset

			world.data.push_back(brick);
		}
	}


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
				break;

			default:
				break;
			}
		}
		auto pos = paddle->getPosition();
		float deltaX = dt * 360;
		float deltaY = dt * 360;
		bool keyHit = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			pos.x -= deltaX;
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			pos.x += deltaX;
			keyHit = true;
		}
		if (keyHit) {
			if (pos.x < 20)
					pos.x = 20;
			if (pos.x > window.getSize().x - 20)
					pos.x = window.getSize().x - 20;
			paddle->setPosition(pos);
		}

		/*if (paddle->box.intersects(ball->box)) {
			ball->dy = -ball->dy;
		}*/


		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			//auto pos = gun.getPosition();
			auto dir = mousePos - pos;
			float dirLen = std::sqrt(dir.x * dir.x + dir.y * dir.y);
			sf::Vector2f dxy(1, 0);
			if (dirLen) {
				dxy = dir / dirLen;
			}
			dxy *= 60.0f * 7;
			if (paddle->currentBall) {
				paddle->currentBall->dx = dxy.x;
				paddle->currentBall->dy = dxy.y;
			}
			paddle->currentBall = nullptr;
		}

		if (mouseLeftIsPressed) 
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;

		//calculate angle from char to mouse
		sf::Vector2f characterToMouse(
			mousePos.y - paddle->getPosition().y,
			mousePos.x - paddle->getPosition().x);

		float radToDeg = 57.2958;
		float angleC2M = atan2(characterToMouse.y, characterToMouse.x);
		//gun.setRotation(-angleC2M * radToDeg);
		//gun.setPosition(shape.getPosition() + sf::Vector2f(8, 16));
		///

		ptr.setPosition(mousePos);
		tDt.setString( to_string(dt)+" FPS:"+ to_string((int)(1.0f / dt)));
		
		
		////////////////////

		//CLEAR
		window.clear();
		
		////////////////////
		//UPDATE
		world.update(dt);
		////////////////////
		//DRAW
		//drawMountain(window);
		drawGround(window);
		//bullets.draw(window);

		//game elems
		//window.draw(shape);
		world.draw(window);
		//window.draw(gun);
		
		//c.draw(window);
		//window.draw(ptr);

		//ui
		//window.draw(tDt);
		
		window.display();
		tExitFrame = getTimeStamp();
	}

	return 0;
}