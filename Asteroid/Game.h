#pragma once

#include "SFML//Graphics.hpp"
#include "SFML//System.hpp"
#include "SFML//Window.hpp"
#include "SFML//Config.hpp"

#include "PlayerShip.h"


class Game
{
private:
	enum State{Menu, Playing, GameOver};
	State m_GameState;

	sf::Font   m_MenuFont;
	sf::String m_Play1Gamer;
	sf::String m_Play2Gamer;
	sf::String m_DebugPlay;
	sf::String m_Exit;
	int m_MenuSelection;

	bool       m_prevSpacePress;
	bool       m_prevFPress;
	bool       m_prevUpPress;
	bool       m_prevDownPress;

	bool m_TwoPlayers;

	sf::RenderWindow m_MainWnd;

	sf::Image  m_BackgroundImage;
	sf::Sprite m_Background;

	sf::Event        m_Msg;

	PlayerShip* m_pPlayer;
	PlayerShip* m_pPlayerTwo;

	int m_ObjectsCount;
	Object* m_Objects[100];

	void Initialize();

	void Draw();

	void Update();

public:
	Game();

	~Game();

	void AddObject(Object* object);

	int Run();

};