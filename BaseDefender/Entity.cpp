#include "Entity.h"

void Entity::Update(sf::Time *delta)
{
	if (m_Active)
	{
		//Calculate movement this frame according to velocity and acceleration.
		m_Velocity += m_Acceleration;
		*m_Position += (m_Velocity * delta->asSeconds());
		//Calculate rotation this frame according to velocity and acceleration.
		m_Rotation.Velocity += m_Rotation.Acceleration;
		m_Rotation.Amount += (m_Rotation.Velocity * delta->asSeconds());
		m_Sprite->setPosition(*m_Position);
		UpdateCollusionPosition();
	}
}

void Entity::UpdateCollusionPosition(void)
{
	m_Collusion->left = m_Sprite->getPosition().x;
	m_Collusion->top = m_Sprite->getPosition().y;
}

void Entity::Draw(sf::RenderWindow *window)
{
	if (m_Active)
	{
		window->draw(*m_Sprite);
	}
}

void Entity::DrawOtherSide(sf::RenderWindow *window)
{
	if (m_Active)
	{
		if (m_Position->x < 1.0f || m_Position->x > m_WorldSize.x - m_Collusion->width)
		{
			m_Sprite->setPosition(m_Position->x - m_WorldSize.x, m_Position->y);
			window->draw(*m_Sprite);
		}
	}
}

Entity::Entity(void)
{
	m_Sprite = new sf::Sprite();
	m_Position = new sf::Vector2f(0, 0);
	m_Collusion = new sf::FloatRect(0, 0, 0, 0);
}

void Entity::Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	m_WindowSize = windowSize;
	m_WorldSize = worldSize;
	
	if (texture != NULL)
	{
		texture->setSmooth(true);
		m_Sprite->setTexture(*texture);
		m_Collusion->height = float(texture->getSize().y);
		m_Collusion->width = float(texture->getSize().x);
	}

	m_Active = false;
}

bool Entity::GetActive(void)
{
	return m_Active;
}

sf::Vector2f *Entity::GetPosition(void)
{
	return m_Position;
}

sf::Vector2f *Entity::GetVelocity(void)
{
	return &m_Velocity;
}

sf::Vector2f *Entity::GetAcceleration(void)
{
	return &m_Acceleration;
}

Rotation Entity::GetRotation(void)
{
	return m_Rotation;
}

sf::FloatRect *Entity::GetCollision(void)
{
	return m_Collusion;
}

sf::Sprite *Entity::GetSprite(void)
{
	return m_Sprite;
}

void Entity::SetActive(bool active)
{
	m_Active = active;
}

void Entity::SetPosition(sf::Vector2f *position)
{	
	*m_Position = sf::Vector2f(*position);
	m_Sprite->setPosition(*position);
}

void Entity::SetVelocity(sf::Vector2f *velocity)
{
	m_Velocity = *velocity;
}

void Entity::SetAcceleration(sf::Vector2f *acceleration)
{
	m_Acceleration = *acceleration;
}

void Entity::SetRotation(Rotation *rotation)
{
	m_Rotation = *rotation;
}

void Entity::SetScale(float *scale)
{
	m_Scale = *scale;
}

void Entity::SetSprite(sf::Sprite *sprite)
{
	sf::Sprite temp = *sprite;
	*m_Sprite = temp;
	m_Sprite->setPosition(*m_Position);
}

void Entity::SetTexture(sf::Texture *texture)
{
	if (texture != NULL)
	{
		texture->setSmooth(true);
		m_Sprite->setTexture(*texture);
		m_Collusion->height = float(texture->getSize().y);
		m_Collusion->width = float(texture->getSize().x);
	}
}