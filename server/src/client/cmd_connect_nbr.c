/*
** cmd_connect_nbr.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 19:29:33 2015 Valentin Potier
** Last update Fri Jul  3 14:24:56 2015 Alexis Bevillard
*/

#define		_GNU_SOURCE
#include	<string.h>
#include        <stdio.h>
#include	"utils/list.h"
#include	"zappy.h"
#include	"zappy/player.h"
#include	"zappy/t_fd.h"

int		zappy_connect_nbr(t_player *player)
{
  t_list	*players;
  t_player	*cur_player;
  int		nb;
  char		str[16];

  nb = 0;
  players = g_zappy->players;
  while (players)
    {
      cur_player = players->data;
      if (cur_player->team)
	if (!strcmp(cur_player->team, player->team) &&
	    cur_player->type == PLAYER)
	  nb++;
      players = players->next;
    }
  nb = g_zappy->team_limit - nb;
  snprintf(str, 15, "%d\n", nb);
  send_message(player, str);
  return (0);
}
