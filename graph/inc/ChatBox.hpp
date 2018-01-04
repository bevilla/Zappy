//
// ChatBox.hpp for zappy in /home/bevill_a/rendu/PSU_2014_zappy/graph
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Wed Jul  1 11:35:52 2015 Alexis Bevillard
// Last update Sun Jul  5 21:07:31 2015 Alexis Bevillard
//

#pragma once

#include		<SFML/Graphics.hpp>
#include		<SFML/Graphics/Text.hpp>
#include		<string>
#include		<list>

#define CHATBOX_BORDER	20
#define CHATBOX_X	400
#define CHATBOX_Y	210
#define CHATBOX_FONT	"./graph/resources/fonts/SmoothieShoppe.ttf"
#define FONT_SIZE       22
#define MSG_LIMIT       9

typedef std::list<std::string>  string_list;

class			ChatBox
{
public:
  enum			color
    {
      CHAT_WHITE,
      CHAT_GREEN,
      CHAT_RED,
      NB_COLOR
    };

private:
  sf::RectangleShape	_rectangle;
  sf::Font		_font;
  sf::Text		_text;
  string_list		_msgList;
  std::list<ChatBox::color> _msgColor;
  sf::Color		_colorTab[ChatBox::NB_COLOR];

public:
  ChatBox();
  ~ChatBox();

  void			draw(sf::RenderWindow &win);
  void			addString(ChatBox::color color, const std::string &str);
};
