//
// Broadcast.hpp for zappy in /home/bevill_a/rendu/PSU_2014_zappy/graph
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Sat Jul  4 10:35:22 2015 Alexis Bevillard
// Last update Sun Jul  5 11:18:55 2015 Louis Bouteillon
//

#pragma once

#include		<SFML/Graphics.hpp>
#include		<SFML/Graphics/CircleShape.hpp>
#include		<list>

#define MIN_CIRCLE_SIZE	5.f
#define MAX_CIRCLE_SIZE	400.f
#define CIRCLE_STEP     2.f
#define CIRCLE_COLOR	sf::Color(255, 255, 255)
#define BORDER_SIZE	3

typedef struct		s_info
{
  int			x;
  int			y;
  float			size;
}			t_info;

class			Broadcast
{
private:
  std::list<t_info>	_infoList;
  sf::CircleShape	_circle;

public:
  Broadcast();
  ~Broadcast();

  void			addBroadcast(int x, int y);
  void			draw(sf::RenderWindow &_win);
};
