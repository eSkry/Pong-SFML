#include "player.h"

Player::Player(sf::Texture &texture, sf::Vector2f pos, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey){
    this->texture = &texture;
    this->position = pos;
    this->playerSprite.setTexture(texture);
    //this->playerSprite.setOrigin( this->texture->getSize().x / 2, this->texture->getSize().y / 2 );
    this->playerSprite.setPosition(position);
    this->upKey = upKey;
    this->downKey = downKey;
    this->speed = 0.18f;
    dirPlr = Direction::NONE;
}

Player::Direction Player::getDir(){
    return dirPlr;
}

void Player::update(float time){
    Mooving(time);
}

sf::Sprite& Player::getSprite(){
    return this->playerSprite;
}

void Player::Mooving(float time){
    if (sf::Keyboard::isKeyPressed(upKey)){
        if (position.y >= 50){
                dirPlr = UP;
                position.y -= time*speed;
        } else {
            position.y += 50 - position.y;
        }
    }
    if (sf::Keyboard::isKeyPressed(downKey)){
        if (position.y + playerSprite.getGlobalBounds().height <= 470){
                dirPlr = DOWN;
                position.y += time*speed;
        } else {
            position.y -= position.y - (470 - playerSprite.getGlobalBounds().height);
        }
    }

    this->playerSprite.setPosition(position);
}

void Player::reset(sf::Vector2f pos){
    position = pos;
    playerSprite.setPosition(position);
}
