/*
** new_client.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 20:00:06 2015 Valentin Potier
** Last update Sun Jul  5 15:36:56 2015 Alexis Bevillard
*/

#define		_GNU_SOURCE
#include	<string.h>
#include	<stdio.h>
#include	"zappy.h"
#include	"zappy/player.h"
#include	"zappy/error.h"
#include	"utils/color.h"
#include	"graphic/server_graphic.h"

static int	get_nb_player(char *team_name)
{
  t_list	*players;
  t_player	*player;
  int		nb;

  players = g_zappy->players;
  nb = 0;
  while (players)
    {
      player = players->data;
      if (player->team == team_name)
	nb++;
      players = players->next;
    }
  return (nb);
}

int		ghost_cx(t_player **player, char *team_name)
{
  t_list	*players;
  t_player	*cur_player;

  players = g_zappy->players;
  while (players)
    {
      cur_player = players->data;
      if (cur_player->team == team_name && cur_player->type == GHOST)
	{
	  PRINTF_YEL("Player %d takes over player %d at (%d,%d)\n",
		     (*player)->id, cur_player->id,
		     cur_player->x, cur_player->y);
	  new_log_message("* Player %d takes over player %d at (%d,%d)\n",
			  (*player)->id, cur_player->id,
			  cur_player->x, cur_player->y);
	  dump_player(*player, cur_player);
	  if (graphic_pnw(*player) || graphic_auto_pin(*player))
	    return (MALLOC_ERR);
	  cur_player->items[NOURRITURE] = 0;
	  return (0);
	}
      players = players->next;
    }
  return (-1);
}

int		set_team_name(t_player **player, t_action *action)
{
  int		nb_player;
  int		i;

  i = 0;
  while (i < g_zappy->nb_team)
    {
      if (!strcmp(g_zappy->team_name[i], action->msg))
	{
	  nb_player = get_nb_player(g_zappy->team_name[i]);
	  if (nb_player >= g_zappy->team_limit)
	    return (ghost_cx(player, g_zappy->team_name[i]));
	  (*player)->team = g_zappy->team_name[i];
	  if (graphic_pnw(*player) || graphic_auto_pin(*player))
	    return (MALLOC_ERR);
	  gettimeofday(&((*player)->last_meal), NULL);
	  return (0);
	}
      i++;
    }
  return (-1);
}

void		send_map_size(t_player *player)
{
  char		str[32];

  snprintf(str, 31, "%d %d\n", g_zappy->width, g_zappy->height);
  send_message(player, str);
}

int		check_new_player()
{
  int		new_client;
  int		err;

  if (FD_ISSET(g_zappy->fd, &(g_zappy->read.fds)))
    {
      if ((new_client = accept(g_zappy->fd, NULL, NULL)) < 0)
	return (server_error(ACCEPT_ERR));
      if ((err = init_new_player(new_client)))
	return (err);
      if (new_client > *(g_zappy->highest))
	*(g_zappy->highest) = new_client;
      g_zappy->read.fdl[g_zappy->read.fdl[0] + 1] = new_client;
      (*(g_zappy->read.fdl))++;
      g_zappy->write.fdl[g_zappy->write.fdl[0] + 1] = new_client;
      (*(g_zappy->write.fdl))++;
    }
  return (0);
}
