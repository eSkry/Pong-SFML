#include <SFML/Graphics.hpp>

#include <sstream>

#include "gamemenu.h"
#include "player.h"
#include "lines.h"
#include "ball.h"
#include "wall.h"

using namespace sf;

int main(){
    Vector2i windowSize;
    windowSize.x = 780;
    windowSize.y = 480;

    RenderWindow window(VideoMode(windowSize.x, windowSize.y), "Pong");
    window.setFramerateLimit(60);

    unsigned short scoreLeft = 0, scoreRight = 0;

    MyLines visualLines(&window, 80, windowSize);

    Font pixFont;
    pixFont.loadFromFile("source/font/stan0753.ttf");
    Text btMenuText("Menu", pixFont, 20);
    btMenuText.setPosition(windowSize.x - 80, 8);
    Text leftScore("", pixFont, 100);
    leftScore.setColor(Color::Black);
    leftScore.setPosition(windowSize.x / 2 + 150, windowSize.y / 2 - 35);
    Text rightScore("", pixFont, 100);
    rightScore.setColor(Color::Black);
    rightScore.setPosition(windowSize.x / 2 - 200, windowSize.y / 2 - 35);

    // Menu
    GameMenu menu(windowSize, window);
    menu.update(window);

    Texture bgTexture;
    bgTexture.loadFromFile("source/background.png");
    Sprite bgSprite(bgTexture);
    bgSprite.setScale((windowSize.x / 50.f) * 50, (windowSize.y / 50.f) * 50);

    //Players
    Texture playerTexture;
    playerTexture.loadFromFile("source/Player.png");

    Vector2f playerPos(20, windowSize.y / 2.f - playerTexture.getSize().y / 2 + 20);

    Player playerOne(playerTexture, playerPos, Keyboard::W, Keyboard::S);
    Player playerTwo(playerTexture, Vector2f(windowSize.x - 40, playerPos.y), Keyboard::Up, Keyboard::Down);

    //Ball
    Texture textureBall;
    textureBall.loadFromFile("source/Ball.png");
    Ball ball(textureBall, Vector2f( windowSize.x / 2, windowSize.y / 2 + 20));

    // Walls
    Texture wallHtex;
    wallHtex.loadFromFile("source/HWall.png");
    Texture wallVtex;
    wallVtex.loadFromFile("source/VWall.png");
    Texture panelTextr;
    panelTextr.loadFromFile("source/panel.png");
    Wall wallUp(wallHtex, Vector2f(0, panelTextr.getSize().y), Vector2f((windowSize.x / wallHtex.getSize().x) * wallHtex.getSize().x, 1), true);
    Wall wallDown(wallHtex, Vector2f(0, windowSize.y - wallHtex.getSize().y), Vector2f((windowSize.x / wallHtex.getSize().x) * wallHtex.getSize().x, 1), true);
    Wall wallLeft(wallVtex, Vector2f(0, wallHtex.getSize().y), Vector2f(1, (windowSize.y / wallVtex.getSize().y) * wallVtex.getSize().y - wallHtex.getSize().y), false);
    Wall wallRight(wallVtex, Vector2f(windowSize.x - wallVtex.getSize().x , wallHtex.getSize().y), Vector2f(1, (windowSize.y / wallVtex.getSize().y) * wallVtex.getSize().y - wallHtex.getSize().y), false);

    //Panel
    Wall Panel(panelTextr, Vector2f(0,0), Vector2f((windowSize.x / panelTextr.getSize().x) * panelTextr.getSize().x, 1));

    //Central line
    Wall centralLine(wallVtex, Vector2f(windowSize.x / 2 - wallVtex.getSize().x / 2, panelTextr.getSize().y + wallHtex.getSize().y),
                     Vector2f(1, (windowSize.y / wallVtex.getSize().y) * wallVtex.getSize().y - (panelTextr.getSize().y + wallHtex.getSize().y)));
    centralLine.getSprite().setColor(Color::Red);

    Vector2i mousePix;
    std::ostringstream ostr;

    float time;
    Clock clock;
    while(window.isOpen()){
        time = clock.getElapsedTime().asMicroseconds();
        time /= 800;
        clock.restart();

        ostr << scoreLeft;
        leftScore.setString(ostr.str());
        ostr.str("");
        ostr.clear();
        ostr << scoreRight;
        rightScore.setString(ostr.str());
        ostr.str("");
        ostr.clear();

        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();

            if (event.key.code == sf::Keyboard::Escape)
                menu.update(window);
        }

        mousePix = Mouse::getPosition(window);

        if (scoreRight == 3 || scoreLeft == 3){
            playerOne.reset(playerPos);
            playerTwo.reset(Vector2f(windowSize.x - 40, playerPos.y));
            ball.reset(Vector2f(windowSize.x / 2, windowSize.y / 2));
            scoreRight = 0;
            scoreLeft = 0;
        }

        if (btMenuText.getGlobalBounds().contains(mousePix.x, mousePix.y)){
            if (event.type == Event::MouseButtonPressed){
                if (event.key.code == Mouse::Left){
                    scoreRight = 0;
                    scoreLeft = 0;
                    playerOne.reset(playerPos);
                    playerTwo.reset(Vector2f(windowSize.x - 40, playerPos.y));
                    ball.reset(Vector2f(windowSize.x / 2, windowSize.y / 2));
                    menu.update(window);
                }
            }
            btMenuText.setColor(Color::Green);
        } else {
            btMenuText.setColor(Color::White);
        }

        playerOne.update(time);
        playerTwo.update(time);
        ball.update(time, playerOne, playerTwo, wallUp, wallDown, wallLeft, wallRight, scoreLeft, scoreRight);

        window.clear();
        window.draw(bgSprite);
        visualLines.update(time);
        window.draw(playerOne.getSprite());
        window.draw(playerTwo.getSprite());
        window.draw(wallUp.getSprite());
        window.draw(wallLeft.getSprite());
        window.draw(wallRight.getSprite());
        window.draw(Panel.getSprite());
        window.draw(centralLine.getSprite());
        window.draw(wallDown.getSprite());
        window.draw(leftScore);
        window.draw(rightScore);
        window.draw(ball.getSprite());
        window.draw(btMenuText);
        window.display();
    }

    return 0;
}
