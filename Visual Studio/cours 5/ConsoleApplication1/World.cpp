#include "SFML/Graphics/RenderWindow.hpp"

#include "Entity.hpp"
#include "World.hpp"

void World::update(double dt)
{
	//if (!audio) 
		//audio = new Audio();
	
	PlayerPaddle* pad = nullptr;
	int idx = 0;
	for (auto e : data) {
		if (e->entity == PlayerObject)
			pad = (PlayerPaddle*)e;
	}


	for (auto e : data) {
		Vector2f predPos = e->getPosition();

		e->lastGoodPosition = e->getPosition();

		e->update(dt);

		if (e->entity == PlayerObject)
			pad = (PlayerPaddle*)e;

		if (e->entity == Ball) {

			for (size_t i = 0; i < data.size(); i++)
			{
				auto oe = data[i];
				if (oe->entity == Wall)
					collideWallBall(oe, e);

				if (oe->entity == Brick) {
					collideBrickBall(oe, e);
				}
			}

			if (!pad->currentBall) {
				for (size_t i = 0; i < data.size(); i++)
				{
					auto oe = data[i];
					if (oe->entity == PlayerObject) {
						collidePadBall(oe, e);
					}
				}
			}
		}

	}

	for (auto e : data) {
		e->lastGoodPosition = e->getPosition();
		if (e->entity == Ball) {
			if (e->getPosition().y > 1024) {
				e->setPosition(pad->getPosition());
				pad->currentBall = e;
			};
		}
	}

	if (breackBrick.size()) {
		for (auto b : breackBrick) {
			auto iter = std::find(data.begin(), data.end(), b);
			if (iter != data.end())
				data.erase(iter);
			delete b;
		}
		breackBrick.clear();
	}
}

void World::draw(sf::RenderWindow& win)
{
	for (auto e : data)
		e->draw(win);
}

void World::collideWallBall(Entity * wall, Entity * ball)
{
	if (wall->box.intersects(ball->box)) {
		//audio
		ball->setPosition(ball->lastGoodPosition);
		if (wall->width > wall->height) {
			//mur en haut ou mur en bas
			ball->dy = -ball->dy;
		}
		else {
			//mur de c?t?
			ball->dx = -ball->dx;
		}

	}

}

void World::collideBrickBall(Entity * brick, Entity * ball)
{
	//voir si ball collide avec brick
	if (brick->box.contains(ball->getPosition())) {
		//jouer un son
		ball->setPosition(ball->lastGoodPosition);
		auto oldPos = ball->lastGoodPosition;
		auto boxBrick = brick->box;
		if ((oldPos.y < boxBrick.top) || (oldPos.y > (boxBrick.top + boxBrick.height))) {
			ball->dy = -ball->dy;

		}
		else {
			ball->dx = -ball->dx;
		}
		breackBrick.push_back(brick);
	}

}

void World::collidePadBall(Entity* pad, Entity* ball)
{
	if (pad->box.intersects(ball->box)) {
		//audio
		ball->setPosition(ball->lastGoodPosition);
		ball->dy = -ball->dy;

	}
}

Audio::Audio()
{


}
