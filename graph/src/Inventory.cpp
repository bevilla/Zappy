//
// Inventory.cpp for Inventory in /home/trupin_t/rendu/PSU_2014_zappy/graph
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Wed Jul  1 14:35:47 2015 Thomas Trupin
// Last update Sun Jul  5 10:11:55 2015 Louis Bouteillon
//

#include	<iostream>
#include	"Inventory.hpp"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{}

bool		Inventory::init()
{
  if (!_texture.loadFromFile(INVENTOR_SPRITE))
    {
      std::cerr << "Error : can't load inventory sprite" << std::endl;
      return (false);
    }
  _sprite.setTexture(_texture);
  _font.loadFromFile(INVENTOR_FONT);
  return (true);
}

void		Inventory::fill(int idPlayer, int x, int y, int *inventory, std::string team)
{
  _idPlayer = idPlayer;
  _team = team;
  for (int j = 0; j < 11; j++)
    _text[j].setFont(_font);
  for (int i = 0; i < 7; i++)
    {
      std::ostringstream	ma_stream;

      ma_stream << inventory[i];
      _text[i].setString(ma_stream.str());
      _text[i].setCharacterSize(CHAR_SIZE);
    }
  std::ostringstream	kek1;
  std::ostringstream	kek2;
  std::ostringstream	kek3;

  kek1 << x;
  kek2 << y;
  kek3 << idPlayer;
  _text[7].setString(kek1.str());
  _text[8].setString(kek2.str());
  _text[9].setString(kek3.str());
  _text[7].setCharacterSize(CHAR_SIZE);
  _text[8].setCharacterSize(CHAR_SIZE);
  _text[9].setCharacterSize(CHAR_SIZE);
  _text[10].setString(_team);
  _text[10].setCharacterSize(CHAR_SIZE);
}

void		Inventory::draw(sf::RenderWindow &window)
{
  int		y = 0;
  int		x = window.getSize().x - INVEN_W;

  _sprite.setPosition(x, y);
  window.draw(_sprite);
  for(int i = 0; i < 7; i ++)
    {
      _text[i].setPosition(x + 220, y + 81 + i * 37);
      window.draw(_text[i]);
    }
  _text[7].setPosition(x + 48, y + 35);
  _text[8].setPosition(x + 170, y + 36);
  _text[9].setPosition(x + 57, y + 11);
  _text[10].setPosition(x + 100, y + 11);
  window.draw(_text[7]);
  window.draw(_text[8]);
  window.draw(_text[9]);
  window.draw(_text[10]);
}
