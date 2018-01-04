//
// ParseCmd.cpp for zappy in /home/bevill_a/test/socket_cpp
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Mon Jun 29 18:00:49 2015 Alexis Bevillard
// Last update Fri Jul  3 18:35:30 2015 Alexis Bevillard
//

#include		<iostream>
#include		<sstream>
#include		<unistd.h>
#include		"ParseCmd.hpp"
#include		"Window.hpp"

ParseCmd::ParseCmd()
{
  FUNCMAP_INIT(parse, BIENVENUE);
  FUNCMAP_INIT(parse, pgt);
  FUNCMAP_INIT(parse, pdr);
  FUNCMAP_INIT(parse, pex);
  FUNCMAP_INIT(parse, ppo);
  FUNCMAP_INIT(parse, plv);
  FUNCMAP_INIT(parse, pie);
  FUNCMAP_INIT(parse, pbc);
  FUNCMAP_INIT(parse, enw);
  FUNCMAP_INIT(parse, msz);
  FUNCMAP_INIT(parse, sgt);
  FUNCMAP_INIT(parse, tna);
  FUNCMAP_INIT(parse, eht);
  FUNCMAP_INIT(parse, pdi);
  FUNCMAP_INIT(parse, seg);
  FUNCMAP_INIT(parse, pnw);
  FUNCMAP_INIT(parse, pin);
  FUNCMAP_INIT(parse, pic);
  FUNCMAP_INIT(parse, bct);

  FUNCMAP_INIT(call, BIENVENUE);
  FUNCMAP_INIT(call, pgt);
  FUNCMAP_INIT(call, pdr);
  FUNCMAP_INIT(call, pex);
  FUNCMAP_INIT(call, ppo);
  FUNCMAP_INIT(call, plv);
  FUNCMAP_INIT(call, pie);
  FUNCMAP_INIT(call, pbc);
  FUNCMAP_INIT(call, enw);
  FUNCMAP_INIT(call, msz);
  FUNCMAP_INIT(call, sgt);
  FUNCMAP_INIT(call, tna);
  FUNCMAP_INIT(call, eht);
  FUNCMAP_INIT(call, pdi);
  FUNCMAP_INIT(call, seg);
  FUNCMAP_INIT(call, pnw);
  FUNCMAP_INIT(call, pin);
  FUNCMAP_INIT(call, pic);
  FUNCMAP_INIT(call, bct);
}

ParseCmd::~ParseCmd()
{
}

bool			ParseCmd::parseMessage(const std::string &msg)
{
  size_t		pos;

  pos = (pos = msg.find(' ')) == msg.npos ? msg.size() : pos;
  _funcName = msg.substr(0, pos);
  if (_parseFunc.find(_funcName) == _parseFunc.end())
    {
      std::cerr << "Warning: '" << _funcName << "' is not a valid command" << std::endl;
      return false;
    }
  return (this->*(_parseFunc[_funcName]))(msg);
}

bool			ParseCmd::callFunc()
{
  if (_callFunc.find(_funcName) == _callFunc.end())
    {
      std::cerr << "Warning: '" << _funcName << "' is not a valid command" << std::endl;
      return false;
    }
  return (this->*(_callFunc[_funcName]))();
}

void			ParseCmd::setFd(int fd)
{
  _fd = fd;
}

void			ParseCmd::setWindow(Window &win)
{
  _win = &win;
}

/*
** Call functions
*/

bool			ParseCmd::call_BIENVENUE()
{
  if (write(_fd, "GRAPHIC\n", 8) < 0)
    return false;
  return true;
}

bool			ParseCmd::call_pgt()
{
  return _win->pgt(_idPlayer, _idItem);
}

bool			ParseCmd::call_pdr()
{
  return _win->pdr(_idPlayer, _idItem);
}

bool			ParseCmd::call_pex()
{
  return _win->pex(_idPlayer);
}

bool			ParseCmd::call_ppo()
{
  return _win->ppo(_idPlayer, _x, _y, _orientation);
}

bool			ParseCmd::call_plv()
{
  return _win->plv(_idPlayer, _level);
}

bool			ParseCmd::call_pie()
{
  return _win->pie(_x, _y, _result);
}

bool			ParseCmd::call_pbc()
{
  return _win->pbc(_idPlayer, _msg);
}

bool			ParseCmd::call_enw()
{
  return _win->enw(_idEgg, _idPlayer, _x, _y);
}

bool			ParseCmd::call_msz()
{
  return _win->msz(_x, _y);
}

bool			ParseCmd::call_sgt()
{
  return _win->sgt(_time);
}

bool			ParseCmd::call_tna()
{
  std::cout << "call " << _funcName << std::endl;
  return true;
}

bool			ParseCmd::call_eht()
{
  std::cout << "call " << _funcName << std::endl;
  return true;
}

bool			ParseCmd::call_pdi()
{
  return _win->pdi(_idPlayer);
}

bool			ParseCmd::call_seg()
{
  return _win->seg(_msg);
}

bool			ParseCmd::call_pnw()
{
  return _win->pnw(_idPlayer, _x, _y, _orientation, _level, _msg);
}

bool			ParseCmd::call_pin()
{
  return _win->pin(_idPlayer, _x, _y,
		   _ressources[RES_NOURRITURE],
		   _ressources[RES_LINEMATE],
		   _ressources[RES_DERAUMERE],
		   _ressources[RES_SIBUR],
		   _ressources[RES_MENDIANE],
		   _ressources[RES_PHIRAS],
		   _ressources[RES_THYSTAME]);
}

bool			ParseCmd::call_pic()
{
  return _win->pic(_x, _y, _level, _list);
}

bool			ParseCmd::call_bct()
{
  return _win->bct(_x, _y,
		   _ressources[RES_NOURRITURE],
		   _ressources[RES_LINEMATE],
		   _ressources[RES_DERAUMERE],
		   _ressources[RES_SIBUR],
		   _ressources[RES_MENDIANE],
		   _ressources[RES_PHIRAS],
		   _ressources[RES_THYSTAME]);
}

/*
** Parse functions
*/

bool			ParseCmd::parse_BIENVENUE(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  _msg = "GRAPHIC";
  std::cout << "parse GRAPHIC" << std::endl;
  return true;
}

bool			ParseCmd::parse_pgt(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _idPlayer))
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _idItem))
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_pdr(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _idPlayer))
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _idItem))
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_pex(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _idPlayer) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_ppo(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _idPlayer) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _x) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _y) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _orientation) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_plv(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _idPlayer) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _level) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_pie(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _x) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _y) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _result) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_pbc(const std::string &msg)
{
  std::istringstream	iss(msg);
  std::string		tmp;

  iss >> _funcName;
  if (!(iss >> _idPlayer) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  _msg = iss.str().substr(1 + iss.tellg());
  return true;
}

bool			ParseCmd::parse_enw(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _idEgg) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _idPlayer) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _x) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _y) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_msz(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _x) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _y) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_sgt(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _time) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_tna(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  _msg = iss.str().substr(1 + iss.tellg());
  return true;
}

bool			ParseCmd::parse_eht(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _idEgg) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_pdi(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _idPlayer) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_seg(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  _msg = iss.str().substr(1 + iss.tellg());
  return true;
}

bool			ParseCmd::parse_pnw(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _idPlayer) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _x) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _y) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _orientation) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _level) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  _msg = iss.str().substr(1 + iss.tellg());
  return true;
}

bool			ParseCmd::parse_pin(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _idPlayer) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _x) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _y) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_NOURRITURE]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_LINEMATE]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_DERAUMERE]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_SIBUR]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_MENDIANE]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_PHIRAS]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_THYSTAME]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_pic(const std::string &msg)
{
  std::istringstream	iss(msg);
  int			nb;

  _list.clear();
  iss >> _funcName;
  if (!(iss >> _x) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _y) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _level) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  nb = -1;
  while (!(iss >> nb) != NULL)
    _list.push_back(nb);
  if (nb < 0)
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}

bool			ParseCmd::parse_bct(const std::string &msg)
{
  std::istringstream	iss(msg);

  iss >> _funcName;
  if (!(iss >> _x) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _y) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_NOURRITURE]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_LINEMATE]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_DERAUMERE]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_SIBUR]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_MENDIANE]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_PHIRAS]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  if (!(iss >> _ressources[ParseCmd::RES_THYSTAME]) )
    {
      std::cout << "Warning: invalid args for " << _funcName << " command" << std::endl;
      return false;
    }
  return true;
}
