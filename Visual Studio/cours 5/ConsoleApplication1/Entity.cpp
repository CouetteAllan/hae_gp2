#include "Entity.hpp"

void Entity::update(double dt)
{
	auto pos = getPosition();
	pos.x += dx * dt;
	pos.y += dy * dt;
	setPosition(pos);
	

	box.top = getPosition().y - height/2;
	box.left = getPosition().x - width/2;
}

inline void Entity::draw(RenderTarget & win, RenderStates states) const {
	if (visible) {

		states.transform *= getTransform();//defined by sf::Transformable

		states.texture = &texture;
		win.draw(sprite, states);
	}
}

void PlayerPaddle::update(double dt)
{
	Entity::update(dt);
	if (currentBall)
		currentBall->setPosition(getPosition() + Vector2f(0,-25));
}

void PlayerPaddle::draw(RenderWindow & win)
{
	Entity::draw(win,RenderStates::Default);

}
