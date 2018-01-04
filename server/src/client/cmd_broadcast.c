/*
** cmd_broadcast.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
** 
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
** 
** Started on  Sat Jun 27 15:42:27 2015 Alexis Bevillard
** Last update Fri Jul  3 17:45:02 2015 Alexis Bevillard
*/

#define		_GNU_SOURCE
#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>
#include	<math.h>
#include	"zappy.h"
#include	"zappy/error.h"
#include	"zappy/player.h"
#include	"zappy/broadcast.h"

double		get_alpha(t_point *from, t_point *to)
{
  double	alpha;
  double	convert[4];
  int		flag;

  convert[0] = 0.0;
  convert[1] = 90.0;
  convert[2] = 180.0;
  convert[3] = 270.0;
  flag = 0;
  if (from->x < to->x && from->y > to->y)
    flag = 1;
  else if (from->x >= to->x && from->y >= to->y)
    flag = 2;
  else if (from->x >= to->x && from->y <= to->y)
    flag = 3;
  if (from->x == to->x)
    alpha = 0.0;
  else if (from->y == to->y)
    alpha = 90.f;
  else
    alpha = 180.0 / M_PI * atan(fabs(from->x - to->x) / fabs(from->y - to->y));
  return (alpha + convert[flag]);
}

int		get_cell(double alpha)
{
  double	tab[8];
  int		i;

  tab[0] = 26.565;
  tab[1] = 63.435;
  tab[2] = 116.565;
  tab[3] = 153.435;
  tab[4] = 206.565;
  tab[5] = 243.435;
  tab[6] = 296.565;
  tab[7] = 333.435;
  i = -1;
  while (++i < 8)
    if (alpha < tab[i])
      return (i + 1);
  return (1);
}

int		convert_broadcast_cell(int cell, t_player *player)
{
  int		tab[4];

  tab[NORTH - 1] = 0;
  tab[EAST - 1] = 2;
  tab[SOUTH - 1] = 4;
  tab[WEST - 1] = 6;
  cell = cell + tab[player->direction - 1];
  if (cell > 8)
    cell = cell - 8;
  return (cell);
}

int		send_broadcast_msg(t_player *player, t_player *cur_player,
				   char *msg)
{
  t_point	from;
  t_point	to;
  char		*buf;
  int		cell;

  from.x = player->x;
  from.y = player->y;
  to.x = cur_player->x;
  to.y = cur_player->y;
  if (from.x == to.x && from.y == to.y)
    cell = 0;
  else
    cell = convert_broadcast_cell(get_cell(get_alpha(&from, &to)), cur_player);
  if (asprintf(&buf, "message %d,%s\n", cell, msg) < 0)
    {
      fprintf(stderr, "Error: malloc failed\n");
      return (MALLOC_ERR);
    }
  send_message(cur_player, buf);
  free(buf);
  return (0);
}

int		zappy_broadcast(t_player *player, char *msg)
{
  t_list	*players;
  t_player	*cur_player;
  int		err;

  if (strlen(msg) == 0)
    {
      send_message(player, "ko\n");
      return (0);
    }
  players = g_zappy->players;
  while (players)
    {
      cur_player = players->data;
      if (cur_player != player && cur_player->type == PLAYER)
	if ((err = send_broadcast_msg(player, cur_player, msg)))
	  return (err);
      players = players->next;
    }
  send_message(player, "ok\n");
  if ((err = graphic_pbc(player, msg)))
    return (err);
  return (0);
}
