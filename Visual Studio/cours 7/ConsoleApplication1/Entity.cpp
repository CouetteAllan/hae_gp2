#include "Entity.hpp"

void Entity::setPosition(float x, float y)
{
	xx = x;
	yy = y;
	cx = floor(xx / 16);
	cy = floor(yy / 16);
	xr = (xx - cx * 16) / 16;
	yr = (yy - cy * 16) / 16;
	sprite.setPosition(xx, yy);


}

void Entity::update(double dt)
{
	xr += dx;


	while (xr > 1) { xr--; cx++; }

	xx = floor((cx + xr) * 16);
	yy = floor((cy + yr) * 16);
	sprite.setPosition(xx, yy);
}
