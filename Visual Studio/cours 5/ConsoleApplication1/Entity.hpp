#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>


using namespace sf;

enum EType {
	PlayerObject,
	Brick,
	Wall,
	Ball,
};

class Entity : public sf::Drawable, public sf::Transformable {
public:
	Texture texture;
	Sprite sprite;
	FloatRect box;
	Shape* shape = nullptr;
	EType entity;
	bool visible = true;

	float dx = 0.0f;
	float dy = 0.0f;

	float height = 0.0f;
	float width = 0.0f;


	Entity(EType entityType ,Texture _texture,float width, float height, Color color = Color::White) {
		texture = _texture;
		entity = entityType;
		box.height = height;
		box.width = width;
		sprite.setTexture(texture);
		sprite.setTextureRect((IntRect)box);
		this->height = height;
		this->width = width;
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
		if (shape) {
			delete shape;
			shape = nullptr;
		}
	}

	void update(double dt);

	virtual void draw(RenderTarget& target, RenderStates states) const;
};


class PlayerPaddle : public Entity{
public:

	Entity* currentBall = nullptr;

	PlayerPaddle(EType type, Texture _texture, float width, float height, Color color = Color::White) : Entity(type, _texture,width,height,color) {

	}

	virtual void update(double dt);
	virtual void draw(RenderWindow& win);

};