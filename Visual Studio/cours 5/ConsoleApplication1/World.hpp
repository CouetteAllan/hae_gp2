#pragma once
#include <vector>
#include "Entity.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class World {
public:
//	Audio* audio = nullptr;
	std::vector<Entity*> data;
	void update(double dt);
	void draw(sf::RenderWindow& win);

	std::vector<Entity*> breackBrick;

	void collideWallBall(Entity* wall, Entity* ball);
	void collideBrickBall(Entity* brick, Entity* ball);
	void collidePadBall(Entity* pad, Entity* ball);

};


class Audio {
public:
	Audio();
	sf::Sound		ballPong;
	sf::SoundBuffer ballPongBuffer;

	sf::Sound		goth;
	sf::SoundBuffer gothBuffer;
};