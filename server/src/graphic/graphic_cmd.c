/*
** graphic_cmd.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 17:31:11 2015 Valentin Potier
** Last update Sun Jul  5 21:45:12 2015 Alexis Bevillard
*/

#define		_GNU_SOURCE
#include	<stdio.h>
#include	<stdlib.h>
#include	"zappy.h"
#include	"zappy/error.h"
#include	"zappy/player.h"
#include	"graphic/server_graphic.h"

int		graphic_msz(t_player *player)
{
  char		buf[64];

  snprintf(buf, sizeof(buf), "msz %d %d\n", g_zappy->width, g_zappy->height);
  send_message(player, buf);
  return (0);
}

int		graphic_mct(t_player *player)
{
  char		buf[64];
  int		i;
  int		j;

  j = 0;
  while (j < g_zappy->height)
    {
      i = 0;
      while (i < g_zappy->width)
	{
	  snprintf(buf, sizeof(buf), "%d %d", i, j);
	  graphic_bct(player, buf);
	  i++;
	}
      j++;
    }
  return (0);
}

int		graphic_tna(t_player *player)
{
  char		*team;
  int		i;

  i = 0;
  while (i < g_zappy->nb_team)
    {
      if (asprintf(&team, "tna %s\n", g_zappy->team_name[i]) < 0)
	return (server_error(MALLOC_ERR));
      send_message(player, team);
      free(team);
      i++;
    }
  return (0);
}

int		graphic_sgt(t_player *player)
{
  char		buf[32];

  snprintf(buf, sizeof(buf), "sgt %d\n", g_zappy->delay);
  send_message(player, buf);
  return (0);
}
