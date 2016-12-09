#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Graphics.hpp>

#include "lines.h"

class GameMenu{
public:
    GameMenu(sf::Vector2i windowSize, sf::RenderWindow &window);
    ~GameMenu();

    void update(sf::RenderWindow &window);

private:
    // Text properties
    sf::Font fontMenu;
    sf::Text *btTextStart;
    sf::Text *btTextExit;
    sf::Text *btTextHelp;
    sf::Text *btTextBack;

    sf::Text *helpText;

    // Bg properties
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    sf::Vector2i windowSize;

    // Methods
    void drawMenu(sf::RenderWindow &window) const;

    // Drawing properties
    bool drawHelp;

    // Visual effects
    MyLines *visualLine;
};

#endif // GAMEMENU_H
