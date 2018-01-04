/*
** cmd_expulse.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 18:46:00 2015 Valentin Potier
** Last update Sun Jun 28 17:57:11 2015 Alexis Bevillard
*/

#include	<stdio.h>
#include	"zappy.h"
#include	"zappy/player.h"
#include	"zappy/error.h"

int		convert_cell(t_player *player, int cell)
{
  int		tab[4];

  tab[NORTH - 1] = 0;
  tab[EAST - 1] = 2;
  tab[SOUTH - 1] = 4;
  tab[WEST - 1] = 6;
  return ((cell + tab[player->direction - 1]) % 8);
}

static void	print_deplacement_expulse(t_player *player, t_player *expulsed)
{
  char		buf[32];
  int		cell;

  if (expulsed->x == player->x && expulsed->y == player->y)
    cell = 0;
  else if (expulsed->x == player->x)
    cell = expulsed->y == (player->y + 1) % g_zappy->height ? 5 : 1;
  else
    cell = expulsed->x == (player->x + 1) % g_zappy->width ? 7 : 3;
  cell = convert_cell(expulsed, cell);
  snprintf(buf, sizeof(buf), "deplacement: %d\n", cell);
  send_message(expulsed, buf);
  graphic_auto_ppo(expulsed);
}

static int	expulse_player(t_player *player, t_player *cur_player)
{
  int	        x[WEST + 1];
  int	        y[WEST + 1];
  t_cell	**map;

  x[NORTH] = 0;
  x[EAST] = 1;
  x[SOUTH] = 0;
  x[WEST] = -1;
  y[NORTH] = -1;
  y[EAST] = 0;
  y[SOUTH] = 1;
  y[WEST] = 0;
  del_elem_list_no_free(&(g_zappy->map[cur_player->y][cur_player->x].players),
			cur_player);
  cur_player->x = (player->x + x[player->direction]) % g_zappy->width;
  cur_player->y = (player->y + y[player->direction]) % g_zappy->height;
  cur_player->x = cur_player->x < 0 ? g_zappy->width - 1 : cur_player->x;
  cur_player->y = cur_player->y < 0 ? g_zappy->height - 1 : cur_player->y;
  map = g_zappy->map;
  if (add_front_elem_list(&(map[cur_player->y][cur_player->x].players),
			  cur_player))
    return (server_error(MALLOC_ERR));
  print_deplacement_expulse(player, cur_player);
  return (0);
}

int		zappy_expulse(t_player *player)
{
  t_cell	*cell;
  t_list	*players;
  t_player	*cur_player;
  int		err;
  int		flag;

  flag = 0;
  cell = &(g_zappy->map[player->y][player->x]);
  players = cell->players;
  while (players)
    {
      cur_player = players->data;
      if (cur_player != player)
	{
	  players = players->next;
	  if ((err = expulse_player(player, cur_player)))
	    return (err);
	  flag = 1;
	}
      if (players)
	players = players->next;
    }
  send_message(player, flag ? "ok\n" : "ko\n");
  graphic_pex(player);
  return (0);
}
