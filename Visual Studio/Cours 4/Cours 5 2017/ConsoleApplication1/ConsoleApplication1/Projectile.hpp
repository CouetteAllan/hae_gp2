#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <stdlib.h>


class Projectile{
public:
	sf::CircleShape projectile;

	std::vector<float> px;
	std::vector<float> py;

	std::vector<float> dx;
	std::vector<float> dy;


	sf::Vector2f pos = sf::Vector2f(610, 480);
	int speed = 20.0f;
	sf::Vector2i dir = sf::Mouse::getPosition();
	std::vector<bool> alive;

	Projectile();
	Projectile(sf::RectangleShape gun);

	void create(float px, float py, float dx, float dy);
	void update(double dt);

	void draw(sf::RenderWindow& win);


protected:
	sf::Vector2i normalize(const sf::Vector2i& source)
	{
		float length = sqrt((source.x * source.x) + (source.y * source.y));
		if (length != 0)
			return sf::Vector2i(source.x / length, source.y / length);
		else
			return source;
	}
};


