#include "World.hpp"
#include "Entity.hpp"

std::vector<Entity*> World::objects;
std::vector<RectangleShape*> World::grid;
Dijkstra World::dij;

void World::draw(RenderWindow& win)
{
	for (auto o : objects) {
		o->draw(win);	
	}
	for (auto r : grid) {
		win.draw(*r);
	}
}

void World::init() {
	dij.dist[sf::Vector2i(0, 0)] = 1.0f;
}

void World::update(double dt)
{
	Entity* p = nullptr;
	for (auto o : objects) {
		o->update(dt);

	}
}

void Dijkstra::compute()
{
	g.clear();
	int maxCellH = 720 / Entity::stride + 1;
	int maxCellW = 1080 / Entity::stride + 1;
	for (size_t y = 0; y < maxCellH; y++)
	{
		for (size_t x = 0; x < maxCellW; x++)
		{
			g[sf::Vector2i]
		}
	}
}
