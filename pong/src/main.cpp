#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
void game(void)
{
        sf::Clock dtc;
    float dt = dtc.getElapsedTime().asSeconds();
    float player_ms = 10000000;
    float ball_ms = 7500000;
    float balld;
    sf::RenderWindow window(sf::VideoMode(1024, 600), "pong");
    sf::RectangleShape player = sf::RectangleShape(sf::Vector2f(40, 100));
    player.setFillColor(sf::Color::White);
    player.setPosition(sf::Vector2f(window.getSize().x - player.getSize().x, (window.getSize().y + player.getSize().y) / 2));
    sf::RectangleShape player2 = sf::RectangleShape(sf::Vector2f(40, 100));
    player2.setFillColor(sf::Color::White);
    player2.setPosition(sf::Vector2f(0, (window.getSize().y + player2.getSize().y) / 2));
    sf::CircleShape pball;
    pball.setRadius(15);
    pball.setFillColor(sf::Color::White);
    pball.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    while(window.isOpen())
    {
        window.setFramerateLimit(60);
        dtc.restart();
        sf::Event eventh;
        while(window.pollEvent(eventh))
        {
            if(eventh.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(player);
        window.draw(player2);
        window.draw(pball);
        window.display();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player.move(sf::Vector2f(0, player_ms * dt));
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player.move(sf::Vector2f(0, -player_ms * dt));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            player2.move(sf::Vector2f(0, -player_ms * dt));
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player2.move(sf::Vector2f(0, player_ms * dt));
        }
        if(player.getPosition().y < 0)
        {
            player.move(sf::Vector2f(0, player_ms * dt));
        }
        else if(player.getPosition().y > window.getSize().y - player.getSize().y)
        {
            player.move(sf::Vector2f(0, -player_ms * dt));
        }
        if(player2.getPosition().y < 0)
        {
            player2.move(sf::Vector2f(0, player_ms * dt));
        }
        else if(player2.getPosition().y > window.getSize().y - player2.getSize().y)
        {
            player2.move(sf::Vector2f(0, -player_ms * dt));
        }
        pball.move(sf::Vector2f(ball_ms * dt, balld * dt));
        if(pball.getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            balld = (rand() % 7500000)- 5000000;
            ball_ms *= -1;
        }
        if(pball.getGlobalBounds().intersects(player2.getGlobalBounds()))
        {
            balld = (rand() % 7500000) - 5000000;
            ball_ms *= -1;
        }
        if(pball.getPosition().y < 0)
        {
            balld *= -1;
        }
        else if(window.getSize().y - pball.getRadius() * 2 < pball.getPosition().y)
        {
            balld *= -1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            pball.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
        }
        if(ball_ms > 0)
        {
            ball_ms += 2500000000 * dt;
        }
        if(ball_ms < 0)
        {
            ball_ms -= 2500000000 * dt;
        }
        if(pball.getPosition().x > window.getSize().x)
        {
            std::cout << "left win" << std::endl;
            window.close();
            game();
        }
        else if(pball.getPosition().x < 0)
        {
            std::cout << "right win" << std::endl;
            window.close();
            game();
        }
    }
}
int main()
{
    game();
}