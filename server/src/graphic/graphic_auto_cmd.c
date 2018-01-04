/*
** graphic_auto_cmd.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Sat Jun 27 16:53:30 2015 Valentin Potier
** Last update Sat Jun 27 16:58:21 2015 Valentin Potier
*/

#define		_GNU_SOURCE
#include	<stdio.h>
#include	"zappy.h"
#include	"graphic/server_graphic.h"

int		graphic_auto_ppo(t_player *player)
{
  char		buf[64];

  snprintf(buf, sizeof(buf), "ppo %d %d %d %d\n",
	   player->id,
	   player->x,
	   player->y,
	   player->direction);
  send_to_graphics(buf);
  return (0);
}

int		graphic_auto_plv(t_player *player)
{
  char		buf[32];

  snprintf(buf, sizeof(buf), "plv %d %d\n",
	   player->id,
	   player->level);
  send_to_graphics(buf);
  return (0);
}

int		graphic_auto_pin(t_player *player)
{
  char		buf[128];

  snprintf(buf, sizeof(buf), "pin %d %d %d %d %d %d %d %d %d %d\n",
	   player->id,
	   player->x,
	   player->y,
	   player->items[NOURRITURE],
	   player->items[LINEMATE],
	   player->items[DERAUMERE],
	   player->items[SIBUR],
	   player->items[MENDIANE],
	   player->items[PHIRAS],
	   player->items[THYSTAME]);
  send_to_graphics(buf);
  return (0);
}
