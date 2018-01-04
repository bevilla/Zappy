//
// Map.hpp for Map in /home/trupin_t/rendu/PSU_2014_zappy/graph
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Tue Jun 23 11:21:02 2015 Thomas Trupin
// Last update Sun Jul  5 20:09:06 2015 Alexis Feldmar
//

#ifndef MAP_H_
# define MAP_H_

#include	<SFML/Audio.hpp>
#include	"Cell.hpp"

#define	STONESET	"./graph/resources/sprites/stone_tile.png"

class Map
{
public:
  Map();
  ~Map();

public:
  bool	initMap(int x, int y);

  void	setCell(int x, int y, int v1, int v2, int v3, int v4, int v5, int v6, int v7);
  void	setSkin(int x, int y, int skin);

  Cell	&getCell(int x, int y);
  int	getX() const;
  int	getY() const;

  void	draw(sf::RenderWindow &window);

  void	stopSound();

private:
  void	drawStones(sf::RenderWindow &window);
  void	initSound();

private:
  Cell			**_map;
  int			_mapX;
  int			_mapY;
  sf::Texture		_stoneTex[7];
  sf::Sprite		_stoneSprite[7];
  sf::Music		_benny;
};

#endif /*!MAP_H_*/
