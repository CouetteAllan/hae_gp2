#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    window.setVerticalSyncEnabled(true);
    sf::Vector2u size = window.getSize();
    float width = size.x;
    float height = size.y;



    sf::RectangleShape shape(sf::Vector2f(40,80));
    sf::Vector2f center;
    center.x = shape.getSize().x / 2;
    center.y = shape.getSize().y / 2;
    shape.setOrigin(center);
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(10);
    shape.setOutlineColor(sf::Color::Magenta);
    shape.setPosition(width/2, height/2);
    
    sf::Mouse::setPosition(sf::Vector2i(width / 2, height / 2),window);
    while (window.isOpen())
    {
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
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;

            case::sf::Event::MouseButtonPressed:

            default:
                break;
            }
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
            shape.move(-3.f, 0.f);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
            shape.move(3.f, 0.f);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
            shape.move(0.f, -3.f);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
            shape.move(0.f, 3.f);
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f localPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
            sf::RectangleShape particles(localPosition);
            window.draw(particles);
        }
            


        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}