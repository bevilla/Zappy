/*
** get_graphic_args.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Sat Jun 27 10:47:08 2015 Valentin Potier
** Last update Sat Jun 27 16:52:47 2015 Valentin Potier
*/

#define		_GNU_SOURCE
#include	<stdlib.h>
#include	<stdio.h>
#include	"zappy/error.h"
#include	"zappy.h"

int		get_int_from_msg(char *msg, int *nb)
{
  int		i;

  i = 0;
  while (msg[i] && msg[i] >= '0' && msg[i] <= '9')
    i++;
  if (msg[i])
    return (-1);
  *nb = atoi(msg);
  return (0);
}

int		get_bct_args(char *msg, int *x, int *y)
{
  int		back;
  int		i;

  i = 0;
  while (msg[i] && msg[i] >= '0' && msg[i] <= '9')
    i++;
  if (msg[i] != ' ')
    return (-1);
  msg[i] = 0;
  *x = atoi(msg);
  if (*x < 0 || *x > (g_zappy->width - 1))
    return (-1);
  i++;
  back = i;
  if (!msg[i])
    return (-1);
  while (msg[i] && msg[i] >= '0' && msg[i] <= '9')
    i++;
  if (msg[i])
    return (-1);
  *y = atoi(msg + back);
  if (*y < 0 || *y > (g_zappy->height - 1))
      return (-1);
  return (0);
}

t_player	*get_player_from_id(int id)
{
  t_player	*player;
  t_list	*tmp;

  tmp = g_zappy->players;
  while (tmp)
    {
      player = tmp->data;
      if (player->id == id)
	return (player);
      tmp = tmp->next;
    }
  return (NULL);
}

int		buf_pin(t_player *player, char **buf)
{
  if (asprintf(buf, "pin %d %d %d %d %d %d %d %d %d %d\n",
	       player->id,
	       player->x,
	       player->y,
	       player->items[NOURRITURE],
	       player->items[LINEMATE],
	       player->items[DERAUMERE],
	       player->items[SIBUR],
	       player->items[MENDIANE],
	       player->items[PHIRAS],
	       player->items[THYSTAME]) < 0)
    return (server_error(MALLOC_ERR));
  return (0);
}
