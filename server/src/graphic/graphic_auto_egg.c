/*
** graphic_auto_egg.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Sat Jun 27 11:52:52 2015 Valentin Potier
** Last update Sat Jun 27 16:01:39 2015 Valentin Potier
*/

#define		_GNU_SOURCE
#include	<stdio.h>
#include	"zappy.h"

int		graphic_pfk(t_player *player)
{
  char		buf[16];

  snprintf(buf, sizeof(buf), "pfk %d\n", player->id);
  send_to_graphics(buf);
  return (0);
}

int		graphic_enw(t_player *egg)
{
  char		buf[64];

  snprintf(buf, sizeof(buf), "enw %d %d %d %d\n",
	   egg->id, egg->father->id, egg->x, egg->y);
  send_to_graphics(buf);
  return (0);
}

int		graphic_eht(t_player *egg)
{
  char		buf[16];

  snprintf(buf, sizeof(buf), "eht %d\n", egg->id);
  send_to_graphics(buf);
  return (0);
}

int		graphic_ebo(t_player *egg)
{
  char		buf[16];

  snprintf(buf, sizeof(buf), "ebo %d\n", egg->id);
  send_to_graphics(buf);
  return (0);
}
