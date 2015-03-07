#include "Player.h"

void Player::Update(sf::Time *delta)
{
	Entity::Update(delta);
	sf::Vector2f pos = *Entity::GetPosition();

	Entity::SetPosition(&sf::Vector2f(*Common::CheckForEdge(&Entity::GetPosition()->x, &Entity::m_WorldSize.x), Entity::GetPosition()->y));

	CheckVelocity();

	for (size_t shot = 0; shot < mShots.size(); shot++)
	{
		if (mShots.at(shot)->GetActive())
			mShots.at(shot)->Update(delta); //TODO: Shots not always have working collision.
	}

	if (mThrustOn)
		SetThrust();

	if (mShieldOn)
	{
		SetShield();

		if (mShieldDisplayTimer < mClock.getElapsedTime().asSeconds())
			mShieldOn = false;
	}

	mRadar->setPosition(sf::Vector2f(Entity::GetPosition()->x + Entity::GetCollision()->width * 0.45f, Entity::GetPosition()->y * 0.1f + m_WorldSize.y + 55));
}

void Player::Draw(sf::RenderWindow *window)
{
	if (mShieldOn)
		window->draw(*mShieldUnder);

	if (mThrustOn)
		window->draw(*mThrust);

	Entity::Draw(window);

	if (mShieldOn)
		window->draw(*mShieldOver);

	for (size_t shot = 0; shot < mShots.size(); shot++)
	{
		if (mShots.at(shot)->GetActive())
		{
			mShots.at(shot)->Draw(window);
		}
	}
}

void Player::DrawRadar(sf::RenderWindow *window)
{
	window->draw(*mRadar);
}

void Player::Initialize(sf::Texture *Texture, sf::Texture *RadarTexture, sf::Texture *ShotTexture, sf::Texture *ThrustTexture, sf::Texture *ShieldOverTexture, sf::Texture *ShieldUnderTexture,
	sf::Vector2u WindowSize, sf::Vector2f WorldBounds)
{
	Entity::Initialize(Texture, WindowSize, WorldBounds);
	mTextureSize = sf::Vector2f(Texture->getSize());
	mShieldOver->setTexture(*ShieldOverTexture);
	mShieldUnder->setTexture(*ShieldUnderTexture);
	mThrust->setTexture(*ThrustTexture);
	mRadar->setTexture(*RadarTexture);
	mThrustTextureSize = sf::Vector2f(ThrustTexture->getSize());
	mThrustOn = false;
	mFlipped = false;
	SetPosition(&sf::Vector2f(640.0f - Entity::GetCollision()->width / 2, 300.0f));
	sf::Vector2f pos = *GetPosition();
	m_ShotTexture = ShotTexture;
	m_Active = true;
	mShieldDisplayTimerAmount = 0.15f;
	mMaxVol.y = 100;
	mMaxVol.x = 500;
	mShots.clear();
}

void Player::Events(sf::Event *event)
{
	if (event->type == sf::Event::KeyPressed)
	{
		if (event->key.code == sf::Keyboard::Left)
		{
			m_Acceleration.x = -10.f;
			mAccelerating = true;
			mThrustOn = true;

			if (!mFlipped) //Takes two taps of key to thrust, one to flip, one to thrust.
			{// Flip sprite backwards.
				sf::Sprite temp = *Entity::GetSprite();
				temp.setTextureRect(sf::IntRect(int(mTextureSize.x), 0, int(-mTextureSize.x), int(mTextureSize.y)));
				Entity::SetSprite(&temp);
				mThrust->setTextureRect(sf::IntRect(int(mThrustTextureSize.x), 0, int(-mThrustTextureSize.x), int(mThrustTextureSize.y)));
				mFlipped = true;
			}

			SetThrust();
		}
		
		if (event->key.code == sf::Keyboard::Right)
		{
			m_Acceleration.x = 10.f;
			mAccelerating = true;
			mThrustOn = true;

			if (mFlipped) //Takes two taps of key to thrust, one to flip, one to thrust.
			{// Flip sprite back normal.
				sf::Sprite temp = *Entity::GetSprite();
				temp.setTextureRect(sf::IntRect(0, 0, int(mTextureSize.x), int(mTextureSize.y)));
				Entity::SetSprite(&temp);
				mThrust->setTextureRect(sf::IntRect(0, 0, int(mThrustTextureSize.x), int(mThrustTextureSize.y)));
				mFlipped = false;
			}

			SetThrust();
		}

		if (event->key.code == sf::Keyboard::Up)
		{
			m_Acceleration.y = -10;
			mAltitude = true;
		} 
		
		if (event->key.code == sf::Keyboard::Down)
		{
			m_Acceleration.y = 10;
			mAltitude = true;
		}

		if (event->key.code == sf::Keyboard::LControl)
		{
			FireShot();
		}
	}
	else if (event->type == sf::Event::KeyReleased)
	{
		if (event->key.code == sf::Keyboard::Right || event->key.code == sf::Keyboard::Left)
		{
			m_Acceleration.x = 0;
			mAccelerating = false;
			mThrustOn = false;
		}

		if (event->key.code == sf::Keyboard::Up || event->key.code == sf::Keyboard::Down)
		{
			m_Acceleration.y = 0;
			mAltitude = false;
		}
	}
}

size_t Player::ShotCount(void)
{
	return mShots.size();
}

bool Player::ShotActive(size_t shot)
{
	return mShots.at(shot)->GetActive();
}

sf::Vector2f *Player::ShotPosition(size_t shot)
{
	return mShots.at(shot)->GetPosition();
}

sf::FloatRect *Player::ShotCollision(size_t shot)
{
	return mShots.at(shot)->GetCollision();
}

void Player::ShotHit(size_t shot)
{
	mShots.at(shot)->Hit();
}

void Player::PlayerHit(void)
{
	mShieldDisplayTimer = mShieldDisplayTimerAmount + mClock.getElapsedTime().asSeconds();
	mShieldOn = true;
	SetShield();
}

Player::Player()
{
	mThrust = new sf::Sprite();
	mShieldUnder = new sf::Sprite();
	mShieldOver = new sf::Sprite();
	mRadar = new sf::Sprite();
}

void Player::SetShield(void)
{
	sf::Vector2f position = *Entity::GetPosition();
	mShieldOver->setPosition(position.x - 20, position.y - 10);
	mShieldUnder->setPosition(position.x - 20, position.y - 10);
}

void Player::SetThrust(void)
{
	sf::Vector2f position;
	sf::Vector2f atPosition = *Entity::GetPosition();

	if (mFlipped)
	{		
		position.x = atPosition.x - Entity::GetSprite()->getTextureRect().width - 20.0f;
	}
	else
	{
		position.x = atPosition.x - Entity::GetSprite()->getTextureRect().width + 50.0f;
	}

	position.y = atPosition.y;
	mThrust->setPosition(position);
}

void Player::FireShot(void)
{
	bool spawnShot = true;
	int shotNumber;
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f atPosition = *Entity::GetPosition();
	velocity.y = m_Velocity.y * 0.25f;
	position.y = atPosition.y + 15.0f;

	if (mFlipped)
	{
		velocity.x = (m_Velocity.x * 0.75f) - 750.0f;
		position.x = atPosition.x + (Entity::GetSprite()->getTextureRect().width * -1) - 40.0f;
	}
	else
	{
		velocity.x = (m_Velocity.x * 0.75f) + 750.0f;
		position.x = atPosition.x + 20.0f;
	}

	for (size_t shot = 0; shot < mShots.size(); shot++)
	{
		if (!mShots.at(shot)->GetActive())
		{			
			spawnShot = false;
			shotNumber = shot;
		}
	}

	if (spawnShot)
	{
		mShots.push_back(std::unique_ptr<PlayerShot>(new PlayerShot()));
		shotNumber = mShots.size() - 1;
		mShots.at(shotNumber)->Initialize(m_ShotTexture, m_WindowSize, m_WorldSize);
	}

	mShots.at(shotNumber)->Fire(position, velocity);
}

void Player::CheckVelocity(void)
{
	sf::Vector2f atPosition = *Entity::GetPosition();

	if (m_Velocity.x > mMaxVol.x)
		m_Velocity.x = mMaxVol.x;

	if (m_Velocity.x < -mMaxVol.x)
		m_Velocity.x = -mMaxVol.x;

	if (m_Velocity.y > mMaxVol.y)
		m_Velocity.y = mMaxVol.y;

	if (m_Velocity.y < -mMaxVol.y)
		m_Velocity.y = -mMaxVol.y;

	if (atPosition.y > float(m_WindowSize.y - 90))
	{
		Entity::SetPosition(&sf::Vector2f(atPosition.x, float(m_WindowSize.y - 90)));
		m_Acceleration.y = 0.f;
		m_Velocity.y = 0.f;
	}

	if (atPosition.y < 60.f)
	{
		Entity::SetPosition(&sf::Vector2f(atPosition.x, 60.f));
		m_Acceleration.y = 0.f;
		m_Velocity.y = 0.f;
	}

	if (!mAltitude)
	{
		if (m_Velocity.y > 5.f)
			m_Acceleration.y = -5.f;
		else if (m_Velocity.y > 0.1f)
			m_Acceleration.y = -0.1f;
		else if (m_Velocity.y > 0.05f)
		{
			m_Acceleration.y = 0;
			mAltitude = true;
		}

		if (m_Velocity.y < -5)
			m_Acceleration.y = 5;
		else if (m_Velocity.y < -0.1f)
			m_Acceleration.y = 0.1f;
		else if (m_Velocity.y < -0.05f)
		{
			m_Acceleration.y = 0;
			mAltitude = true;
		}
	}

	if (!mAccelerating)
	{
		if (m_Velocity.x > 1.f)
		{
			m_Acceleration.x = -1.f;
		}
		else if (m_Velocity.x > 0.1f)
		{
			m_Acceleration.x = -0.1f;
		}
		else if (m_Velocity.x > 0.05f)
		{
			m_Acceleration.x = 0.f;
			mAccelerating = true;
		}

		if (m_Velocity.x < -1.f)
		{
			m_Acceleration.x = 1.f;
		}
		else if (m_Velocity.x < -0.1f)
		{
			m_Acceleration.x = 0.1f;
		}
		else if (m_Velocity.x < -0.05f)
		{
			m_Acceleration.x = 0.f;
			mAccelerating = true;
		}
	}
}