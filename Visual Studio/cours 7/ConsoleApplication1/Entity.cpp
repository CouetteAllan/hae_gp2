#include "Entity.hpp"

void Entity::setPosition(float x, float y)
{
	xx = x;
	yy = y;
	cx = floor(xx / stride);
	cy = floor(yy / stride);
	rx = (xx - cx * stride) / stride;
	ry = (yy - cy * stride) / stride;


}

void Entity::syncSprite()
{
	xx = floor((cx + rx) * stride);
	yy = floor((cy + ry) * stride);
	sprite->setPosition(xx, yy);
}

void Entity::update(double dt)
{

	dx *= friction;
	rx += dx * dt;


	

	while (rx > 1) {
		handleCollisions();

		rx--;
		cx++;
	}
	while (rx < 0) {
		handleCollisions();

		rx++; 
		cx--;
	}


	ry += dy * dt;
	if(!isGrounded && type != Wall && gravity)
		dy += 50.0f * dt;
	dy *= 0.95f;
	while (ry > 1) {
		handleCollisions();

		ry--;
		cy++;
	}
	while (ry < 0) {
		handleCollisions();

		ry++;
		cy--;
	}

	syncSprite();
}

void Entity::handleCollisions(Entity* e)
{
	if (e) {
		if (e->type == Wall) {
			//collide avec des entités (murs,sol,ennemis...)
			if (cx == e->cx && cy == e->cy + 1) {
				rx = 0.0f;
				dx = 0;
			}

			if (cx - 1 == e->cx && cy == e->cy + 1) {
				cx = cx + 1;
				rx = 0.0f;
				dx = 0;
			}

			if (cy == e->cy && cx == e->cx) {
				ry = 0.0f;
				dy = 0;
				isGrounded = true;
			}
			if (cy - 1 == e->cy && cx == e->cx) {
				ry = 0.0f;
				dy = 0;
			}
		}
	}
	if (((cx + rx)*stride) > 1280) {
		rx = 0.7f;
		dx = 0;
	}
	
	if (((cx + rx)*stride) < 0) {
		rx = 0.3f;
		dx = 0;
	}
	
	if ((cy + ry) > 640.0f / stride) {
		isGrounded = true;
		ry = 0.0f;
		cy = 650.0f / stride;
		dy = 0;
	}
	
	if (((cy + ry)*stride) < 10) {
		rx = 0.7f;
		dy = 0;
	}



}

void Entity::draw(RenderWindow &win)
{
	win.draw(*sprite);
}

bool Entity::hasCollision(int _cx, int _cy)
{

	//regarde si il y a quelque chose en (_cx,_cy);


	return false;
}
