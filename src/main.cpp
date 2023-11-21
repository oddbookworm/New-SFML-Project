#include <SFML/Graphics.hpp>
#include <cstdio>
#include <iostream>
#include <string>

#include "ErrorLogger.h"
#include "ResourceManager.h"

int main()
{
    TRACE("TRACE");
    DEBUG("DEBUG");
    WARN("WARN");
    ERROR("ERROR");
    FATAL(std::string("FATAL"));

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    std::weak_ptr<sf::SoundBuffer> buf;
    Utils::ResourceManager::getInstance().getSound("Test.mp3", buf);
    sf::Sound sound(*buf.lock().get());
    sound.play();

    std::weak_ptr<sf::Texture> tex;
    Utils::ResourceManager::getInstance().getTexture("Test.png", tex);
    sf::Sprite sprite(*tex.lock().get());
    sprite.setScale(sf::Vector2f(0.5, 0.5));

    std::weak_ptr<sf::Font> font;
    Utils::ResourceManager::getInstance().getFont("DotGothic16-Regular.ttf", font);
    sf::Text myText;
    myText.setFont(*font.lock());
    myText.setString("Hello World!");
    myText.setCharacterSize(30);
    myText.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(sprite);
        window.draw(myText);
        window.display();
    }

    return 0;
}