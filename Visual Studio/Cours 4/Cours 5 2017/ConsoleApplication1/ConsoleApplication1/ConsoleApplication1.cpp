#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include "Projectile.hpp"

float catmull(float p0,float p1, float p2, float p3, float t) {
	auto q = 2.0f * p1;
	auto t2 = t * t;



	q += (-p0 + p2) 					* t;
	q += (2.0*p0 - 5.0f*p1 + 4.0f * p2 - p3) 	* t2;
	q += (-p0 + 3.0f * p1 - 3.0f * p2 + p3) 	* t2 * t;

	return 0.5 * q;
}


void drawMountain(sf::RenderWindow& window) {
	sf::VertexArray mountain(sf::LineStrip);
	sf::Color col = sf::Color::Red;

	float sommet = 100;


	sf::Vector2f a(-400, 630);
	sf::Vector2f b(600, sommet);
	sf::Vector2f c(1000, sommet +50);
	sf::Vector2f d(1300, 450);
	
	/*mountain.append(sf::Vertex(sf::Vertex(a,col)));
	mountain.append(sf::Vertex(sf::Vertex(b,col)));
	mountain.append(sf::Vertex(sf::Vertex(c,col)));
	mountain.append(sf::Vertex(sf::Vertex(d,col)));
	window.draw(mountain);

	mountain.clear();*/

	for (size_t i = 0; i < 256; i++)
	{
		float t = 1.0f * i / 256;
		//float x = (window.getSize().x - 0) * t;
		float y = catmull(a.y, a.y, b.y, c.y, t);
		float x = catmull(a.x, a.x, b.x, c.x, t);

		mountain.append(sf::Vertex(sf::Vector2f(x, y), col));
	}

	for (size_t i = 0; i < 256; i++)
	{
		float t = 1.0f * i / 256;
		//float x = (window.getSize().x - 0) * t;
		float y = catmull(a.y, b.y, c.y, d.y, t);
		float x = catmull(a.x, b.x, c.x, d.x, t);

		mountain.append(sf::Vertex(sf::Vector2f(x, y),col));
	}
	for (size_t i = 0; i < 256; i++)
	{
		float t = 1.0f * i / 256;
		//float x = (window.getSize().x - 0) * t;
		float y = catmull(b.y, c.y, d.y, d.y, t);
		float x = catmull(b.x, c.x, d.x, d.x, t);

		mountain.append(sf::Vertex(sf::Vector2f(x, y), col));
	}
	
	window.draw(mountain);
}


void drawGround(sf::RenderWindow& window) {
	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LineStrip);
	sf::Color col =  sf::Color::Green;

	float baseline = 600 + 30;

	sf::Vector2f a(0, baseline);
	sf::Vector2f b(window.getSize().x, baseline);

	arr.append(sf::Vertex(sf::Vertex(a,col)));
	arr.append(sf::Vertex(sf::Vertex(b,col)));
	window.draw(arr);
}


void shootProjectile(sf::RectangleShape gun) {
	sf::CircleShape projectile(20);
	projectile.setPosition(gun.getPosition().x, gun.getPosition().y);
	projectile.setOrigin(sf::Vector2f(20, 20));
	projectile.setFillColor(sf::Color::White);
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	window.setVerticalSyncEnabled(true);
	sf::Vector2u size = window.getSize();
	float width = size.x;
	float height = size.y;

	sf::Vector2f localMousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);


	sf::RectangleShape shape(sf::Vector2f(80, 40));
	sf::Vector2f center;
	center.x = shape.getSize().x / 2;
	center.y = shape.getSize().y / 2;
	shape.setOrigin(center);
	shape.setFillColor(sf::Color::Blue);
	shape.setOutlineThickness(10);
	shape.setOutlineColor(sf::Color::Magenta);
	shape.setPosition(width / 2, 600);


	sf::RectangleShape gun(sf::Vector2f(10, 90));
	sf::Vector2f gunCenter;
	gun.setOrigin(sf::Vector2f(5, 75));
	gun.setFillColor(sf::Color::Red);
	gun.setOutlineThickness(2);
	gun.setOutlineColor(sf::Color::Cyan);

	
	bool shoot = false;

	sf::CircleShape mouseCircle(10);
	mouseCircle.setOrigin(10, 10);
	mouseCircle.setFillColor(sf::Color::Yellow);
	mouseCircle.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	Projectile projectiles;
	
	//double tEnterFrame = getTimeStamp;
	//double tExitFrame = getTimeStamp;
	sf::Mouse::setPosition(sf::Vector2i(width / 2, height / 2), window);
	while (window.isOpen())
	{
		localMousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
		//double dt = tExitFrame - tEnterFrame;
		sf::Event event;
		while (window.pollEvent(event))
		{
			// on regarde le type de l'évènement...
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

			case::sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
					shoot = true;
				else
					shoot = false;
			default:
				break;
			}
		}
		bool shoot = sf::Mouse::isButtonPressed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			shape.move(-5.f, 0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			shape.move(5.f, 0.f);

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			shape.move(0.f, -3.f);*/

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			shape.move(0.f, 3.f);*/



		if (shoot) {
			auto pos = gun.getPosition();
			auto dir = localMousePosition - pos;
			float dirLen = std::sqrt(dir.x * dir.x + dir.y * dir.y);
			sf::Vector2f dxy(1, 0);
			if (dirLen) {
				dxy = dir / dirLen;
			}
			dxy *= 60.0f * 3;
			projectiles.create(pos.x, pos.y, dxy.x, dxy.y);
		}

		auto angle = atan2((localMousePosition.x - gun.getPosition().x), -(localMousePosition.y - gun.getPosition().y));
		angle = (angle / 3.1415926) * 180; //rad en degré
		gun.setRotation(angle);
		gun.setPosition(shape.getPosition().x, shape.getPosition().y);

		mouseCircle.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		//---------------------------------------------------
		//CLEAR
		window.clear();
		//---------------------------------------------------
		//---------------------------------------------------
		//UPDATE
		//projectiles.update(dt);

		//---------------------------------------------------
		//---------------------------------------------------
		//DRAW
		drawMountain(window);
		drawGround(window);
		window.draw(shape);
		window.draw(gun);
		//window.draw(mouseCircle);
		window.display();
		//---------------------------------------------------

	}



	return 0;
}
