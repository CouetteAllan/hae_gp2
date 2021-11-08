#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <math.h>
int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	window.setVerticalSyncEnabled(true);
	sf::Vector2u size = window.getSize();
	float width = size.x;
	float height = size.y;

	sf::Vector2f localMousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);


	sf::RectangleShape shape(sf::Vector2f(80, 40));
	sf::Vector2f center;
	center.x = shape.getSize().x / 2;
	center.y = shape.getSize().y / 2;
	shape.setOrigin(center);
	shape.setFillColor(sf::Color::Blue);
	shape.setOutlineThickness(10);
	shape.setOutlineColor(sf::Color::Magenta);
	shape.setPosition(width / 2, height / 2 + 50);


	sf::RectangleShape gun(sf::Vector2f(10, 90));
	sf::Vector2f gunCenter;
	gunCenter.x = gun.getSize().x / 2;
	gunCenter.y = gun.getSize().y / 2;
	gun.setOrigin(sf::Vector2f(5, 75));
	gun.setFillColor(sf::Color::Red);
	gun.setOutlineThickness(2);
	gun.setOutlineColor(sf::Color::Cyan);
	gun.setPosition(shape.getPosition().y, shape.getPosition().x);

	sf::RectangleShape particles(sf::Vector2f(10, 10));
	particles.setPosition(gunCenter.x, gunCenter.y - 75);
	particles.setFillColor(sf::Color::White);
	bool shoot = false;

	sf::CircleShape mouseCircle(10);
	mouseCircle.setOrigin(10, 10);
	mouseCircle.setFillColor(sf::Color::Yellow);
	mouseCircle.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	sf::Mouse::setPosition(sf::Vector2i(width / 2, height / 2), window);
	while (window.isOpen())
	{

		localMousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			// on regarde le type de l'évènement...
			switch (event.type)
			{
				// fenêtre fermée
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;

			case::sf::Event::MouseButtonPressed:

			default:
				break;
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			shape.move(-3.f, 0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			shape.move(3.f, 0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			shape.move(0.f, -3.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			shape.move(0.f, 3.f);



		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			shoot = true;
		}
		else
			shoot = false;


		auto angle = atan2((localMousePosition.x - gun.getPosition().x), -(localMousePosition.y - gun.getPosition().y));
		angle = (angle / 3.1415926) * 180;
		gun.setRotation(angle);
		gun.setPosition(shape.getPosition().x, shape.getPosition().y);
		particles.setPosition(localMousePosition);


		mouseCircle.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		window.clear();
		window.draw(shape);
		window.draw(gun);
		//window.draw(mouseCircle);
		if (shoot)
			//window.draw(particles);
		window.display();
	}

	

	return 0;
}

void Shoot() {

}