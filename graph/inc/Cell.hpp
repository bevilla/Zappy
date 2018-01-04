//
// Cell.hpp for Cell in /home/trupin_t/rendu/PSU_2014_zappy/graph
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Tue Jun 23 10:55:10 2015 Thomas Trupin
// Last update Sun Jul  5 10:20:58 2015 Louis Bouteillon
//

#ifndef CELL_H_
# define CELL_H_

#include <SFML/Graphics.hpp>
#include <iostream>

#define	LINEMATE	1
#define	DERAUMERE	2
#define	SIBUR		3
#define	MENDIANE	4
#define	PHIRAS		5
#define	THYSTAME	6
#define	FOOD		0

#define SPRITE_W	54
#define SPRITE_H	54
#define	CELL_SKINS_NBR	7

#define	TILESET		"./graph/resources/sprites/tileset.png"

class Cell
{
public:
  Cell();
  ~Cell();

  bool	init(int x, int y, int sprite);
  void	draw(sf::RenderWindow &window);

  void	setValues(int v1, int v2, int v3, int v4, int v5, int v6, int v7);
  void	setSkin(int skin);
  void	gatherRessource(int idRes, int nbr);
  void	incantEnd(bool result);

  int	*getValues();

  void	debug();

private:
  int		_ressources[7];
  int		_skin;
  sf::Texture	_texture;
  sf::Sprite	_tileSprite;
  sf::Vector2f	_coord;
};

#endif /*!CELL_H_*/
