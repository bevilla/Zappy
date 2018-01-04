/*
** cmd_fork.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
** 
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
** 
** Started on  Sat Jun 27 15:41:15 2015 Alexis Bevillard
** Last update Sat Jun 27 17:16:34 2015 Alexis Bevillard
*/

#include	"zappy.h"
#include	"zappy/player.h"

int		zappy_fork(t_player *player)
{
  int		err;

  if ((err = init_new_egg(player)))
    return (err);
  send_message(player, "ok\n");
  graphic_enw(g_zappy->players->last->data);
  return (0);
}
