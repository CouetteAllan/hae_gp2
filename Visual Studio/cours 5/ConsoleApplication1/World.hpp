#pragma once
#include "Entity.hpp"

class World {
public:
	std::vector<Entity*> data;

	void update();
	void draw(sf::RenderWindow& win);
};