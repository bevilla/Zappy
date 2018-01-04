//
// ChatBox.cpp for zappy in /home/bevill_a/rendu/PSU_2014_zappy/graph
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Wed Jul  1 11:40:34 2015 Alexis Bevillard
// Last update Sun Jul  5 21:17:37 2015 Alexis Bevillard
//

#include	<iostream>
#include	"ChatBox.hpp"

#include <sstream>

ChatBox::ChatBox()
{
  _rectangle.setSize(sf::Vector2f(CHATBOX_X, CHATBOX_Y));
  _rectangle.setFillColor(sf::Color(0, 0, 0, 169));
  _rectangle.setOutlineThickness(3);
  _rectangle.setOutlineColor(sf::Color(255, 255, 255));

  _font.loadFromFile(CHATBOX_FONT);
  _text.setFont(_font);
  _text.setCharacterSize(FONT_SIZE);

  _colorTab[ChatBox::CHAT_WHITE] = sf::Color(255, 255, 255);
  _colorTab[ChatBox::CHAT_GREEN] = sf::Color(0, 255, 0);
  _colorTab[ChatBox::CHAT_RED] = sf::Color(255, 0, 0);
}

ChatBox::~ChatBox()
{
}

void		ChatBox::draw(sf::RenderWindow &win)
{
  int		x = CHATBOX_BORDER;
  int		y = win.getSize().y - _rectangle.getSize().y - (CHATBOX_BORDER * 4);

  _rectangle.setPosition(x, y);
  win.draw(_rectangle);
  y = y + CHATBOX_Y - FONT_SIZE - 7;

  std::list<ChatBox::color>::iterator color = _msgColor.begin();
  for (string_list::iterator it = _msgList.begin();
       it != _msgList.end();
       it++)
    {
      _text.setColor(_colorTab[*color]);
      _text.setString(*it);
      _text.setPosition(x, y);
      win.draw(_text);
      y -= FONT_SIZE;
      color++;
    }
}

void		ChatBox::addString(ChatBox::color color, const std::string &str)
{
  _msgList.push_front(str);
  _msgColor.push_front(color);
  if (_msgList.size() > MSG_LIMIT)
    {
      _msgList.pop_back();
      _msgColor.pop_back();
    }
}
