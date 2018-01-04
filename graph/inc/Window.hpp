//
// Window.hpp for zappy in /home/chardo_j/rendu/PSU_2014_zappy/graph/src
//
// Made by Julien Chardon
// Login   <chardo_j@epitech.net>
//
// Started on  Wed Jun 10 11:44:38 2015 Julien Chardon
// Last update Sun Jul  5 22:09:56 2015 Thomas Trupin
//

#ifndef WINDOW_HPP_
# define WINDOW_HPP_

#include	<unistd.h>

#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "ZappyClient.hpp"
#include "defWin.hpp"
#include "ChatBox.hpp"
#include "Inventory.hpp"
#include "Broadcast.hpp"
#include "Time.hpp"

class Window
{
public:
  Window(const std::string &addr, int port);
  ~Window();

public:
  bool	init();

private:
  bool	initWindow();
  bool	initFont();

public:
  void	manage();

  bool	newPlayer(int id, int x, int y, char direction, char level, std::string team);
  bool	ppo(int id, int x, int y, int orientaion);	// déplacement joueur
  bool	plv(int id, int newLelvel);			// level up
  bool	pgt(int playerId, int itemId);			// ressource récup.
  bool	pdr(int playerId, int itemId);			// ressource jettée
  bool	pex(int playerId);				// expulse
  bool	pie(int x, int y, bool result);			// fin d'incant sur la case
  bool	enw(int idEgg, int idPlayer, int x, int y);	// un joueur pond
  bool	eht(int idEgg);					// eclosion
  bool	msz(int width, int height);			// init de la map
  bool	pdi(int playerId);				// player die
  bool	pnw(int id, int x, int y, int ori, int level, std::string team); //co player
  bool  pbc(int id, const std::string &msg); // broadcast
  bool  pic(int x, int y, int level, const std::list<int> &players);
  bool	bct(int x, int y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);
  bool	sgt(int time);
  bool	sst(int time);

  bool	pin(int id, int x, int y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);                // inventaire
  bool	seg(const std::string &msg);
  void	showCell(int x, int y);				 // inventaire cell

private:
  void	manageWin();
  void	manageEvent();

  void	refreshWin();
  void	draw();

  void	eventClick(sf::Event &event);
  void	followPlayer(sf::Event &event);

  void	initSound();

private:
  ZappyClient		_client;
  sf::RenderWindow	_window;
  sf::Clock		_clock;
  sf::Font		_font;
  Map			_map;
  Camera		_camera;
  std::map<int,Player*>	_players;
  int			_playerNbr;
  ChatBox		_chatBox;
  Inventory		_inventory;
  bool			_inventToggle;
  Time			_time;
  Player		*_locked;
  bool			_isEnded;
  Broadcast		_broadcast;
  sf::Music		_victory;
  bool			_isLoaded;

public:
  ChatBox		&getChatBox();
};

#endif
