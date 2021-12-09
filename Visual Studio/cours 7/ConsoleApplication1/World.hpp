#pragma once
#include "Entity.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

class Entity;

class World {
public:
	std::vector<sf::RectangleShape* > grid;
	std::vector<Entity*> objects;


	void draw(sf::RenderWindow& win);
	void update(double dt);


};