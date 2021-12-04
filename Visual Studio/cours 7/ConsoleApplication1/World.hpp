#pragma once
#include "Entity.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

class World {
public:
	std::vector<Entity*> objects;


	void draw(RenderWindow& win);
	void update(double dt);


};