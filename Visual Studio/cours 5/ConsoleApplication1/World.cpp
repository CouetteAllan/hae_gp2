#include "World.hpp"


void World::update()
{

}

void World::draw(sf::RenderWindow & win)
{
	for (auto e : data)
		e->draw(win,sf::RenderStates::Default);
}
