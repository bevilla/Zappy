/*
** server_exec.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 19:49:10 2015 Valentin Potier
** Last update Fri Jul  3 18:00:54 2015 Alexis Bevillard
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		<string.h>
#include		"zappy.h"
#include		"zappy/error.h"
#include		"zappy/player.h"
#include		"zappy/update.h"
#include		"zappy/incantation.h"

void			update_nourriture()
{
  double		diff;
  struct timeval	tv;
  int			i;
  int			x;
  int			y;

  gettimeofday(&tv, NULL);
  tv.tv_sec = tv.tv_sec - g_zappy->nourriture_pop.tv_sec;
  tv.tv_usec = tv.tv_usec - g_zappy->nourriture_pop.tv_usec;
  diff = (double)tv.tv_sec + tv.tv_usec / 1000000.0;
  if (diff >= 300 / (double)g_zappy->delay)
    {
      i = g_zappy->width * g_zappy->height / 2 + 1;
      while (i--)
	{
	  x = rand() % g_zappy->width;
	  y = rand() % g_zappy->height;
	  if (g_zappy->map[y][x].items[NOURRITURE] < 4)
	    g_zappy->map[y][x].items[NOURRITURE]++;
	}
      gettimeofday(&(g_zappy->nourriture_pop), NULL);
    }
}

static int		getoklen(int tok)
{
  return (g_zappy->exec.lens[tok]);
}

static int		can_do_action(int tok, t_action *action)
{
  double		diff;
  struct timeval	d;

  gettimeofday(&d, NULL);
  d.tv_sec = d.tv_sec - action->tv.tv_sec;
  d.tv_usec = d.tv_usec - action->tv.tv_usec;
  diff = (double)d.tv_sec + d.tv_usec / 1000000.0;
  if (diff >= g_zappy->exec.delays[tok])
    return (1);
  return (0);
}

static int		playeractiontok(t_action *action)
{
  int			i;

  i = -1;
  while (++i < F_SUM)
    if (!strncmp(action->msg, g_zappy->exec.ptabstr[i],
		 strlen(g_zappy->exec.ptabstr[i])))
      return (i);
  return (-1);
}

int			exec_player_action(t_player *player, t_action *action)
{
  int			tok;

  if ((tok = playeractiontok(action)) < 0)
    return (send_message(player, "ko\n"));
  if (tok == F_INCANTATION && action->flag &&
      !cmp_cell_incantation(&(g_zappy->map[player->y][player->x]),
			    player->level))
    {
      send_message(player, "elevation en cours\n");
      if (graphic_pic(player->x, player->y, player->level,
		      g_zappy->map[player->y][player->x].players))
	return (MALLOC_ERR);
    }
  else if (tok == F_INCANTATION && action->flag)
    return (send_message(player, "ko\n"));
  if (can_do_action(tok, action))
    {
      if (tok == F_PREND || tok == F_POSE || tok == F_BROADCAST)
	return (g_zappy->exec.pptr[tok](player,
					action->msg + getoklen(tok) + 1));
      return (g_zappy->exec.pptr[tok](player));
    }
  return (-1);
}
