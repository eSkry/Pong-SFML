#include "gamemenu.h"

GameMenu::GameMenu(sf::Vector2i windowSize, sf::RenderWindow &window){
    this->windowSize = windowSize;
    bgTexture.loadFromFile("source/background.png");
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale((windowSize.x / 50.f) * 50, (windowSize.y / 50.f) * 50);
    drawHelp = false;

    fontMenu.loadFromFile("source/font/stan0753.ttf");

    btTextStart = new sf::Text("Start", fontMenu, 20);
    btTextStart->setPosition(20, 50);

    btTextHelp = new sf::Text("Help", fontMenu, 20);
    btTextHelp->setPosition(20, 75);

    btTextExit = new sf::Text("Exit", fontMenu, 20);
    btTextExit->setPosition(20, 100);

    btTextBack = new sf::Text("Back", fontMenu, 20);
    btTextBack->setPosition(windowSize.x - (50+40), windowSize.y - 50);

    helpText = new sf::Text("Help:\n"
                            "Player 1: W - UP, S - DOWN\n"
                            "Player 2: Arrow UP - UP, Arrow DOWN - DOWN\n"
                            "Space - Start ball", fontMenu, 20);
    helpText->setPosition(20, 20);

    // Visual
    visualLine = new MyLines(&window, 80, windowSize);
}

GameMenu::~GameMenu(){
    delete btTextStart;
    delete btTextExit;
    delete btTextHelp;
    delete btTextBack;
    delete helpText;
    delete visualLine;
}

void GameMenu::update(sf::RenderWindow &window){
    sf::Vector2i mousePixel;

    float time;
    sf::Clock clock;
    while(window.isOpen()){
        time = clock.getElapsedTime().asMicroseconds();
        time /= 800;
        clock.restart();

        mousePixel = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

            //if (event.key.code == sf::Keyboard::Escape)
                //window.close();
        }

        if (!drawHelp){
            // START
            if (btTextStart->getGlobalBounds().contains(mousePixel.x, mousePixel.y)){
                btTextStart->setColor(sf::Color::Green);
                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.key.code == sf::Mouse::Left)
                        break;
                }
            } else {
                btTextStart->setColor(sf::Color::White);
            }

            // HELP
            if (btTextHelp->getGlobalBounds().contains(mousePixel.x, mousePixel.y)){
                btTextHelp->setColor(sf::Color::Yellow);
                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.key.code == sf::Mouse::Left){
                        drawHelp = true;
                    }
                }

            } else {
                btTextHelp->setColor(sf::Color::White);
            }

            // EXIT
            if (btTextExit->getGlobalBounds().contains(mousePixel.x, mousePixel.y)){
                btTextExit->setColor(sf::Color::Red);
                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.key.code == sf::Mouse::Left){
                        window.close();
                    }
                }
            } else {
                btTextExit->setColor(sf::Color::White);
            }
        } else {
            // BACK
            if (btTextBack->getGlobalBounds().contains(mousePixel.x, mousePixel.y)){
                btTextBack->setColor(sf::Color::Magenta);
                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.key.code == sf::Mouse::Left){
                        drawHelp = false;
                    }
                }
            } else {
                btTextBack->setColor(sf::Color::White);
            }
        }

        window.clear();
        drawMenu(window);
        visualLine->update(time);
        window.display();
    }
}

void GameMenu::drawMenu(sf::RenderWindow &window) const{
    window.draw(bgSprite);
    if (!drawHelp){
        window.draw(*btTextStart);
        window.draw(*btTextExit);
        window.draw(*btTextHelp);
    } else {
        window.draw(*btTextBack);
        window.draw(*helpText);
    }
}



