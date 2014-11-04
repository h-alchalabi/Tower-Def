#include "Entity.h"
#include <SFML\Graphics\Rect.hpp>
#include <string>

Entity::Entity(){
	// do nothing
}
void Entity::setEntityImage(std::string path){
	entityTexture.loadFromFile(path);
	entitySprite.setTexture(entityTexture);
}
void Entity::handleCollision(Entity& e){
	// function to be overrriden in child classes. (Critters and Towers and Projectiles)
}
// Returns the pointer to the Entity's hitbox.
sf::Rect<float>* Entity::getHitbox(){
	sf::Rect<float>* hitbox = new sf::Rect<float>(this->entitySprite.getPosition().x, this->entitySprite.getPosition().y, this->entityTexture.getSize().x, this->entityTexture.getSize().y);
	return hitbox;
}
sf::Sprite Entity::getSprite(){
	return this->entitySprite;
}
float Entity::getX() const{
	return this->x;
}
float Entity::getY() const{
	return this->y;
}
float Entity::getCenterX() const{
	return this->centerX;
}
float Entity::getCenterY() const{
	return this->centerY;
}
void Entity::setPostion(float newX, float newY){
	this->x = newX;
	this->y = newY;
	this->centerX = newX + (this->entitySprite.getLocalBounds().width / 2);
	this->centerY = newY + (this->entitySprite.getLocalBounds().height / 2);
}
void Entity::setCenterPostion(float newCenterX, float newCenterY){
	this->centerX = newCenterX;
	this->centerY = newCenterY;
	this->x = newCenterX - (this->entitySprite.getLocalBounds().width / 2);
	this->y = newCenterY - (this->entitySprite.getLocalBounds().height / 2);
}