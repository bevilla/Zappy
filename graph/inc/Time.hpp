//
// Time.hpp for zappy in /home/chardo_j/rendu/PSU_2014_zappy/graph/src
//
// Made by Julien Chardon
// Login   <chardo_j@epitech.net>
//
// Started on  Thu Jul  2 17:10:51 2015 Julien Chardon
// Last update Sun Jul  5 21:01:39 2015 Alexis Bevillard
//

#pragma once

#ifndef TIME_HPP_
# define TIME_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/Graphics/Image.hpp>

# define TIME_STEP	3
# define TIME_IMAGE	"./graph/resources/sprites/time.png"
# define TIME_SCALE_X	0.5f
# define TIME_SCALE_Y	0.5f
# define TIME_POS_X	50
# define TIME_POS_Y	50

# define REDUCE_POS_X	50
# define REDUCE_POS_Y	60
# define REDUCE_RAD	18
# define PLAY_POS_X	122
# define PLAY_POS_Y	60
# define PLAY_RAD	36
# define INCREASE_POS_X	197
# define INCREASE_POS_Y	62
# define INCREASE_RAD	18

class Window;

class Time
{
public:
  Time();
  ~Time();

  void		setWindow(Window &win);

  void		setPause();
  void		stopPause();

  void		reduceTime();
  void		increaseTime();

  void		setOldTime(int t);

  int		getOldTime() const;

  void		draw(sf::RenderWindow &win);

  void		eventClick(sf::Event &event);

private:
  sf::Texture	_texture;
  sf::Sprite	_sprite;
  bool		_imageIsLoaded;
  int		_oldTime;
  int		_saveOldTime;
  bool		_onPause;
  Window	*_win;
  int		_value;
  int		_true_save;
};

#endif /* !TIME_HPP_ */
