#include "Game.h"

ResourceHolder<sf::Texture, Textures::ID> mTextures;

std::shared_ptr<Player> pPlayer(new Player);
std::shared_ptr<Cities> pCities(new Cities);
std::unique_ptr<Background> pBackground(new Background);
std::unique_ptr<Overlay> pOverlay(new Overlay);
std::unique_ptr<Radar> pRadar(new Radar);
std::unique_ptr<EnemySpawner> pSpawner(new EnemySpawner);

//std::shared_ptr<sf::RenderTexture> pRadarTexure(new sf::RenderTexture); //TODO: What is this even for?

Game::Game(void)
{
	/* initialize random seed: */
	srand(unsigned(time(NULL)));

	const unsigned int gameWidth = 1280;
	const unsigned int gameHeight = 720;
	const std::string gameTitle = "Base Defender using SFML 2.3.2 - game version A01.40";

	mWindow = new sf::RenderWindow();
	mWindow->create(sf::VideoMode(gameWidth, gameHeight, 32), gameTitle, sf::Style::Titlebar | sf::Style::Close);

	mWindow->setKeyRepeatEnabled(false);
	mWindow->setVerticalSyncEnabled(true);	
	mWorldView = new sf::View(mWindow->getDefaultView());
	mWorldOthersideView = new sf::View(mWindow->getDefaultView());
	mWorldSize = sf::Vector2f(1280.0f *4.0f, 600.0f);
	//pRadarTexure->create(int(mWorldSize.x), int (mWorldSize.y));
	//pRadarTexure->setSmooth(true);

	sf::Image icon;
	if (!icon.loadFromFile("Media/Textures/icon.PNG"))
		return;

	mWindow->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::Initialize(void)
{
	mTextures.load(Textures::Player, "Media/Textures/Player.PNG");
	mTextures.load(Textures::PlayerRadar, "Media/Textures/RadarPlayerDot.PNG");
	mTextures.load(Textures::PlayerShot, "Media/Textures/PlayerShot.PNG");
	mTextures.load(Textures::PlayerThrust, "Media/Textures/PlayerThrust.PNG");
	mTextures.load(Textures::PlayerShieldOver, "Media/Textures/PlayerShipOvershield.PNG");
	mTextures.load(Textures::PlayerShieldUnder, "Media/Textures/PlayerShipUndershield.PNG");
	mTextures.load(Textures::Background, "Media/Textures/Background.PNG");
	mTextures.load(Textures::BackgroundLine, "Media/Textures/BackgroundLine.PNG");
	mTextures.load(Textures::Overlay, "Media/Textures/Overlay.PNG");
	mTextures.load(Textures::Radar, "Media/Textures/Radar.PNG");
	mTextures.load(Textures::City, "Media/Textures/CityNew.PNG");
	mTextures.load(Textures::CityDamaged1, "Media/Textures/CityDamaged1.PNG");
	mTextures.load(Textures::CityDamaged2, "Media/Textures/CityDamaged2.PNG");
	mTextures.load(Textures::CityDamaged3, "Media/Textures/CityDamaged3.PNG");
	mTextures.load(Textures::CityDamaged4, "Media/Textures/CityDamaged4.PNG");
	mTextures.load(Textures::CityDistroyed, "Media/Textures/CityDistroyed.PNG");
	mTextures.load(Textures::CityRadar, "Media/Textures/RadarCityDot.PNG");
	mTextures.load(Textures::CityRadarAlert, "Media/Textures/RadarCityDotAlert.PNG");
	mTextures.load(Textures::CityRadarDistroyed, "Media/Textures/RadarCityDotDistroyed.PNG");
	mTextures.load(Textures::Attacker, "Media/Textures/Attacker.PNG");
	mTextures.load(Textures::AttackerRadar, "Media/Textures/RadarAttackerDot.PNG");
	mTextures.load(Textures::AttackerShot, "Media/Textures/AttackerShot.PNG");
	mTextures.load(Textures::AttackerBomber, "Media/Textures/AttackerBomber.PNG");
	mTextures.load(Textures::AttackerFC, "Media/Textures/AttackerFC.PNG");
	mTextures.load(Textures::Berserker, "Media/Textures/Berserker.PNG");
	mTextures.load(Textures::BerserkerRadar, "Media/Textures/RadarBerserkerDot.PNG");
	mTextures.load(Textures::MineLayer, "Media/Textures/MineLayer.PNG");
	mTextures.load(Textures::MineLayerRadar, "Media/Textures/RadarMineLayerDot.PNG");
	mTextures.load(Textures::Mine, "Media/Textures/Mine.PNG");
	mTextures.load(Textures::Pod, "Media/Textures/Pod.PNG");
	mTextures.load(Textures::PodRadar, "Media/Textures/RadarPodDot.PNG");
	mTextures.load(Textures::Swarmer, "Media/Textures/Swarmer.PNG");
	mTextures.load(Textures::SwarmerRadar, "Media/Textures/RadarSeakerDot.PNG");
	mTextures.load(Textures::EnemyExplosion, "Media/Textures/TempEnemyExplosion.PNG");
	mTextures.load(Textures::Bomb, "Media/Textures/Bomb.PNG");
	mTextures.load(Textures::BombExplosion, "Media/Textures/TempBombExplosion.PNG");

	pBackground->Initialize(&mTextures.get(Textures::Background), mWindow->getSize(), mWorldSize);
	pRadar->Initialize(&mTextures.get(Textures::Radar), mWindow->getSize());
	pBackground->InitializeLine(&mTextures.get(Textures::BackgroundLine));
	pOverlay->Initialize(&mTextures.get(Textures::Overlay));
	pPlayer->Initialize(&mTextures.get(Textures::Player), &mTextures.get(Textures::PlayerRadar), &mTextures.get(Textures::PlayerShot),
		&mTextures.get(Textures::PlayerThrust),	&mTextures.get(Textures::PlayerShieldOver),	&mTextures.get(Textures::PlayerShieldUnder),
		mWindow->getSize(), mWorldSize);
	pCities->Initialize(&mTextures.get(Textures::City), &mTextures.get(Textures::CityDamaged1), &mTextures.get(Textures::CityDamaged2),
		&mTextures.get(Textures::CityDamaged3), &mTextures.get(Textures::CityDamaged4), &mTextures.get(Textures::CityDistroyed),
		&mTextures.get(Textures::CityRadar), &mTextures.get(Textures::CityRadarAlert), &mTextures.get(Textures::CityRadarDistroyed),
		mWindow->getSize(), mWorldSize);
	pSpawner->PlayerPointer(pPlayer);
	pSpawner->CityPointer(pCities);
	pSpawner->InitializeRadar(&mTextures.get(Textures::MineLayerRadar), &mTextures.get(Textures::PodRadar),	&mTextures.get(Textures::SwarmerRadar));
	pSpawner->InitializeCityEnemyRadar(&mTextures.get(Textures::AttackerRadar), &mTextures.get(Textures::BerserkerRadar));
	pSpawner->Initialize(&mTextures.get(Textures::MineLayer), &mTextures.get(Textures::Mine), &mTextures.get(Textures::Pod),
		&mTextures.get(Textures::Swarmer), &mTextures.get(Textures::AttackerShot), &mTextures.get(Textures::EnemyExplosion),
		mWindow->getSize(), mWorldSize);
	pSpawner->InitializeCityEnemys(&mTextures.get(Textures::Attacker), &mTextures.get(Textures::AttackerBomber), &mTextures.get(Textures::AttackerFC),
		&mTextures.get(Textures::Berserker), &mTextures.get(Textures::Bomb), &mTextures.get(Textures::BombExplosion));
	mPlayerCenterX = mTextures.get(Textures::Player).getSize().x / 2.f;
	mWorldPlayerXMax = mWorldSize.x * 0.875f;
	mWorldPlayerXMin = mWindow->getSize().x * 0.5f;
}

void Game::Run(void)
{
	sf::Clock *clock = new sf::Clock;
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

	float playerX = pPlayer->GetPosition()->x;
	pCities->Update(delta, &playerX);

	mWorldView->setCenter(pPlayer->GetPosition()->x + mPlayerCenterX, 360.f);

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

	// Reset View to default.
	mWindow->setView(mWindow->getDefaultView());
	// Draw Radar here.
	pRadar->Draw(mWindow);
	pSpawner->DrawRadar(mWindow);
	pCities->DrawRadar(mWindow);
	// Reset View to world.
	mWindow->setView(*mWorldView);
	// Draw Radar dots and Background here.
	pPlayer->DrawRadar(mWindow); //TODO::Fix so this is in one place too. So it uses the default view.
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
	// Reset View to default.
	mWindow->setView(mWindow->getDefaultView());
	//Overlay, and score here. They go over the top of everything else.
	pOverlay->Draw(mWindow);
	mWindow->display();
}