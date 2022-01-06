#pragma once
#include "Entity.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unordered_map>

class Entity;

namespace std {
	template <>
	struct hash<sf::Vector2i> {
		std::size_t operator()(const sf::Vector2i& k) const {
			using std::size_t;
			using std::hash;
			using std::string;
			return k.x | (k.y << 12);
		}
	};
}

class Dijkstra {
public:

	std::unordered_map<sf::Vector2i, bool>		g;
	std::unordered_map<sf::Vector2i, float>		dist;

	void			compute();
};

class World {
public:
	static std::vector<sf::RectangleShape* > grid;
	static std::vector<Entity*> objects;
	static Dijkstra		dij;

	void draw(sf::RenderWindow& win);
	void update(double dt);

	void init();


};