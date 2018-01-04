/*
** graphic_auto_power.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Sat Jun 27 15:44:54 2015 Valentin Potier
** Last update Sat Jun 27 17:39:25 2015 Alexis Bevillard
*/

#define		_GNU_SOURCE
#include	<string.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	"zappy/error.h"
#include	"zappy.h"

int		graphic_pex(t_player *player)
{
  char		buf[16];

  snprintf(buf, sizeof(buf), "pex %d\n", player->id);
  send_to_graphics(buf);
  return (0);
}

int		graphic_pbc(t_player *player, char *msg)
{
  char		*buf;

  if (asprintf(&buf, "pbc %d %s\n", player->id, msg) < 0)
    return (server_error(MALLOC_ERR));
  send_to_graphics(buf);
  free(buf);
  return (0);
}

int		graphic_pic(int x, int y, int lvl, t_list *players)
{
  t_player	*player;
  char		*buf;
  char		*tmp;

  if (asprintf(&buf, "pic %d %d %d", x, y, lvl) < 0)
    return (server_error(MALLOC_ERR));
  while (players)
    {
      player = players->data;
      if (!(tmp = strdup(buf)))
	return (server_error(MALLOC_ERR));
      free(buf);
      if (asprintf(&buf, "%s %d%s", tmp, player->id,
		   players->next ? "" : "\n") < 0)
	return (server_error(MALLOC_ERR));
      free(tmp);
      players = players->next;
    }
  send_to_graphics(buf);
  free(buf);
  return (0);
}

int		graphic_pie(int x, int y, int res)
{
  char		buf[32];

  snprintf(buf, sizeof(buf), "pie %d %d %d\n", x, y, res);
  send_to_graphics(buf);
  return (0);
}
