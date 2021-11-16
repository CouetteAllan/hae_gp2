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
	IntRect box;
	Shape* shape = nullptr;
	EType entity;


	Entity(EType entityType ,Texture _texture,float width, float height, Color color = Color::White) {
		texture = _texture;
		entity = entityType;
		box.height = height;
		box.width = width;
		sprite.setTextureRect(box);
		sprite.setTexture(texture);
	}

	Entity(EType entityType ,float width, float height,Color color = Color::White) {
		entity = entityType;
		box.height = height;
		box.width = width;
		sprite.setTextureRect(box);
		texture.loadFromFile("res/duck.png");
		sprite.setColor(color);
	}

	~Entity(){
		if (shape) {
			shape = nullptr;
		}
	}


	virtual void draw(RenderTarget& target, RenderStates states) const;
};


class PlayerPaddle : public Entity{
public:

	Entity* currentBall = nullptr;

	void update(double dt);
	virtual void draw(RenderWindow& win);

};