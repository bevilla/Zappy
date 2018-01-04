//
// Inventory.hpp for Inventory in /home/trupin_t/rendu/PSU_2014_zappy/graph
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Wed Jul  1 14:35:56 2015 Thomas Trupin
// Last update Sun Jul  5 19:27:41 2015 Louis Bouteillon
//

#ifndef INVENTORY_H_
# define INVENTORY_H_

#include	<sstream>
#include	<string>
#include	<cstdlib>
#include	<SFML/Graphics.hpp>

#define	INVENTOR_SPRITE	"./graph/resources/sprites/inventory.png"
#define	INVENTOR_FONT	"./graph/resources/fonts/SmoothieShoppe.ttf"
#define	CHAR_SIZE	20

#define	INVEN_W		260
#define	INVEN_H		350


class Inventory
{
public:
  Inventory();
  ~Inventory();

  bool	init();
void	fill(int idPlayer, int x, int y, int *inventory, std::string team);
  void	draw(sf::RenderWindow &window);

private:
  sf::Texture	_texture;
  sf::Sprite	_sprite;
  std::string	_team;
  sf::Font	_font;
  sf::Text	_text[11];
  int		_idPlayer;
};

#endif /*!INVENTORY_H_*/
