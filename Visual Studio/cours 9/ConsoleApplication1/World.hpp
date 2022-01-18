#pragma once
#include "Entity.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <optional>

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
	std::unordered_map<sf::Vector2i, sf::Vector2i>		pred;

	std::vector<sf::Vector2i>		queue;
	std::optional<sf::Vector2i>		findMin(std::vector<sf::Vector2i>& q);

	void			updateDist(sf::Vector2i & s1, sf::Vector2i & s2);
	void			compute(const sf::Vector2i& start);
	void			init(const sf::Vector2i& start);
};

class World {
public:
	static inline const int W = 1280;
	static inline const int H = 720;

	static std::vector<sf::RectangleShape* > grid;
	static std::vector<sf::Vector2i> walls;
	static std::vector<sf::Vector2i> currentPath;
	static std::vector<Entity*> objects;
	static Dijkstra		dij;

	static Entity*		player;

	void draw(sf::RenderWindow& win);
	void update(double dt);

	void init();


};