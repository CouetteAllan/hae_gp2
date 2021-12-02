#include "World.hpp"

void World::draw(RenderWindow& win)
{
	for (auto o : objects) {
		o->draw(win);
	}

}

void World::update(double dt)
{
	for (auto o : objects) {
		o->update(dt);
	}
}
