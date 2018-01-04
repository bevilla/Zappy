/*
** graphic_auto_items.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Sat Jun 27 15:14:14 2015 Valentin Potier
** Last update Wed Jul  1 17:59:07 2015 Alexis Bevillard
*/

#define		_GNU_SOURCE
#include	<stdio.h>
#include	<stdlib.h>
#include	"zappy/error.h"
#include	"zappy.h"

int		graphic_send_players2(t_player *graphic, t_player *player)
{
  char		*buf;

  if (asprintf(&buf, "pnw %d %d %d %d %d %s\n", player->id, player->x,
	       player->y, player->direction, player->level,
	       player->team) < 0)
    return (server_error(MALLOC_ERR));
  send_message(graphic, buf);
  free(buf);
  if (asprintf(&buf, "pin %d %d %d %d %d %d %d %d %d %d\n", player->id,
	       player->x, player->y, player->items[NOURRITURE],
	       player->items[LINEMATE], player->items[DERAUMERE],
	       player->items[SIBUR], player->items[MENDIANE],
	       player->items[PHIRAS], player->items[THYSTAME]) < 0)
    return (server_error(MALLOC_ERR));
  send_message(graphic, buf);
  free(buf);
  return (0);
}

int		graphic_send_players(t_player *graphic)
{
  t_list	*players;
  t_player	*player;

  players = g_zappy->players;
  while (players)
    {
      player = players->data;
      if (player->type != GRAPHIC)
	if (graphic_send_players2(graphic, player))
	  return (MALLOC_ERR);
      players = players->next;
    }
  return (0);
}

int		graphic_pnw(t_player *player)
{
  char		*buf;

  if (asprintf(&buf, "pnw %d %d %d %d %d %s\n",
	       player->id,
	       player->x,
	       player->y,
	       player->direction,
	       player->level,
	       player->team) < 0)
    return (server_error(MALLOC_ERR));
  send_to_graphics(buf);
  free(buf);
  return (0);
}

int		graphic_seg(char *team)
{
  char		*buf;

  if (asprintf(&buf, "seg %s\n", team) < 0)
    return (server_error(MALLOC_ERR));
  send_to_graphics(buf);
  free(buf);
  return (0);
}

int		graphic_pdi(t_player *player)
{
  char		buf[16];

  snprintf(buf, sizeof(buf), "pdi %d\n", player->id);
  send_to_graphics(buf);
  return (0);
}
