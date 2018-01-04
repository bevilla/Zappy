//
// Camera.cpp for Camera in /home/trupin_t/rendu/PSU_2014_zappy/graph
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Wed Jun 24 13:53:28 2015 Thomas Trupin
// Last update Fri Jul  3 18:25:44 2015 Alexis Bevillard
//

#include <iostream>
#include "Camera.hpp"
#include "Cell.hpp"

Camera::Camera() :
  _zoomLevel(1)
{
  for (int i = 0; i < CMD_NBR; i++)
    _cameraKey[i] = false;
  _view.setSize(W_WIDTH, W_HEIGHT);
  _zoomState = 1;
  _widthMap = 5;
  _heightMap = 5;
  _view.setCenter(_widthMap * SPRITE_W / 2, _heightMap * SPRITE_H / 2); // cast float ? Non
}

Camera::~Camera()
{}

void		Camera::event(sf::Event &event, sf::RenderWindow &window)
{
  eventKeyboard(event);
  eventMouse(event, window);
}

void		Camera::eventKeyboard(sf::Event &event)
{
  if (event.type == sf::Event::KeyPressed)
    {
      switch(event.key.code)
	{
	case sf::Keyboard::Left:
	  _cameraKey[LEFT] = true;
	  break;
	case sf::Keyboard::Right:
	  _cameraKey[RIGHT] = true;
	  break;
	case sf::Keyboard::Up:
	  _cameraKey[UP] = true;
	  break;
	case sf::Keyboard::Down:
	  _cameraKey[DOWN] = true;
	  break;
	case sf::Keyboard::Add:
	  _cameraKey[ZOOM_IN] = true;
	  break;
	case sf::Keyboard::Subtract:
	  _cameraKey[ZOOM_OUT] = true;
	  break;
	default:
	  break;
	}
    }
  else if (event.type == sf::Event::KeyReleased)
    {
      switch(event.key.code)
	{
	case sf::Keyboard::Left:
	  _cameraKey[LEFT] = false;
	  break;
	case sf::Keyboard::Right:
	  _cameraKey[RIGHT] = false;
	  break;
	case sf::Keyboard::Up:
	  _cameraKey[UP] = false;
	  break;
	case sf::Keyboard::Down:
	  _cameraKey[DOWN] = false;
	  break;
	case sf::Keyboard::Add:
	  _cameraKey[ZOOM_IN] = false;
	  break;
	case sf::Keyboard::Subtract:
	  _cameraKey[ZOOM_OUT] = false;
	  break;
	default:
	  break;
	}
    }
}

void		Camera::eventMouse(sf::Event &event, sf::RenderWindow &window)
{
  sf::Vector2i	mousePos;

  mousePos = sf::Mouse::getPosition(window);
  (mousePos.x < EDGE_X && mousePos.x > 0) ?
    _cameraKey[LEFT_M] = true : _cameraKey[LEFT_M] = false;
  (mousePos.x > W_WIDTH - EDGE_X && mousePos.x < W_WIDTH) ?
    _cameraKey[RIGHT_M] = true : _cameraKey[RIGHT_M] = false;
  (mousePos.y < EDGE_Y && mousePos.y > 0) ?
    _cameraKey[UP_M] = true : _cameraKey[UP_M] = false;
  (mousePos.y > W_HEIGHT - EDGE_Y && mousePos.y < W_HEIGHT) ?
    _cameraKey[DOWN_M] = true : _cameraKey[DOWN_M] = false;
  if (event.type == sf::Event::MouseWheelMoved)
    {
      if (event.mouseWheel.delta == 1)
	{
	  _cameraKey[ZOOM_IN_M] = true;
	  _cameraKey[ZOOM_OUT_M] = false;
	}
      else if (event.mouseWheel.delta == -1)
	{
	  _cameraKey[ZOOM_IN_M] = false;
	  _cameraKey[ZOOM_OUT_M] = true;
	}
    }
}

void		Camera::update()
{
  updateMove();
  updateZoom();
}

void		Camera::updateMove()
{
  int		speed;
  int		offsetX;
  int	 	offsetY;

  speed = CAMERA_SPEED * ((_zoomLevel < 0.5) ? 0.5 : (_zoomLevel > 1.5) ? 1.5 : _zoomLevel);
  offsetX = 0;
  offsetY = 0;
  if ((_cameraKey[UP] || _cameraKey[UP_M]) &&
      _view.getCenter().y > W_HEIGHT / 3)
    offsetY -= speed;
  if ((_cameraKey[DOWN] || _cameraKey[DOWN_M]) &&
      _view.getCenter().y < (SPRITE_H * _heightMap - W_HEIGHT / 3))
    offsetY += speed;
  if ((_cameraKey[LEFT] || _cameraKey[LEFT_M]) &&
      _view.getCenter().x > W_WIDTH / 3)
    offsetX -= speed;
  if ((_cameraKey[RIGHT] || _cameraKey[RIGHT_M]) &&
      _view.getCenter().x < (SPRITE_W * _widthMap - W_WIDTH / 3))
    offsetX += speed;
  _view.move(offsetX, offsetY);
}

void		Camera::updateZoom()
{
  if (_cameraKey[ZOOM_IN] || _cameraKey[ZOOM_IN_M])
    {
      _cameraKey[ZOOM_IN_M] = false;
      if (_zoomLevel >= -1)
	{
	  _zoomLevel -= ZOOM_STEP;
	  _view.zoom(1 - ZOOM_STEP);
	  _zoomState *= 1 + ZOOM_STEP;
	}
    }
  if (_cameraKey[ZOOM_OUT] || _cameraKey[ZOOM_OUT_M])
    {
      _cameraKey[ZOOM_OUT_M] = false;
      if (_zoomLevel <= 1.5)
	{
	  _zoomLevel += ZOOM_STEP;
	  _view.zoom(1 + ZOOM_STEP);
	  _zoomState *= 1 - ZOOM_STEP;
	}
    }
}

sf::View	&Camera::getView()
{
  return	_view;
}

double		Camera::getZoomState() const
{
  return (_zoomState);
}

void		Camera::setWidthMap(int widthMap)
{
  _widthMap = widthMap;
  _view.setCenter(_widthMap * SPRITE_W / 2, _heightMap * SPRITE_H / 2); // cast float ? Non
}

void		Camera::setHeightMap(int heightMap)
{
  _heightMap = heightMap;
  _view.setCenter(_widthMap * SPRITE_W / 2, _heightMap * SPRITE_H / 2); // cast float ? Non
}
