#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player{
public:
    Player(sf::Texture &texture, sf::Vector2f pos, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);

    void update(float time);
    void reset(sf::Vector2f pos);

    sf::Sprite& getSprite();

    enum Direction{
        NONE,
        UP,
        DOWN
    };

    Direction getDir();

private:
    float speed;
    Direction dirPlr;

    sf::Texture *texture;
    sf::Sprite playerSprite;

    sf::Vector2f position;

    sf::Keyboard::Key upKey;
    sf::Keyboard::Key downKey;

    void Mooving(float time);
};

#endif // PLAYER_H
