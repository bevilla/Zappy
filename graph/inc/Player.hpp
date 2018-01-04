//
// Player.hpp for Player in /home/trupin_t/rendu/PSU_2014_zappy/graph
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Sat Jun 27 16:08:09 2015 Thomas Trupin
// Last update Sun Jul  5 17:24:26 2015 Thomas Trupin
//

#ifndef PLAYER_H_
# define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Cell.hpp>

#define	PLAYER_SPRITE	"./graph/resources/sprites/player_sprite.png"
#define	DYING_SPRITE	"./graph/resources/sprites/dying.png"
#define	EGG_SPRITE	"./graph/resources/sprites/Egg.png"
#define	EVOLVE_SPRITE	"./graph/resources/sprites/Evolve.png"
#define	WIN_SPRITE	"./graph/resources/sprites/rolling_slime.png"

#define	NORTH		1
#define	EAST		2
#define	SOUTH		3
#define	WEST		4

#define	ANIM_FRAMES	7
#define	DYING_FRAMES	13
#define	EVOLVE_FRAMES	3
#define	WIN_FRAMES	9
#define	FRAME_TIME	50

class Player
{
public:
  Player(int x, int y, char direction, char level, std::string team);
  ~Player();

  bool			init();
  bool			draw(sf::RenderWindow &window);

  sf::Vector2f		getCoord() const;
  std::string		getTeam() const;
  int			*getInventory();
  sf::Sprite		&getSprite();
  void			modifyInventory(int res, int nbr);
  void			setAnimLevel(int newValue);

  void			move(int x, int y, int ori);
  void			levelUp(int newLevel);
  void			expulse();
  void			hatch();
  void			die();

  void			setEvolve(bool evolving);
  void			setWin();
  void			setEgg();

private:
  sf::Vector2f		_coord;
  sf::Texture		_texture;
  sf::Sprite		_sprite;
  sf::Clock		_animClock;
  bool			_egg;
  bool			_evolve;
  bool			_dying;
  bool			_win;
  int			_inventory[7];
  int			_animLevel;
  char			_level;
  char			_playerDir;
  char			_anim;
  const std::string	_team;
};

#endif /*!PLAYER_H_*/
