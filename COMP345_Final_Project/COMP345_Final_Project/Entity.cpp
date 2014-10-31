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