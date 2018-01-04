//
// Cell.cpp for Cell in /home/trupin_t/rendu/PSU_2014_zappy/graph
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Tue Jun 23 11:53:17 2015 Thomas Trupin
// Last update Fri Jul  3 12:36:59 2015 Thomas Trupin
//

#include	"Cell.hpp"

Cell::Cell()
{
  for	(int i = 0; i < 7; i++)
    _ressources[i] = 0;
}

Cell::~Cell()
{}

// 7val -> 1struct
void	Cell::setValues(int v1, int v2, int v3, int v4, int v5, int v6, int v7)
{
  _ressources[0] = v1;
  _ressources[1] = v2;
  _ressources[2] = v3;
  _ressources[3] = v4;
  _ressources[4] = v5;
  _ressources[5] = v6;
  _ressources[6] = v7;
}

void	Cell::setSkin(int skin)			// PAS OP
{
  _skin = skin;
}

bool	Cell::init(int x, int y, int sprite)
{
  int	spr_pos;

  spr_pos = (sprite - 1) * SPRITE_W;
  if (!_texture.loadFromFile(TILESET, sf::IntRect(spr_pos, 0, SPRITE_W, SPRITE_H)))
    {
      std::cerr << "Error : can't load tileset." << std::endl;
      return (false);
    }
  _tileSprite.setTexture(_texture);
  _coord.x = x;
  _coord.y = y;
  _tileSprite.setPosition(_coord);
  return (true);
}

void	Cell::draw(sf::RenderWindow &window)
{
  window.draw(_tileSprite);
}

void	Cell::debug()
{
  std::cout << "Coord : " << _coord.x << " / " << _coord.y << std::endl;
}

int	*Cell::getValues()
{
  return (_ressources);
}

void	Cell::gatherRessource(int idRes, int nbr)
{
  _ressources[idRes] += nbr;
}

void	Cell::incantEnd(bool result)
{
  (void)result; // Sinon ça fait un warning et c'est putain de casse couille
  // Animation de fin d'incantation
}
