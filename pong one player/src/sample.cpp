#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <unistd.h>
void game(void)
{
    sf::Clock dtc;
    float dt = dtc.getElapsedTime().asSeconds();
    float player_ms = 10000000;
    float ball_ms = 7500000;
    float balld;
    sf::RenderWindow window(sf::VideoMode(1366, 768), "pong");
    sf::Texture player_tex;
    sf::Sprite player;
    player_tex.loadFromFile("images/plate.png");
    player.setPosition(sf::Vector2f(window.getSize().x - player_tex.getSize().x * 3, (window.getSize().y + player_tex.getSize().y) / 2));
    sf::Texture player2_tex;
    sf::Sprite player2;
    player2_tex.loadFromFile("images/plate.png");
    player2.setPosition(sf::Vector2f(player2_tex.getSize().x * 3, (window.getSize().y + player2_tex.getSize().y) / 2));
    sf::Texture pball_tex;
    sf::Sprite pball;
    pball_tex.loadFromFile("images/pball.png");
    pball.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    player.setTexture(player_tex);
    player2.setTexture(player2_tex);
    pball.setTexture(pball_tex);
    pball.setScale(2, 2);
    player.setScale(3, 3);
    player2.setScale(-3, -3);
    sf::Texture background_tex;
    background_tex.loadFromFile("images/background.png");
    sf::Sprite background;
    background.setTexture(background_tex);
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
        window.draw(background);
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
        if(player.getPosition().y < 0)
        {
            player.move(sf::Vector2f(0, player_ms * dt));
        }
        else if(player.getPosition().y > window.getSize().y - player_tex.getSize().y * 3 + 1)
        {
            player.move(sf::Vector2f(0, -player_ms * dt));
        }
        if(player2.getPosition().y < player2_tex.getSize().y * 3)
        {
            player2.move(sf::Vector2f(0, player_ms * dt));
        }
        else if(player2.getPosition().y > window.getSize().y - 0)
        {
            player2.move(sf::Vector2f(0, -player_ms * dt));
        }
        pball.move(sf::Vector2f(ball_ms * dt, balld * dt));
        if(pball.getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            balld = (rand() % 20000000)- 9000000;
            ball_ms *= -1;
        }
        if(pball.getGlobalBounds().intersects(player2.getGlobalBounds()))
        {
            balld = (rand() % 20000000) - 9000000;
            ball_ms *= -1;
        }
        if(pball.getPosition().y < 0)
        {
            balld *= -1;
        }
        else if(window.getSize().y - pball_tex.getSize().y * 2 < pball.getPosition().y)
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
            std::cout << "left win" << std::endl;;
            window.close();
            game();
        }
        else if(pball.getPosition().x < 0)
        {
            std::cout << "right win" << std::endl;
            window.close();
            game();
        }
        if(pball.getPosition().x < window.getSize().x - window.getSize().x / 3.5)
        {
            if(player2.getPosition().y + player2_tex.getSize().y / 2 < pball.getPosition().y + pball_tex.getSize().y / 2 + 80)
            {
                player2.move(sf::Vector2f(0, player_ms * dt * 0.75));
            }
            else if(player2.getPosition().y + player2_tex.getSize().y / 2 > pball.getPosition().y + pball_tex.getSize().y / 2 - 80)
            {
                player2.move(sf::Vector2f(0, player_ms * dt * -0.75));
            }
        }
        // background.setScale(sf::Vector2f(window.getSize().x / background_tex.getSize().x,window.getSize().y / background_tex.getSize().y));
    background.setScale((float)window.getSize().x / background_tex.getSize().x, (float)window.getSize().y / background_tex.getSize().y);
    }
}
int main()
{
    game();
}
