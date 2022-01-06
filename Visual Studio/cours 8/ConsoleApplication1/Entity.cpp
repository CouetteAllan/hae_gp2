#include "Entity.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "imgui.h"
#include "World.hpp"

void Entity::setPosition(float x, float y)
{
	xx = x;
	yy = y;
	cx = floor(xx / stride);
	cy = floor(yy / stride);
	rx = (xx - cx * stride) / stride;
	ry = (yy - cy * stride) / stride;


}

void Entity::setState(State * state)
{
	if (currentState)
		delete currentState;

	currentState = state;
	currentState->onEnter();
}

void Entity::syncSprite()
{
	xx = floor((cx + rx) * stride);
	yy = floor((cy + ry) * stride);
	sprite->setPosition(xx, yy);
}

void Entity::update(double dt)
{
	if (currentState) {
		currentState->onUpdate(dt);
	}

	if (type == Wall) {
		return;
	}
	rx += dx * dt;
	dx *= friction;//0.96f


	
	if (isColliding(cx + 1, cy)&& rx >= 0.8f) {
		rx = 0.8f;
		dx = 0;
	}
	
	if (isColliding(cx - 1, cy)&& rx <= 0.2f) {
		rx = 0.2f;
		dx = 0;
	}

	while (rx > 1) {

		rx--;
		cx++;
	}
	while (rx < 0) {

		rx++; 
		cx--;
	}


	ry += dy * dt;
	/*if(!isGrounded && type != Wall && gravity)
		dy += 80.0f * dt;*/
	dy *= friction;
	
	if (isColliding(cx, cy - 1) && ry <= 0.0f) {
		ry = 0.0f;
		dy = 0;
	}
	
	if (isColliding(cx, cy + 1) && ry >= 1.0f) {
		ry = 1.0f;
		dy = 0;
		isGrounded = true;
	}
	else
		isGrounded = false;

	while (ry > 1) {

		ry--;
		cy++;
	}
	while (ry < 0) {

		ry++;
		cy--;
	}

	syncSprite();
}


void Entity::draw(RenderWindow &win)
{
	win.draw(*sprite);
}

bool Entity::isColliding(int _cx, int _cy)
{
	if (cx < 0)
		return true;
	if (cy < 0)
		return true;
	if (cx > 1280 / stride)
		return true;
	if (cy > 720 / stride)
		return true;
	
	for (auto& w : World::objects) {
		if (w->type != Player) {

			if (w->cx == _cx && w->cy == _cy)
				return true;
		}
	}

	return false;

	//regarde si il y a quelque chose en (_cx,_cy);
	//cx 
}

void IdleState::onEnter()
{
	if (e->sprite) {
		delete e->sprite;
	}
	RectangleShape* heroSprite = new RectangleShape(Vector2f(15, 35));
	heroSprite->setFillColor(Color::Red);
	heroSprite->setOrigin(heroSprite->getSize().x / 2, heroSprite->getSize().y);
	e->sprite = heroSprite;
}

void IdleState::onUpdate(double dt)
{
	bool movement = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
	
	bool sprint = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

	if(movement)
		return e->setState(new WalkState(e));

	if (movement && sprint)
		return e->setState(new RunState(e));

	timer -= dt;
	bool collide = e->isColliding(e->cx + 1, e->cy) && e->rx >= 0.8f ||
		e->isColliding(e->cx - 1, e->cy) && e->rx <= 0.2f ||
		e->isColliding(e->cx, e->cy - 1) && e->ry <= 0.0f ||
		e->isColliding(e->cx, e->cy + 1) && e->ry >= 0.9f;



	if (collide) {
		timer -= dt/10;
		if (timer <= 0) {
			timer = timerReset;
			e->setState(new CoverState(e));
		}
	}
}

void WalkState::onEnter()
{
	if (e->sprite) {
		delete e->sprite;
	}
	RectangleShape* heroSprite = new RectangleShape(Vector2f(15, 35));
	heroSprite->setFillColor(Color::Green);
	heroSprite->setOrigin(heroSprite->getSize().x / 2, heroSprite->getSize().y);
	e->sprite = heroSprite;
}

void WalkState::onUpdate(double dt)
{
	bool movement = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z);

	bool sprint = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		e->dx += 2;

	} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		e->dx -= 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		e->dy += 2;

	} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		e->dy -= 2;
	}

	if (abs(e->dx) <= 1 && abs(e->dy)<=1) {
		e->setState(new IdleState(e));
	}

	if (sprint && movement)
		e->setState(new RunState(e));

}

void RunState::onEnter()
{
	if (e->sprite) {
		delete e->sprite;
	}
	RectangleShape* heroSprite = new RectangleShape(Vector2f(15, 35));
	heroSprite->setFillColor(Color::Blue);
	heroSprite->setOrigin(heroSprite->getSize().x / 2, heroSprite->getSize().y);
	e->sprite = heroSprite;

}

void RunState::onUpdate(double dt)
{
	bool movement = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z);

	bool sprint = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sprint) {
		e->dx += 2 * 2;

	} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sprint) {
		e->dx -= 2 * 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sprint) {
		e->dy += 2 * 2;

	} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sprint) {
		e->dy -= 2*2;
	}

	if (abs(e->dx) <= 1 && abs(e->dy) <= 1) {
		e->setState(new IdleState(e));
	}

	if (!sprint && movement)
		e->setState(new WalkState(e));
}

void CoverState::onEnter()
{
	if (e->sprite) {
		delete e->sprite;
	}
	RectangleShape* heroSprite = new RectangleShape(Vector2f(15, 35));
	heroSprite->setFillColor(Color::Yellow);
	heroSprite->setOrigin(heroSprite->getSize().x / 2, heroSprite->getSize().y);
	e->sprite = heroSprite;
}

void CoverState::onUpdate(double dt)
{
	bool movement = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z);

	bool sprint = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);


	if (movement) {
		e->setState(new WalkState(e));
	}

	if (sprint && movement)
		e->setState(new RunState(e));
}
