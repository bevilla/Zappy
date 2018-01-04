//
// Player.cpp for Player in /home/trupin_t/rendu/PSU_2014_zappy/graph
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Sat Jun 27 16:07:22 2015 Thomas Trupin
// Last update Sun Jul  5 22:09:09 2015 Thomas Trupin
//

#include	"Player.hpp"

Player::Player(int x, int y, char direction, char level, std::string team) : _team(team)
{
  for (int i = 0; i < 7; i++)
    _inventory[i] = 0;
  _coord.x = x * SPRITE_W;
  _coord.y = y * SPRITE_H;
  _playerDir = direction;
  _level = level;
  _animLevel = 0;
  _egg = false;
  _dying = false;
  _evolve = false;
  _win = false;
}

Player::~Player()
{}

bool		Player::init()
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

  if (!_texture.loadFromFile(PLAYER_SPRITE, sf::IntRect(0, SPRITE_H * (_playerDir - 1), SPRITE_W, SPRITE_H)))
    {
      std::cerr << "Error : Unable to load the player sprites" << std::endl;
      return (false);
    }
  _sprite.setTexture(_texture);
  _sprite.setPosition(_coord);
  if (_level > 1)
    _sprite.setColor(sf::Color(colortab[_level - 2][0],colortab[_level - 2][1],colortab[_level - 2][2]));
  return (true);
}

bool		Player::draw(sf::RenderWindow &window)
{
  if (_animLevel >= DYING_FRAMES)
    return (true);
  if (!_egg && !_dying && !_evolve && !_win)
    {
      if (!_texture.loadFromFile(PLAYER_SPRITE, sf::IntRect(_animLevel * SPRITE_W, SPRITE_H * (_playerDir - 1), SPRITE_W, SPRITE_H)))
	{
	  std::cerr << "Error : Unable to load the player sprites" << std::endl;
	  return (false);
	}
      if (_animClock.getElapsedTime().asMilliseconds() > FRAME_TIME)
	{
	  _animClock.restart();
	  _animLevel += 1;
	}
      if (_animLevel > ANIM_FRAMES)
	_animLevel = 0;
    }
  else if (_egg && !_dying && !_evolve)
    {
      if (!_texture.loadFromFile(EGG_SPRITE))
	{
	  std::cerr << "Error : Unable to load egg sprite" << std::endl;
	  return (false);
	}
    }
  else if (_evolve && !_dying)
    {
      if (!_texture.loadFromFile(EVOLVE_SPRITE, sf::IntRect(_animLevel * 54, 0 , 54, 54)))
	{
	  std::cerr << "Error : Can't load evolving sprite" << std::endl;
	  return (false);
	}
      if (_animClock.getElapsedTime().asMilliseconds() > FRAME_TIME)
	{
	  _animClock.restart();
	  _animLevel += 1;
	}
      if (_animLevel > EVOLVE_FRAMES)
	_animLevel = 0;
    }
  else if (!_dying && _win)
    {
      if (!_texture.loadFromFile(WIN_SPRITE, sf::IntRect(_animLevel * 54, 0 , 54, 54)))
	{
	  std::cerr << "Error : Can't load winning animation" << std::endl;
	  return (false);
	}
      if (_animClock.getElapsedTime().asMilliseconds() > FRAME_TIME)
	{
	  _animClock.restart();
	  _animLevel += 1;
	}
      if (_animLevel > WIN_FRAMES)
	_animLevel = 0;
    }
  else
    {
      if (!_texture.loadFromFile(DYING_SPRITE, sf::IntRect(_animLevel * SPRITE_W, 0, SPRITE_W, SPRITE_H)))
	{
	  std::cerr << "Error : Can't load dying sprite" << std::endl;
	  return (false);
	}
      if (_animClock.getElapsedTime().asMilliseconds() > FRAME_TIME)
	{
	  _animClock.restart();
	  _animLevel += 1;
	}
    }
  window.draw(_sprite);
  return (true);
}

void		Player::move(int x, int y, int ori)
{
  _coord.x = x * SPRITE_W;
  _coord.y = y * SPRITE_H;
  _sprite.setPosition(_coord);
  _playerDir = ori;
}

void		Player::levelUp(int newLevel)
{
  _level = newLevel;
}

sf::Vector2f	Player::getCoord() const
{
  return (_coord);
}

std::string	Player::getTeam() const
{
  return (_team);
}

void		Player::modifyInventory(int res, int nbr)
{
  _inventory[res] += nbr;
}

void		Player::expulse()
{
  // faire une animation swaggée ou le joueur fiat genre "libération"
}

void		Player::hatch()
{
  _egg = false;
}

void		Player::die()
{
  _dying = true;
  _animLevel = 0;
}

int		*Player::getInventory()
{
  return (_inventory);
}

sf::Sprite	&Player::getSprite()
{
  return(_sprite);
}

void		Player::setEvolve(bool evolving)
{
  _evolve = evolving;
}

void		Player::setAnimLevel(int newValue)
{
  _animLevel = newValue;
}

void		Player::setWin()
{
  _animLevel = 0;
  _win = true;
}

void		Player::setEgg()
{
  _egg = true;
}
