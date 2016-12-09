#include "ball.h"

Ball::Ball(Texture &texture, Vector2f pos){
    position = pos;
    ballTexture = new Texture(texture);
    ballSprite.setTexture(*ballTexture);
    ballSprite.setOrigin(ballTexture->getSize().x / 2, ballTexture->getSize().y / 2);
    ballSprite.setScale(0.5, 0.5);
    ballSprite.setPosition(position);
    HSpeed = 0.27;
    VSpeed = 0.25;

    VDir = VDirection::VNONE;
    HDir = HDirection::HNONE;
}

Ball::~Ball(){
    delete ballTexture;
}

void Ball::update(float &time, Player &pl1, Player &pl2, Wall &wallUp, Wall &wallDown, Wall &left, Wall &right, unsigned short &one, unsigned short &two){

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if (VDir == VNONE && HDir == HNONE){
            randomDir();
        }
    }

    ////// PLAYER //////
    if (ballSprite.getGlobalBounds().intersects(pl1.getSprite().getGlobalBounds())){
        HDir = RIGHT;

        if (VDir == UP){
            VDir = UP;
        } else {
            VDir = DOWN;
        }

    }
    if (ballSprite.getGlobalBounds().intersects(pl2.getSprite().getGlobalBounds())){
        HDir = LEFT;

        if (VDir == UP){
            VDir = UP;
        } else {
            VDir = DOWN;
        }
    }
    ////// PLAYER //////
    ////// WALL //////

    if (VDir == UP){
        if (ballSprite.getGlobalBounds().intersects(wallUp.getSprite().getGlobalBounds())){
            VDir = DOWN;
        }
    } else if (VDir == DOWN){
        if (ballSprite.getGlobalBounds().intersects(wallDown.getSprite().getGlobalBounds())){
            VDir = UP;
        }
    }

    if (ballSprite.getGlobalBounds().intersects(left.getSprite().getGlobalBounds())){
        position = sf::Vector2f(780 / 2, 480 / 2);
        HDir = HNONE;
        VDir = VNONE;
        one++;
    }
    if (ballSprite.getGlobalBounds().intersects(right.getSprite().getGlobalBounds())){
        position = sf::Vector2f(780 / 2, 480 / 2);
        HDir = HNONE;
        VDir = VNONE;
        two++;
    }
    ////// WALL //////
    if (HDir == HDirection::LEFT){
        position.x -= HSpeed*time;
    } else if (HDir == HDirection::RIGHT){
        position.x += HSpeed*time;
    }

    if (VDir == VDirection::UP){
        position.y -= VSpeed*time;
    } else if (VDir == VDirection::DOWN){
        position.y += VSpeed*time;
    }
    ballSprite.setPosition(position);
}

Sprite& Ball::getSprite(){
    return ballSprite;
}

void Ball::randomDir(){
    bool temp = rand()%2;
    if(temp){
        VDir = UP;
    } else {
        VDir = DOWN;
    }
    temp = rand()%2;
    if (temp){
        HDir = RIGHT;
    } else {
        HDir = LEFT;
    }
}

void Ball::reset(Vector2f pos){
    position = pos;
    ballSprite.setPosition(position);
    HDir = HNONE;
    VDir = VNONE;
}













