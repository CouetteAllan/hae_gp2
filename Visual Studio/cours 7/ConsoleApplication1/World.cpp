#include "World.hpp"

void World::draw(RenderWindow& win)
{
	for (auto o : objects) {
		o->draw(win);
	}
	for (auto r : grid) {
		win.draw(*r);
	}
}

void World::update(double dt)
{
	Entity* p = nullptr;
	for (auto o : objects) {
		o->update(dt);

		if (o->type == Player)
			p = o;
			for (int j = 0; j < objects.size(); ++j) {
				auto oe = objects[j];
				if (oe->type == Wall) {
					p->handleCollisions(oe);

				}
			}
	}
}
