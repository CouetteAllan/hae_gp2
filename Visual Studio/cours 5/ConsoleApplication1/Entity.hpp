#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>

				//permet de draw		//definis la position/rotation/scale
class Entity : public sf::Drawable, public sf::Transformable {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::FloatRect box;


	Entity(sf::Texture _texture,float width, float height) {
		sprite.setTexture(texture);
		box.height = height;
		box.width = width;
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();//defined by sf::Transformable

		states.texture = &texture;

		target.draw(sprite, states);
	}
};