#ifndef ENTITY_H
#define ENTITY_H
#include "Common.h"
#include "Header.h"

struct Rotation
{
	float Amount;
	float Velocity;
	float Acceleration;
};

class Entity :
	public Common
{
private:
	sf::Sprite *m_Sprite;
	sf::Vector2f *m_Position;
	sf::FloatRect *m_Collusion;

protected:
	sf::Vector2u m_WindowSize;
	sf::Vector2f m_WorldSize;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Acceleration;
	Rotation m_Rotation;
	float m_Scale;
	bool m_Active;

	bool CheckForXEdge(void);
	bool CheckForYEdge(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void UpdateCollusionPosition(void);
	void SetTexture(sf::Texture *texture);

public:
	Entity(void);
	void Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize);

	bool GetActive(void);
	float GetRadius(void);
	Rotation GetRotation(void);
	sf::Vector2f *GetPosition(void);
	sf::Vector2f *GetVelocity(void);
	sf::Vector2f *GetAcceleration(void);
	sf::FloatRect *GetCollision(void);
	sf::Sprite *GetSprite(void);

	void SetActive(bool Active);
	void SetPosition(sf::Vector2f *Position);
	void SetVelocity(sf::Vector2f *Velocity);
	void SetAcceleration(sf::Vector2f *Acceleration);
	void SetRotation(Rotation *Rotation);
	void SetScale(float *Scale);
	void SetSprite(sf::Sprite *sprite);
};

#endif