#include "Game.h"

/////////////////////////////////////////////////////////////////////////////
////////////////				Constructors				/////////////////
/////////////////////////////////////////////////////////////////////////////

Game::Game(): m_MainWnd(sf::VideoMode(800,600,32), "Asteroid"), m_prevSpacePress(false), m_prevUpPress(false), m_prevDownPress(false), m_ObjectsCount(0)
{
	for(int i=0; i < 100 ; ++i)
		this->m_Objects[i] = NULL;
}

Game::~Game()
{
	delete m_pPlayer;
	//delete shotImg;
	//delete plImg;

	for(int i=0; i < 100 ; ++i)
	{
		if( this->m_Objects[i] != NULL )
			delete m_Objects[i];
	}
	delete[] m_Objects;
}

/////////////////////////////////////////////////////////////////////////////
////////////////				Methods						/////////////////
/////////////////////////////////////////////////////////////////////////////

void Game::Initialize()
{
	sf::Image* plImg    = new sf::Image();
	sf::Image* plTwoImg = new sf::Image();
	if( !plImg->LoadFromFile("goodFighter.png") )
		throw(new std::exception("Game::Initialize -> No se puede cargar la imagen: goodFighter.png"));

	if( !plTwoImg->LoadFromFile("evilFighter.png") )
		throw(new std::exception("Game::Initialize -> No se puede cargar la imagen: evilFighter.png"));
	

	sf::Image* shotImg = new sf::Image();
	if( !shotImg->LoadFromFile("bullet.png") )
		throw(new std::exception("Game::Initialize -> No se puede cargar la imagen: bullet.png"));

	if( !m_MenuFont.LoadFromFile("arial.ttf") )
		throw(new std::exception("Game::Initialize -> No se puede cargar la fuente del menu: arial.ttf"));

	if( !m_BackgroundImage.LoadFromFile("starfield.png") )
		throw(new std::exception("Game::Initialize -> No se puede cargar la imagen: starfield.png"));
	this->m_Background.SetImage(m_BackgroundImage);

	this->m_Play1Gamer.SetFont(m_MenuFont);
	this->m_Play1Gamer.SetText("Un jugador");
	this->m_Play1Gamer.SetPosition(this->m_MainWnd.GetWidth()/2.0f,this->m_MainWnd.GetHeight()/8.0f);
	this->m_Play1Gamer.SetColor(sf::Color::Red);
	this->m_MenuSelection = 0;
	this->m_Play2Gamer.SetFont(m_MenuFont);
	this->m_Play2Gamer.SetText("Dos jugador");
	this->m_Play2Gamer.SetPosition(this->m_MainWnd.GetWidth()/2.0f,this->m_MainWnd.GetHeight()*3/8.0f);
	this->m_DebugPlay.SetFont(m_MenuFont);
	this->m_DebugPlay.SetText("Debug");
	this->m_DebugPlay.SetPosition(this->m_MainWnd.GetWidth()/2.0f,this->m_MainWnd.GetHeight()*4/8.0f);
	this->m_Exit.SetFont(m_MenuFont);
	this->m_Exit.SetText("Salir");
	this->m_Exit.SetPosition(this->m_MainWnd.GetWidth()/2.0f,this->m_MainWnd.GetHeight()*7/8.0f);
	

	m_pPlayer    = new PlayerShip(plImg   , shotImg, this, 200, 200);
	m_pPlayerTwo = new PlayerShip(plTwoImg, shotImg, this, 500, 500);

	m_GameState = State::Menu;

}

void Game::Update()
{
	switch( m_GameState )
	{
	case State::Menu:
		{
			const sf::Input& Input = m_MainWnd.GetInput();

			if( m_prevUpPress && !Input.IsKeyDown(sf::Key::Up) )
			{
				if( m_MenuSelection == 1 )
				{
					m_Play1Gamer.SetColor(sf::Color::Red);
					m_Play2Gamer.SetColor(sf::Color::White);
					--m_MenuSelection;
				}else if( m_MenuSelection == 2 )
					{
						m_Play2Gamer.SetColor(sf::Color::Red);
						m_DebugPlay.SetColor(sf::Color::White);
						--m_MenuSelection;
					}else if( m_MenuSelection == 3 )
						{
							m_DebugPlay.SetColor(sf::Color::Red);
							m_Exit.SetColor(sf::Color::White);
							--m_MenuSelection;
						}
			}

			if( m_prevDownPress && !Input.IsKeyDown(sf::Key::Down) )
			{
				if( m_MenuSelection == 0 )
				{
					m_Play1Gamer.SetColor(sf::Color::White);
					m_Play2Gamer.SetColor(sf::Color::Red);
					++m_MenuSelection;
				}else if( m_MenuSelection == 1 )
					{
						m_Play2Gamer.SetColor(sf::Color::White);
						m_DebugPlay.SetColor(sf::Color::Red);
						++m_MenuSelection;
					}else if( m_MenuSelection == 2 )
						{
							m_DebugPlay.SetColor(sf::Color::White);
							m_Exit.SetColor(sf::Color::Red);
							++m_MenuSelection;
						}
			}

			if( m_prevSpacePress && !Input.IsKeyDown(sf::Key::Space) )
			{
				switch(m_MenuSelection)
				{
					case 0:
						m_GameState = State::Playing;
						m_TwoPlayers = false;
						break;
					case 1:
						m_GameState = State::Playing;
						m_TwoPlayers = true;
						break;
					case 2:
						m_GameState = State::Playing;
						m_TwoPlayers = false;
						break;
					case 3:
						m_MainWnd.Close();
						break;
				}
			}

			m_prevSpacePress = Input.IsKeyDown(sf::Key::Space);
			m_prevUpPress    = Input.IsKeyDown(sf::Key::Up);
			m_prevDownPress  = Input.IsKeyDown(sf::Key::Down);
		}
		break;
	case State::Playing:
		{
		float elapsedTime = this->m_MainWnd.GetFrameTime();

		const sf::Input& Input = m_MainWnd.GetInput();
		if( Input.IsKeyDown(sf::Key::Up) )
			m_pPlayer->MoveForward();

		if( Input.IsKeyDown(sf::Key::Down) )
			m_pPlayer->MoveBackward();

		if( Input.IsKeyDown(sf::Key::Left) )
			m_pPlayer->TurnLeft();

		if( Input.IsKeyDown(sf::Key::Right) )
			m_pPlayer->TurnRight();

		if( !m_prevSpacePress && Input.IsKeyDown(sf::Key::Space) )
			m_pPlayer->Shot();

		if( m_TwoPlayers )
		{
			if( Input.IsKeyDown(sf::Key::W) )
				m_pPlayerTwo->MoveForward();

			if( Input.IsKeyDown(sf::Key::S) )
				m_pPlayerTwo->MoveBackward();

			if( Input.IsKeyDown(sf::Key::A) )
				m_pPlayerTwo->TurnLeft();

			if( Input.IsKeyDown(sf::Key::D) )
				m_pPlayerTwo->TurnRight();

			if( !m_prevFPress && Input.IsKeyDown(sf::Key::F) )
				m_pPlayerTwo->Shot();
		}

		if( Input.IsKeyDown(sf::Key::Escape) )
			m_MainWnd.Close();

		if( m_TwoPlayers )
			m_pPlayerTwo->Update(elapsedTime);

		m_pPlayer->Update(elapsedTime);

		for(int i=0; i < m_ObjectsCount ;++i)
			m_Objects[i]->Update(elapsedTime);

		//Collision
		for(int i=0; i < m_ObjectsCount ;++i)
			if( Object::Collide( *m_pPlayer, *m_Objects[i] ) )
			{
				sf::Vector2<float> normal = m_pPlayer->GetPosition() - m_Objects[i]->GetPosition();
				normal = normal/Norm(normal);
				m_pPlayer->ResolveCollision(normal);

				delete m_Objects[i];
				for(int j=i; j < (m_ObjectsCount-1); ++j)
					m_Objects[j] = m_Objects[j+1];
				--m_ObjectsCount;
				//m_Objects[i]->ResolveCollision(-normal);
			}

		if( m_TwoPlayers )
		{
			for(int i=0; i < m_ObjectsCount ;++i)
			if( Object::Collide( *m_pPlayerTwo, *m_Objects[i] ) )
			{
				sf::Vector2<float> normal = m_pPlayerTwo->GetPosition() - m_Objects[i]->GetPosition();
				normal = normal/Norm(normal);
				m_pPlayerTwo->ResolveCollision(normal);

				delete m_Objects[i];
				for(int j=i; j < (m_ObjectsCount-1); ++j)
					m_Objects[j] = m_Objects[j+1];
				--m_ObjectsCount;
				//m_Objects[i]->ResolveCollision(-normal);

			}

			if( Object::Collide( *m_pPlayer, *m_pPlayerTwo ) )
				{
					sf::Vector2<float> normal = m_pPlayer->GetPosition() - m_pPlayerTwo->GetPosition();
					normal = normal/Norm(normal);
					m_pPlayer->ResolveCollision(normal);
					m_pPlayerTwo->ResolveCollision(-normal);
				}
		}

/*
		for(int i=0; i < m_ObjectsCount ;++i)
			for(int j=0; j < m_ObjectsCount ;++j)
				if( i != j )
					if( Object::Collide( *m_Objects[i], *m_Objects[j] ) )
					{
						sf::Vector2<float> normal = m_Objects[i]->GetPosition() - m_Objects[j]->GetPosition();
						normal = normal/Norm(normal);
						m_Objects[i]->ResolveCollision(normal);
						m_Objects[j]->ResolveCollision(-normal);
					}
*/

		m_prevSpacePress = Input.IsKeyDown(sf::Key::Space);
		m_prevFPress     = Input.IsKeyDown(sf::Key::F);

		}
		break;
	}
}

void Game::Draw()
{
	switch( m_GameState )
	{
	case State::Menu:
		{
			m_MainWnd.Draw(m_Play1Gamer);
			m_MainWnd.Draw(m_Play2Gamer);
			m_MainWnd.Draw(m_DebugPlay);
			m_MainWnd.Draw(m_Exit);
		}
		break;
	case State::Playing:
		{
			m_MainWnd.Draw(m_Background);
			m_pPlayer->Draw(m_MainWnd);
			if( m_TwoPlayers )
				m_pPlayerTwo->Draw(m_MainWnd);


			for(int i=0; i < m_ObjectsCount ;++i)
				m_Objects[i]->Draw(m_MainWnd);
		}
		break;
	}
}

void Game::AddObject(Object* object)
{
	if( m_ObjectsCount == 100 )//va a dejar memory leaks!
		m_ObjectsCount = 0;
	m_Objects[m_ObjectsCount] = object;
	m_ObjectsCount++;
}

int Game::Run()
	{
		Initialize();
		
		// Main message loop:
		while ( m_MainWnd.IsOpened() )
		{
			while( m_MainWnd.GetEvent(m_Msg) )
			{
				if( m_Msg.Type == sf::Event::Closed )
					m_MainWnd.Close();
			}

			Update();

			m_MainWnd.Clear();
			
			Draw();

			m_MainWnd.Display();
		}

		return 0;
	}