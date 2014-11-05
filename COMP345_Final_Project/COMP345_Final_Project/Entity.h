#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <string>
class Entity{
public:
	Entity(); 
	virtual void handleCollision(Entity& e) = 0;
	sf::Rect<float>* getHitbox();
	sf::Sprite getSprite();
	void setEntityImage(std::string path);
	float getX() const;
	float getY() const;
	float getCenterX() const;
	float getCenterY() const;
	void setPostion(float newX, float newY);
	void setCenterPostion(float newCenterX, float newCenterY);
private:
	/*top right coordinates of entity*/
	float x, y;
	/*coordinates of the center of the entity*/
	float centerX, centerY;
	std::string entityPath;
	sf::Texture entityTexture;
	sf::Sprite entitySprite;
};

#endif // ENTITY_H
