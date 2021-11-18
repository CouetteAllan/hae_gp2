#include "Entity.hpp"

void Entity::update(double dt)
{
	auto pos = this->getPosition();
	pos.x += dx * dt;
	pos.y += dy * dt;
	this->setPosition(pos);
	sprite.setPosition(pos);

	box.top = getPosition().y - height/2;
	box.left = getPosition().x - width/2;
}

inline void Entity::draw(RenderWindow& win) {
	if (visible) {

		win.draw(sprite);
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
	Entity::draw(win);

}
