//
// Map.cpp for Map in /home/trupin_t/rendu/PSU_2014_zappy/graph
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Tue Jun 23 11:27:51 2015 Thomas Trupin
// Last update Sun Jul  5 20:08:50 2015 Alexis Feldmar
//

#include	"Map.hpp"

Map::Map()
{
  _map = NULL;
}

Map::~Map()
{
  if (_map)
    {
      for (int i = 0; i < _mapX; i++)
	delete [] _map[i];
      delete [] _map;
    }
}

void	Map::initSound()
{
  if (!_benny.openFromFile("./sound/benny.wav"))
    exit(-1);
  _benny.play();
  _benny.setLoop(true);
}

void	Map::stopSound()
{
  _benny.stop();
}

bool	Map::initMap(int x, int y)
{
  initSound();
  _mapX = x;
  _mapY = y;
  _map = new Cell *[_mapX];
  for (int i = 0; i < _mapX; i++)
    _map[i] = new Cell[_mapY];
  for (int j = 0; j < 7; j++)
    {
      if (!_stoneTex[j].loadFromFile(STONESET, sf::IntRect(j * SPRITE_W, 0, SPRITE_W, SPRITE_H)))
	{
	  std::cerr << "Error : can't load stones tileset." << std::endl;
	  return (false);
	}
      _stoneSprite[j].setTexture(_stoneTex[j]);
    }
  return (true);
}

Cell	&Map::getCell(int x, int y)
{
  return	_map[x][y];
}

// 7 valeurs -> 1 struct ?
void	Map::setCell(int x, int y, int v1, int v2, int v3, int v4, int v5, int v6, int v7)
{
  _map[x][y].setValues(v1, v2, v3, v4, v5, v6, v7);
}

int	Map::getX() const
{
  return (_mapX);
}

int	Map::getY() const
{
  return (_mapY);
}

void	Map::setSkin(int x, int y, int skin)
{
  _map[x][y].setSkin(skin);
}

void	Map::draw(sf::RenderWindow &window)
{
  for (int i = 0; i < _mapX; i++)
    for (int j = 0; j < _mapY; j++)
      _map[i][j].draw(window);
  drawStones(window);
}

void	Map::drawStones(sf::RenderWindow &window)
{
  int	*buff;

  int	test = 0;
  int	i = 0, j = 0;
  while (i != _mapX)
    {
      j = 0;
      while (j != _mapY)
	{
	  test ++;
	  buff = _map[i][j].getValues();
	  for (int x = 0; x < 7; x++)
	    {
	      if (buff[x])
		{
		  _stoneSprite[x].setPosition(i * SPRITE_W, j * SPRITE_H);
		  window.draw(_stoneSprite[x]);
		}
	    }
	  j++;
	}
      i++;
    }
}
