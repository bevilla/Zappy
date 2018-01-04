//
// Camera.hpp for Camera in /home/trupin_t/rendu/PSU_2014_zappy/graph
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Wed Jun 24 13:46:12 2015 Thomas Trupin
// Last update Fri Jul  3 18:04:01 2015 Alexis Bevillard
//

#ifndef CAMERA_H_
# define CAMERA_H_

#include <SFML/Graphics.hpp>
#include "defWin.hpp"

#define	UP		0
#define	DOWN		1
#define	LEFT		2
#define	RIGHT		3
#define	ZOOM_IN		4
#define	ZOOM_OUT	5
#define	UP_M		6   //
#define	DOWN_M		7   // Touches différentes pour la souris
#define	RIGHT_M		8   // (pour utiliser souris et touches direc.
#define	LEFT_M		9   //  en même temps et sans bugs)
#define ZOOM_IN_M	10
#define ZOOM_OUT_M	11

#define CMD_NBR		12

#define CAMERA_SPEED	10
#define ZOOM_STEP	0.05
#define	EDGE_X		75      // La zone où la souris fait bouger la camera
#define	EDGE_Y		75

class Camera
{
public:
  Camera();
  ~Camera();

  void		event(sf::Event &event, sf::RenderWindow &window);
  void		update();

  sf::View	&getView();
  double	getZoomState() const;

  void		setWidthMap(int widthMap);
  void		setHeightMap(int heightMap);

private:
  void		eventKeyboard(sf::Event &event);
  void		eventMouse(sf::Event &event, sf::RenderWindow &window);

  void		updateMove();
  void		updateZoom();

protected:
  sf::View	_view;
  bool		_cameraKey[CMD_NBR];
  double	_zoomLevel;
  double	_zoomState;
  int		_widthMap;
  int		_heightMap;
};

#endif /*!CAMERA_H_*/
