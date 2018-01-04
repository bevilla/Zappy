/*
** cmd_voir.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 18:24:07 2015 Valentin Potier
** Last update Fri Jun 26 13:08:10 2015 Alexis Bevillard
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"zappy.h"
#include	"zappy/direction.h"
#include	"zappy/voir.h"
#include	"zappy/player.h"
#include	"zappy/error.h"

static void	change_x_y(enum e_direction direction, int *x, int *y)
{
  int		tmp;

  if (direction == EAST)
    {
      tmp = *x;
      *x = -(*y);
      *y = tmp;
    }
  else if (direction == SOUTH)
    {
      *y = -(*y);
      *x = -(*x);
    }
  else if (direction == WEST)
    {
      tmp = (*y);
      *y = -(*x);
      *x = tmp;
    }
}

static t_cell	*get_voir_cell(t_player *player, int x, int y)
{
  int		x_cell;
  int		y_cell;

  change_x_y(player->direction, &x, &y);
  x_cell = player->x + x;
  if (x_cell >= g_zappy->width)
    x_cell = x_cell % g_zappy->width;
  else if (x_cell < 0)
    x_cell = (g_zappy->width - (-x_cell % g_zappy->width)) % g_zappy->width;
  y_cell = player->y + y;
  if (y_cell >= g_zappy->height)
    y_cell = y_cell % g_zappy->height;
  else if (y_cell < 0)
    y_cell = (g_zappy->height - (-y_cell % g_zappy->height)) % g_zappy->height;
  return (&(g_zappy->map[y_cell][x_cell]));
}

static int	append_cell_to_str(char **str, t_player *player, int y, int x)
{
  t_cell	*cell;
  int		err;

  cell = get_voir_cell(player, x, y);
  if ((err = append_players_to_str(str, cell->players)))
    return (err);
  if ((err = append_items_to_str(str, cell->items)))
    return (err);
  return (0);
}

int		zappy_voir(t_player *player)
{
  char		*str;
  int		i;
  int		j;
  int		err;

  str = NULL;
  if (append_to_str(&str, "{"))
    return (server_error(MALLOC_ERR));
  i = -1;
  while (++i <= player->vision)
    {
      j = -i - 1;
      while (++j <= i)
	{
	  if ((err = append_cell_to_str(&str, player, -i, j)))
	    return (err);
	  if ((i != player->vision || j != i) && append_to_str(&str, ","))
	    return (server_error(MALLOC_ERR));
	}
    }
  if (append_to_str(&str, "}\n"))
    return (server_error(MALLOC_ERR));
  send_message(player, str);
  free(str);
  return (0);
}
