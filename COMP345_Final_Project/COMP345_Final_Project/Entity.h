#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <string>
class Entity{
public:
	Entity(); 
	void handleCollision(Entity& e);
	sf::Rect<float>* getHitbox();
	sf::Sprite getSprite();
	void setEntityImage(std::string path);
private:
	std::string entityPath;
	sf::Texture entityTexture;
	sf::Sprite entitySprite;
};

#endif // ENTITY_H
