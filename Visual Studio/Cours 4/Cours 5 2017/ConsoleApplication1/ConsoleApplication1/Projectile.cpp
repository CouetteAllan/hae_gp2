#include "Projectile.hpp"


Projectile::Projectile() {
	projectile = sf::CircleShape(15);
	projectile.setOutlineThickness(5);
	projectile.setOutlineColor(sf::Color::Cyan);
	projectile.setFillColor(sf::Color::Blue);
	projectile.setOrigin(12, 12);
}

Projectile::Projectile(sf::RectangleShape gun) {
	projectile = sf::CircleShape(15);
	projectile.setOutlineThickness(5);
	projectile.setOutlineColor(sf::Color::Cyan);
	projectile.setFillColor(sf::Color::Blue);
	projectile.setOrigin(12, 12);
	projectile.setPosition(gun.getPosition());
}

void Projectile::create(float _px, float _py, float _dx, float _dy)
{
	for (int i = 0; i < px.size(); i++)
	{
		if (!alive[i]) {
			px[i] = _px;
			py[i] = _py;
			dx[i] = _dx;
			dy[i] = _dy;
			alive[i] = true;
			return;
		}
	}
	px.push_back(_px);
	py.push_back(_py);
	dy.push_back(_dy);
	dx.push_back(_dx);
	alive.push_back(true);

}

void Projectile::update(double dt) {
	for (int i = 0; i < px.size(); ++i) {
		if (alive[i]) {
			px[i] += dx[i] * dt;
			py[i] += dy[i] * dt;
			if (
				(px[i] > 3000) || (px[i] < -100) ||
				(py[i] > 3000) || (py[i] < -100)
				) {
				alive[i] = false;
			}
		}
	}
}
void Projectile::draw(sf::RenderWindow& win) {
	int idx = 0;
	const int sz = px.size();
	while (idx < sz) {
		if (alive[idx]) {
			projectile.setPosition(px[idx], py[idx]);
			win.draw(projectile);
		}
		idx++;
	}
}

