//Common class for enemy that starts out as Angreifer.
#ifndef EnemyGraphics_H
#define EnemyGraphics_H
#include "Entity.h"

class EnemyGraphics 
	: public Entity
{
public:
	EnemyGraphics();
	~EnemyGraphics();


protected:
	void Update(sf::Time *Delta);
	void Draw(sf::RenderWindow *Window);
	void Initialize(sf::Texture *Texture, sf::Vector2u WindowSize, sf::Vector2f WorldBounds);

private:
	sf::Sprite mShip;	
};

#endif