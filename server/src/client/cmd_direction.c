/*
** cmd_direction.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server/src/client
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 18:21:10 2015 Valentin Potier
** Last update Sat Jun 27 17:02:44 2015 Alexis Bevillard
*/

#include	<stdio.h>
#include	"zappy.h"
#include	"zappy/player.h"
#include	"zappy/error.h"
#include	"graphic/server_graphic.h"

int		zappy_avance(t_player *player)
{
  int	        x[WEST + 1];
  int	        y[WEST + 1];

  x[NORTH] = 0;
  x[EAST] = 1;
  x[SOUTH] = 0;
  x[WEST] = -1;
  y[NORTH] = -1;
  y[EAST] = 0;
  y[SOUTH] = 1;
  y[WEST] = 0;
  del_elem_list_no_free(&(g_zappy->map[player->y][player->x].players), player);
  player->x = (player->x + x[player->direction]) % g_zappy->width;
  player->y = (player->y + y[player->direction]) % g_zappy->height;
  player->x = player->x < 0 ? g_zappy->width - 1 : player->x;
  player->y = player->y < 0 ? g_zappy->height - 1 : player->y;
  if (add_front_elem_list(&(g_zappy->map[player->y][player->x].players),
			  player))
    return (server_error(MALLOC_ERR));
  send_message(player, "ok\n");
  graphic_auto_ppo(player);
  return (0);
}

int		zappy_droite(t_player *player)
{
  if (player->direction == WEST)
    player->direction = NORTH;
  else
    player->direction++;
  send_message(player, "ok\n");
  graphic_auto_ppo(player);
  return (0);
}

int		zappy_gauche(t_player *player)
{
  if (player->direction == NORTH)
    player->direction = WEST;
  else
    player->direction--;
  send_message(player, "ok\n");
  graphic_auto_ppo(player);
  return (0);
}
