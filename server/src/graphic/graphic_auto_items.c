/*
** graphic_auto_items.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Sat Jun 27 15:56:58 2015 Valentin Potier
** Last update Sat Jun 27 16:01:58 2015 Valentin Potier
*/

#define		_GNU_SOURCE
#include	<stdio.h>
#include	"zappy.h"

int		graphic_pdr(t_player *player, int item)
{
  char		buf[32];

  snprintf(buf, sizeof(buf), "pdr %d %d\n", player->id, item);
  send_to_graphics(buf);
  return (0);
}

int		graphic_pgt(t_player *player, int item)
{
  char		buf[32];

  snprintf(buf, sizeof(buf), "pgt %d %d\n", player->id, item);
  send_to_graphics(buf);
  return (0);
}
