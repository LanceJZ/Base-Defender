#include "Game.h"

ResourceHolder<sf::Texture, Textures::ID> mTextures;

//std::unique_ptr<Player> pPlayer(new Player);
std::shared_ptr<Player> pPlayer(new Player);
std::shared_ptr<Cities> pCities(new Cities);
std::unique_ptr<Background> pBackground(new Background);
std::unique_ptr<Overlay> pOverlay(new Overlay);
std::unique_ptr<Radar> pRadar(new Radar);
std::unique_ptr<EnemySpawner> pSpawner(new EnemySpawner);

Game::Game(void)
{
	mWindow = new sf::RenderWindow();
	mWindow->create(sf::VideoMode(1280, 720), "Base Defender SFML version A00001.15", sf::Style::Close);
	//mWindow->setTitle("Base Defender SFML version A00001.14");
	mWindow->setKeyRepeatEnabled(false);
	mWindow->setVerticalSyncEnabled(true);	
	mWorldView = new sf::View(mWindow->getDefaultView());
	mWorldOthersideView = new sf::View(mWindow->getDefaultView());
	mWorldSize = sf::Vector2f(1280.0f *4.0f, 600.0f);

	sf::Image icon;
	if (!icon.loadFromFile("Media/Textures/icon.PNG"))
		return;

	mWindow->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	//pPlayer = new Player();
}

void Game::Initialize(void)
{
	mTextures.load(Textures::Player, "Media/Textures/Player.PNG");
	mTextures.load(Textures::PlayerShot, "Media/Textures/PlayerShot.PNG");
	mTextures.load(Textures::PlayerThrust, "Media/Textures/PlayerThrust.PNG");
	mTextures.load(Textures::PlayerShieldOver, "Media/Textures/PlayerShipOvershield.PNG");
	mTextures.load(Textures::PlayerShieldUnder, "Media/Textures/PlayerShipUndershield.PNG");
	mTextures.load(Textures::Background, "Media/Textures/Background.PNG");
	mTextures.load(Textures::BackgroundLine, "Media/Textures/BackgroundLine.PNG");
	mTextures.load(Textures::Overlay, "Media/Textures/Overlay.PNG");
	mTextures.load(Textures::City, "Media/Textures/CityNew.PNG");
	mTextures.load(Textures::Attacker, "Media/Textures/Attacker.PNG");
	mTextures.load(Textures::AttackerShot, "Media/Textures/AttackerShot.PNG");
	mTextures.load(Textures::AttackerBomber, "Media/Textures/AttackerBomber.PNG");
	mTextures.load(Textures::AttackerFC, "Media/Textures/AttackerFC.PNG");
	mTextures.load(Textures::Bomber, "Media/Textures/Bomber.PNG");
	mTextures.load(Textures::Mine, "Media/Textures/Mine.PNG");
	mTextures.load(Textures::Pod, "Media/Textures/Pod.PNG");
	mTextures.load(Textures::Swarmer, "Media/Textures/Swarmer.PNG");
	mTextures.load(Textures::EnemyExplosion, "Media/Textures/TempEnemyExplosion.PNG");
	mTextures.load(Textures::Bomb, "Media/Textures/Bomb.PNG");
	mTextures.load(Textures::BombExplosion, "Media/Textures/TempBombExplosion.PNG");

	pBackground->Initialize(&mTextures.get(Textures::Background), mWindow->getSize(), mWorldSize);
	pBackground->InitializeLine(&mTextures.get(Textures::BackgroundLine));
	pOverlay->Initialize(&mTextures.get(Textures::Overlay));
	pPlayer->Initialize(&mTextures.get(Textures::Player), &mTextures.get(Textures::PlayerShot), &mTextures.get(Textures::PlayerThrust),
		&mTextures.get(Textures::PlayerShieldOver),	&mTextures.get(Textures::PlayerShieldUnder),
		mWindow->getSize(), mWorldSize);
	pCities->Initialize(&mTextures.get(Textures::City), mWindow->getSize(), mWorldSize);
	pSpawner->PlayerPointer(pPlayer);
	pSpawner->CityPointer(pCities);
	pSpawner->Initialize(&mTextures.get(Textures::Attacker), &mTextures.get(Textures::AttackerShot), &mTextures.get(Textures::AttackerBomber),
		&mTextures.get(Textures::AttackerFC), &mTextures.get(Textures::Bomb), &mTextures.get(Textures::BombExplosion), &mTextures.get(Textures::Bomber),
		&mTextures.get(Textures::Mine), &mTextures.get(Textures::Pod), &mTextures.get(Textures::Swarmer), &mTextures.get(Textures::EnemyExplosion),
		mWindow->getSize(), mWorldSize);

	mPlayerCenterX = mTextures.get(Textures::Player).getSize().x / 2.f;
	mWorldPlayerXMax = mWorldSize.x * 0.875f;
	mWorldPlayerXMin = mWindow->getSize().x * 0.5f;
}

void Game::Run(void)
{
	sf::Clock *clock = new sf::Clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Event *events = new sf::Event;

	while (mWindow->isOpen())
	{
		while (mWindow->pollEvent(*events))
		{
			if (events->type == sf::Event::Closed)
			{
				mWindow->close();
				return;
			}

			ProcessInput(events);
		}

		Update(&clock->restart());
		Draw();
		timeSinceLastUpdate = sf::Time::Zero;
	}
}

void Game::ProcessInput(sf::Event *event)
{
	if (event->type == sf::Event::KeyPressed || event->type == sf::Event::KeyReleased)
	{
		if (event->key.code == sf::Keyboard::Escape)
		{
			mWindow->close();
			return;
		}
	
		pPlayer->Events(event);
	}	
}

void Game::Update(sf::Time *delta)
{
	mSeeLeftSide = false;
	mSeeRightSide = false;

	pPlayer->Update(delta);
	pCities->Update(delta);

	sf::Vector2f playerpos = *pPlayer->GetPosition();
	mWorldView->setCenter(playerpos.x + mPlayerCenterX, 360.f);

	if (mWorldView->getCenter().x >= mWorldPlayerXMax) //4480 = 5120 * 0.875
	{
		mSeeLeftSide = true;
		mWorldOthersideView->setCenter(mWorldView->getCenter().x - mWorldSize.x, 360.f);
	}

	if (mWorldView->getCenter().x <= mWorldPlayerXMin + 100)
	{
		mSeeRightSide = true;
		mWorldOthersideView->setCenter(mWorldView->getCenter().x + mWorldSize.x, 360.f);
	}

	// Enemy Update here
	pSpawner->Update(delta);
	pRadar->Update(delta);
}

void Game::Draw(void)
{
	mWindow->clear();

	if (mSeeLeftSide || mSeeRightSide)
	{
		mWindow->setView(*mWorldOthersideView);
		// draw other side background here.
		pBackground->Draw(mWindow);
		pCities->Draw(mWindow);

		// Enemy Draw here
		pSpawner->Draw(mWindow);

		// So shots can be seen on the other size.
		pPlayer->Draw(mWindow);
	}

	mWindow->setView(*mWorldView);
	// Background elements here too
	pBackground->Draw(mWindow);
	pCities->Draw(mWindow);

	if (!mSeeLeftSide || !mSeeRightSide)
	{
		// Enemy Draw here too
		pSpawner->Draw(mWindow);
	}

	if (mSeeRightSide)
		pSpawner->DrawOtherSide(mWindow);

	pPlayer->Draw(mWindow);

	//Overlay, Radar and scores here
	pRadar->Draw(mWindow);
	pOverlay->Draw(mWindow);
	mWindow->display();
}