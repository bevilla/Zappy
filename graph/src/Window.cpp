//
// Graph.cpp for zappy in /home/chardo_j/rendu/PSU_2014_zappy/graph
//
// Made by Julien Chardon
// Login   <chardo_j@epitech.net>
//
// Started on  Wed Jun 10 11:49:19 2015 Julien Chardon
// Last update Sun Jul  5 22:11:36 2015 Thomas Trupin
//

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Window.hpp"
#include "Map.hpp"

Window::Window(const std::string &addr, int port)
{
  _client.setAddr(addr);
  _client.setPort(port);
  _client.setWindow(*this);
  _time.setWindow(*this);
  _locked = NULL;
  _isEnded = false;
  _isLoaded = false;
}

Window::~Window()
{
  _client.disconnect();
  for (std::map<int,Player*>::iterator it=_players.begin(); it!=_players.end(); ++it)
    delete it->second;
}

bool	Window::init()
{
  if (!_client.connectToServer())
    return false;
  if (!_inventory.init())
    return (false);
  _playerNbr = 0;
  _inventToggle = false;
  if (!initWindow() || !initFont())
    return false;
  return true;
}

void	Window::initSound()
{
  if (!_victory.openFromFile("./sound/victory.wav"))
    exit(-1);
}

bool	Window::initWindow()
{
  _window.create(sf::VideoMode(W_WIDTH, W_HEIGHT), W_NAME,
	   sf::Style::Titlebar | sf::Style::Close);
  if (!_window.isOpen())
    {
      std::cerr << "Error: Couldn't init the window." << std::endl;
      return false;
    }
  initSound();
  return true;
}

bool	Window::initFont()
{
  std::string nameFont = W_N_FONT_PATH;
  nameFont += W_N_FONT;
  if (!_font.loadFromFile(nameFont))
    {
      std::cerr << "Error: Couldn't load font : " << W_N_FONT << "." << std::endl;
      return false;
    }
  return true;
}

void	Window::manage()
{
  sf::Time time;

  while (_window.isOpen() && (_client.isConnected() || _isEnded))
    {
      if (!_isLoaded)
	manageWin();
      else
	{
	  time = _clock.getElapsedTime();
	  if (time >= sf::milliseconds(1000 / W_FPS))
	    {
	      manageWin();
	    }
	  else
	    sf::sleep(sf::milliseconds(1000 / W_FPS) - time);
	}
    }
}

void	Window::manageWin()
{
  if (_client.canRead())
    _client.parseMessage(_client.getMessage());
  manageEvent();
}

void	Window::manageEvent()
{
  sf::Event event;

  while (_window.pollEvent(event))
    {
      switch (event.type)
  	{
  	case sf::Event::Closed:
  	  _window.close();
  	  break;
  	case sf::Event::KeyPressed:
  	  if (event.key.code == sf::Keyboard::Escape)
  	    _inventToggle = false;
  	  else if (event.key.code == sf::Keyboard::P)
	    _time.setPause();
  	  break;
  	case sf::Event::MouseButtonPressed:
  	  if (event.mouseButton.button == sf::Mouse::Left)
  	    eventClick(event);
  	  if (event.mouseButton.button == sf::Mouse::Right)
  	    followPlayer(event);
  	  if (event.mouseButton.button == sf::Mouse::Left)
	    _time.eventClick(event);
  	default:
  	  break;
  	}
      _camera.event(event, _window);
    }
  refreshWin();
}

void	Window::eventClick(sf::Event &event)
{
  sf::Vector2f	center = _camera.getView().getCenter();
  sf::Vector2f	size = _camera.getView().getSize();
  double	zoomLevel = W_WIDTH / size.x;
  int		x = event.mouseButton.x + (center.x - size.x / 2);
  int		y = event.mouseButton.y + (center.y - size.y / 2);

  x = x / zoomLevel;
  y = y / zoomLevel;


  for (std::map<int,Player*>::iterator it=_players.begin(); it!=_players.end(); ++it)
    {
      sf::Vector2f	pos;
      pos = it->second->getCoord();
      if (pos.x < x && x < (pos.x + SPRITE_W)  && pos.y < y && y < (pos.y + SPRITE_H))
	{
	  int		tab[7];
	  std::ostringstream kek;

	  kek << it->first;
	  _client.sendMessage("pin " + kek.str() + "\n");
	  for (int i = 0; i < 7; i++)
	    tab[i] = it->second->getInventory()[i];
	  pin(it->first, pos.x / SPRITE_W, pos.y / SPRITE_H, tab[0],tab[1],tab[2],tab[3],tab[4],tab[5],tab[6]);
	  std::cout << it->second->getTeam() << std::endl;
	  return;
	}
    }
  x = x / 54;
  y = y / 54;
  if (x >= 0 && y >= 0 && x < _map.getX() && y < _map.getY())
    showCell(x, y);
}

void	Window::followPlayer(sf::Event &event)
{
  sf::Vector2f	center = _camera.getView().getCenter();
  sf::Vector2f	size = _camera.getView().getSize();
  int		x = event.mouseButton.x + (center.x - size.x / 2);
  int		y = event.mouseButton.y + (center.y - size.y / 2);

  _locked = NULL;
  for (std::map<int,Player*>::iterator it=_players.begin(); it!=_players.end(); ++it)
    {
      sf::Vector2f	pos;
      pos = it->second->getCoord();
      if (pos.x < x && x < (pos.x + SPRITE_W)  && pos.y < y && y < (pos.y + SPRITE_H))
	{
	  _locked = it->second;
	  return;
	}
    }
}

void	Window::refreshWin()
{
  _window.clear();
  _camera.update();
  draw();
  _window.display();
}

void	Window::draw()
{
  if (_locked != NULL)
    _camera.getView().setCenter(_locked->getCoord());
  _window.setView(_camera.getView());
  _map.draw(_window);
  for (std::map<int,Player*>::iterator it=_players.begin(); it!=_players.end(); ++it)
    it->second->draw(_window);
  _broadcast.draw(_window);
  _window.setView(_window.getDefaultView());
  _chatBox.draw(_window);
  _time.draw(_window);
  if (_inventToggle)
    _inventory.draw(_window);
}


// Fonctions serveur

bool	Window::ppo(int id, int x, int y, int orientation)
{
  _players[id]->move(x, y, orientation);
  return (true);
}

bool	Window::plv(int id, int newLevel)
{
  int	colortab[7][3] = {
    {45, 150, 20},		// Green Carnation
    {240, 175, 0},		// Clockwork Orange
    {240, 5, 5},		// Red red wine
    {255, 240, 0},		// Yellow Mellow
    {0, 255, 255},		// Cyan ide and happiness
    {255, 80, 230},		// Swaggy
    {190, 190, 190},		// 50 nuances
  };

  _players[id]->getSprite().setColor(sf::Color(255, 255, 255));
  _players[id]->getSprite().setColor(sf::Color(colortab[newLevel - 2][0],colortab[newLevel - 2][1],colortab[newLevel - 2][2]));
  _players[id]->levelUp(newLevel);

  return (true);
}

bool	Window::pgt(int playerId, int itemId)
{
  sf::Vector2f	temp;

  temp = _players[playerId]->getCoord();
  temp.x = temp.x / SPRITE_W;
  temp.y = temp.y / SPRITE_W;
  _map.getCell(temp.x, temp.y).gatherRessource(itemId, -1);
  _players[playerId]->modifyInventory(itemId, 1);
  return (true);
}

bool	Window::pdr(int playerId, int itemId)
{
  sf::Vector2f		temp;

  temp = _players[playerId]->getCoord();
  temp.x = temp.x / SPRITE_W;
  temp.y = temp.y / SPRITE_W;
  _map.getCell(temp.x, temp.y).gatherRessource(itemId, 1);
  _players[playerId]->modifyInventory(itemId, -1);
  return (true);
}

bool	Window::pex(int playerId)
{
  _players[playerId]->expulse();
  return (true);
}

bool	Window::pie(int x, int y, bool result)
{
  std::ostringstream oss;

  oss << "L'incantation en [" << x << ";" << y << "] a " << (result ? "reussi" : "echoue");
  _chatBox.addString(ChatBox::CHAT_GREEN, oss.str());
  _map.getCell(x, y).incantEnd(result);
  for (std::map<int,Player*>::iterator it=_players.begin(); it!=_players.end(); ++it)
    {
      int	_x = it->second->getCoord().x;
      int	_y = it->second->getCoord().y;

      if (_x / 54 == x && _y / 54 == y)
	it->second->setEvolve(false);
    }

  return (true);
}

bool	Window::enw(int idEgg, int idPlayer, int x, int y)
{
  pnw(idEgg, x, y, 1, 1, _players[idPlayer]->getTeam());
  _players[idEgg]->setEgg();
  return (true);
}

bool	Window::eht(int idEgg)
{
  _players[idEgg]->die();
  _players[idEgg]->setAnimLevel(50);
  return (true);
}

bool	Window::msz(int width, int height)
{
  int	random_sprite;

  if (!_map.initMap(width, height))
    return (false);
  srand(time(NULL));
  for(int i = 0; i < _map.getX(); i++)
    {
      for(int j = 0; j < _map.getY(); j++)
	{
	  random_sprite = rand() % CELL_SKINS_NBR + 1;
	  if (!_map.getCell(i, j).init(i * SPRITE_W, j * SPRITE_H, random_sprite))
	    return (false);
	}
    }
  _camera.setWidthMap(width);
  _camera.setHeightMap(height);
  return (true);
}

bool	Window::pdi(int playerId)
{
  std::ostringstream oss;

  oss << "Le joueur " << playerId << " est MORT";
  _chatBox.addString(ChatBox::CHAT_RED, oss.str());
  _players[playerId]->die();
  return (true);
}

bool	Window::pnw(int id, int x, int y, int ori, int level, std::string team)
{
  _players[id] = new Player(x, y, ori, level, team);
  if (!_players[id]->init())
    return (false);
  _playerNbr ++;
  return (true);
}

bool	Window::pbc(int id, const std::string &msg)
{
  std::ostringstream oss;

  oss << "Player " << id << ": " << msg;
  _chatBox.addString(ChatBox::CHAT_WHITE, oss.str());
  _broadcast.addBroadcast(_players[id]->getCoord().x,
			  _players[id]->getCoord().y);
  return true;
}

bool	Window::pin(int id, int x, int y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
  int	tab[7] = {food, linemate, deraumere, sibur, mendiane, phiras, thystame};

  _inventory.fill(id, x, y, tab, _players[id]->getTeam());
  _inventToggle = true;
  return (true);
}

void	Window::showCell(int x, int y)
{
  int	*tab;
  std::ostringstream oss;

  oss << "bct " << x << " " << y << std::endl;
  _client.sendMessage(oss.str());
  tab = _map.getCell(x, y).getValues();
  _inventory.fill(-1, x, y, tab, "Cell");
  _inventToggle = true;
}

bool	Window::pic(int x, int y, int level, const std::list<int> &players)
{
  std::ostringstream oss;

  oss << "Elevation au niveau " << level + 1 << " en [" << x << ";" << y << "]";
  _chatBox.addString(ChatBox::CHAT_GREEN, oss.str());
  for (std::list<int>::const_iterator it = players.begin(); it != players.end(); it++)
    {
      _players[*it]->setAnimLevel(0);
      _players[*it]->setEvolve(true);
    }
  return true;
}

bool	Window::bct(int x, int y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
  if (x == (_map.getX() - 1) && y == (_map.getY() - 1))
    _isLoaded = true;
  _map.setCell(x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame);
  return (true);
}

bool	Window::seg(const std::string &msg)
{
  std::ostringstream oss;

  _isEnded = true;
  _map.stopSound();
  _victory.play();
  oss << "L'equipe '" << msg << "' remporte la victoire !";
  std::cout << oss.str() << std::endl;
  _chatBox.addString(ChatBox::CHAT_GREEN, oss.str());
  for (std::map<int, Player *>::iterator it = _players.begin();
       it != _players.end();
       ++it)
    if (it->second->getTeam() == msg)
      {
	it->second->setWin();
      }
  return true;
}

bool	Window::sgt(int time)
{
  _time.setOldTime(time);
  return (true);
}

bool	Window::sst(int time)
{
  std::ostringstream oss;

  oss << "sst " << time << "\n";
  _client.sendMessage(oss.str());
  return (true);
}

// Getter

ChatBox	&Window::getChatBox()
{
  return _chatBox;
}
