#include "Entity.hpp"

inline void Entity::draw(RenderTarget & target, RenderStates states) const {
	states.transform *= getTransform();//defined by sf::Transformable

	states.texture = &texture;
	target.draw(sprite, states);
}

void PlayerPaddle::draw(RenderWindow & win)
{
	Entity::draw(win,RenderStates::Default);

}
