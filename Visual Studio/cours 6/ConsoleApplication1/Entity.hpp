#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>


using namespace sf;

enum EType {
	
};

class Entity : public sf::Transformable {
public:
	Texture texture;
	Sprite sprite;
	FloatRect box;
	EType entity;
	bool visible = true;

	float dx = 0.0f;
	float dy = 0.0f;

	sf::Vector2f	lastGoodPosition;

	float height = 0.0f;
	float width = 0.0f;


	Entity(EType entityType ,Texture _texture,float width, float height, Color color = Color::White) {
		texture = _texture;
		entity = entityType;

		box.height = height;
		box.width = width;

		this->setOrigin(width / 2, height / 2);

		sprite.setTexture(texture);
		sprite.setTextureRect((IntRect)box);

		this->height = height;
		this->width = width;
		sprite.setOrigin(width / 2, height / 2);

		box.top = getPosition().y - height / 2;
		box.left = getPosition().x - width / 2;
	}

	Entity(EType entityType ,float width, float height,Color color = Color::White) {
		entity = entityType;
		box = sprite.getGlobalBounds();
		sprite.setTextureRect((IntRect)box);
		texture.loadFromFile("res/duck.png");
		this->height = height;
		this->width = width;
		sprite.setColor(color);
	}

	~Entity() {
		//delete(sprite);
		
	}

	void update(double dt);

	virtual void draw(RenderWindow& win);
};


class PlayerPaddle : public Entity{
public:

	Entity* currentBall = nullptr;

	PlayerPaddle(EType type, Texture _texture, float width, float height, Color color = Color::White) : Entity(type, _texture,width,height,color) {

	}

	virtual void update(double dt);
	virtual void draw(RenderWindow& win);

};