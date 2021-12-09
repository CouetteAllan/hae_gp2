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

void Entity::syncSprite()
{
	xx = floor((cx + rx) * stride);
	yy = floor((cy + ry) * stride);
	sprite->setPosition(xx, yy);
}

void Entity::update(double dt)
{
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
	if(!isGrounded && type != Wall && gravity)
		dy += 80.0f * dt;
	dy *= 0.95f;
	
	if (isColliding(cx, cy - 1) && ry <= 0.0f) {
		ry = 1.0f;
		dy = 0;
	}
	
	if (isColliding(cx, cy + 1) && ry >= 0.9f) {
		ry = 1.0f;
		dy = 0;
		isGrounded = true;
	}

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

void Entity::handleCollisions(Entity* e)
{
	if (e) {
		if (e->type == Wall) {
			//collide avec des entités (murs,sol,ennemis...)
			//verifie si il y a une case à la droite du player ET si la case est alignée avec lui sur l'axe Y
			if ((cx + rx) * stride >= e->xx && cy == e->cy + 1 && cx == e->cx) {
				//remet le player à côté de la case
 				cx--;
				rx = 0.8f;
				dx = 0;
			}
			//pareil mais à gauche du player (sauf que ça marche pas pour l'instant)
			if ((cx - rx) * stride <= e->xx && cy == e->cy + 1 && cx == e->cx + 1) {
				rx = 0.3f;
				dx = 0;
			}

			//pareil mais sous le joueur
			if (cy == e->cy && cx == e->cx) {
				ry = 0.0f;
				dy = 0;
				isGrounded = true;
			}
			//et au dessus du joueur
			if (cy - 1 == e->cy && cx == e->cx) {
				ry = 0.0f;
				cy = cy + 1;
				dy = 0;
			}
		}
	}
	if ((cx + rx)*stride > 1280) {
		rx = 0.7f;
		dx = 0;
	}
	
	if ((cx + rx)*stride < 0) {
		rx = 0.3f;
		dx = 0;
	}
	
	if ((cy + ry) * stride > 640.0f ) {
		isGrounded = true;
		ry = 0.0f;
		cy = 650.0f / stride;
		dy = 0;
	}
	
	if ((cy + ry)*stride < 10) {
		ry = 0.7f;
		dy = 0;
	}



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
