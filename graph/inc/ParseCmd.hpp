//
// ParseCmd.hpp for zappy in /home/bevill_a/test/socket_cpp
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Mon Jun 29 17:58:44 2015 Alexis Bevillard
// Last update Wed Jul  1 16:27:18 2015 Alexis Bevillard
//

#pragma once

#include			<string>
#include			<list>
#include			<map>

class				Window;

class				ParseCmd
{

#define FUNCMAP_INIT(v, f)      _ ## v ## Func[#f] = &ParseCmd::v ## _ ## f

public:
  enum				ressource
    {
      RES_NOURRITURE,
      RES_LINEMATE,
      RES_DERAUMERE,
      RES_SIBUR,
      RES_MENDIANE,
      RES_PHIRAS,
      RES_THYSTAME,
      NB_RESSOURCE
    };
  enum				orientation
    {
      ORI_NORTH = 1,
      ORI_EST,
      ORI_SOUTH,
      ORI_WEST
    };

private:
  typedef bool			(ParseCmd::*MFPP)(const std::string &msg);
  typedef bool		        (ParseCmd::*MFPC)();
  std::map<std::string, MFPP>	_parseFunc;
  std::map<std::string, MFPC>	_callFunc;
  std::string			_funcName;
  int				_ressources[ParseCmd::NB_RESSOURCE];
  int				_idPlayer;
  int				_idEgg;
  int				_idItem;
  int				_x;
  int				_y;
  int				_orientation;
  int				_level;
  bool				_result;
  std::string			_msg;
  int				_time;
  std::list<int>		_list;
  int				_fd;
  Window			*_win;

public:
  ParseCmd();
  ~ParseCmd();

public:
  bool				parseMessage(const std::string &msg);
  bool				callFunc();
  void				setFd(int fd);
  void				setWindow(Window &win);

private:
  bool			        parse_BIENVENUE(const std::string &msg);
  bool			        parse_pgt(const std::string &msg);
  bool			        parse_pdr(const std::string &msg);
  bool			        parse_pex(const std::string &msg);
  bool			        parse_ppo(const std::string &msg);
  bool			        parse_plv(const std::string &msg);
  bool			        parse_pie(const std::string &msg);
  bool			        parse_pbc(const std::string &msg);
  bool			        parse_enw(const std::string &msg);
  bool			        parse_msz(const std::string &msg);
  bool			        parse_sgt(const std::string &msg);
  bool			        parse_tna(const std::string &msg);
  bool			        parse_eht(const std::string &msg);
  bool			        parse_pdi(const std::string &msg);
  bool			        parse_seg(const std::string &msg);
  bool			        parse_pnw(const std::string &msg);
  bool			        parse_pin(const std::string &msg);
  bool			        parse_pic(const std::string &msg);
  bool			        parse_bct(const std::string &msg);

private:
  bool				call_BIENVENUE();
  bool			        call_pgt();
  bool			        call_pdr();
  bool			        call_pex();
  bool			        call_ppo();
  bool			        call_plv();
  bool			        call_pie();
  bool			        call_pbc();
  bool			        call_enw();
  bool			        call_msz();
  bool			        call_sgt();
  bool			        call_tna();
  bool			        call_eht();
  bool			        call_pdi();
  bool			        call_seg();
  bool			        call_pnw();
  bool			        call_pin();
  bool			        call_pic();
  bool			        call_bct();
};
