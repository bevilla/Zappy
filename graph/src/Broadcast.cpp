//
// Broadcast.cpp for zappy in /home/bevill_a/rendu/PSU_2014_zappy/graph
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Sat Jul  4 10:35:22 2015 Alexis Bevillard
// Last update Sun Jul  5 11:25:36 2015 Louis Bouteillon
//

#include	"Cell.hpp"
#include	"Broadcast.hpp"

Broadcast::Broadcast()
{
}

Broadcast::~Broadcast()
{
}

void		Broadcast::addBroadcast(int x, int y)
{
  t_info	info;

  info.x = x;
  info.y = y;
  info.size = MIN_CIRCLE_SIZE;
  _infoList.push_back(info);
}

void		Broadcast::draw(sf::RenderWindow &_win)
{
  sf::CircleShape	_circle;

  for (std::list<t_info>::iterator it = _infoList.begin();
       it != _infoList.end();
       ++it)
    {
      _circle.setRadius(it->size);
      _circle.setPosition(it->x - it->size + SPRITE_W / 2, it->y - it->size + SPRITE_H / 2);
      _circle.setOutlineThickness(BORDER_SIZE);
      _circle.setFillColor(sf::Color(0, 0, 0, 0));
      _circle.setOutlineColor(CIRCLE_COLOR);
      _win.draw(_circle);
      it->size += CIRCLE_STEP;
      if (it->size > MAX_CIRCLE_SIZE)
        _infoList.erase(it--);
    }
}
