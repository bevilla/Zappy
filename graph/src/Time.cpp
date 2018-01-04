//
// Time.cpp for zappy in /home/chardo_j/rendu/PSU_2014_zappy/graph/src
//
// Made by Julien Chardon
// Login   <chardo_j@epitech.net>
//
// Started on  Thu Jul  2 17:10:18 2015 Julien Chardon
// Last update Sun Jul  5 21:02:09 2015 Alexis Bevillard
//

#include <math.h>
#include "Time.hpp"
#include "Window.hpp"

Time::Time() :
  _oldTime(0),
  _saveOldTime(0),
  _onPause(false),
  _value(0),
  _true_save(0)
{
  if ((_imageIsLoaded = _texture.loadFromFile(TIME_IMAGE)))
    {
      _sprite.setTexture(_texture, true);
      _sprite.setScale(TIME_SCALE_X, TIME_SCALE_Y);
      _sprite.setColor(sf::Color(255, 255, 255, 128));
      _sprite.setPosition(TIME_POS_X, TIME_POS_Y);
    }
}

Time::~Time()
{}

void	Time::setWindow(Window &win)
{
  _win = &win;
}

void	Time::setPause()
{
  if (_oldTime > 0)
    _true_save = _oldTime;
  if (_onPause)
    {
      stopPause();
    }
  else
    {
      _win->sst(0);
      _onPause = true;
    }
}

void	Time::stopPause()
{
  _onPause = false;
  if (_true_save > 0)
    _win->sst(_true_save);
  else
    _win->sst(_saveOldTime);
}

void	Time::reduceTime()
{
  if (!_onPause)
    {
      _saveOldTime = _oldTime;
      if (_saveOldTime - TIME_STEP > 0)
	_saveOldTime -= TIME_STEP;
      _win->sst(_saveOldTime);
    }
}

void	Time::increaseTime()
{
  if (!_onPause)
    {
      _saveOldTime = _oldTime;
      if (_saveOldTime + TIME_STEP < 1000000)
	_saveOldTime += TIME_STEP;
      _win->sst(_saveOldTime);
    }
}

void	Time::setOldTime(int t)
{
  _saveOldTime = _oldTime;
  _oldTime = t;
}

int	Time::getOldTime() const
{
  return _oldTime;
}

void	Time::draw(sf::RenderWindow &win)
{
  if (_imageIsLoaded)
    win.draw(_sprite);
}

void	Time::eventClick(sf::Event &event)
{
  int	x = event.mouseButton.x;
  int	y = event.mouseButton.y;

  if (sqrt(pow(x - REDUCE_POS_X, 2) + pow(y - REDUCE_POS_Y, 2)) < REDUCE_RAD)
    reduceTime();
  if (sqrt(pow(x - PLAY_POS_X, 2) + pow(y - PLAY_POS_Y, 2)) < PLAY_RAD)
    setPause();
  if (sqrt(pow(x - INCREASE_POS_X, 2) + pow(y - INCREASE_POS_Y, 2)) < INCREASE_RAD)
    increaseTime();
}
