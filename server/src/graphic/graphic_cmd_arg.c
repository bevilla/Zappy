/*
** graphic_cmd.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 17:31:11 2015 Valentin Potier
** Last update Sun Jul  5 21:47:43 2015 Alexis Bevillard
*/

#define		_GNU_SOURCE
#include	<stdio.h>
#include	<stdlib.h>
#include	"zappy/error.h"
#include	"zappy/exec.h"
#include	"zappy.h"

int		graphic_bct(t_player *player, char *msg)
{
  char		*content;
  int		x;
  int		y;

  if (get_bct_args(msg, &x, &y))
    send_message(player, "suc\n");
  else
    {
      if (asprintf(&content, "bct %d %d %d %d %d %d %d %d %d\n",
		   x,
		   y,
		   g_zappy->map[y][x].items[NOURRITURE],
		   g_zappy->map[y][x].items[LINEMATE],
		   g_zappy->map[y][x].items[DERAUMERE],
		   g_zappy->map[y][x].items[SIBUR],
		   g_zappy->map[y][x].items[MENDIANE],
		   g_zappy->map[y][x].items[PHIRAS],
		   g_zappy->map[y][x].items[THYSTAME]) < 0)
	return (server_error(MALLOC_ERR));
      send_message(player, content);
      free(content);
    }
  return (0);
}

int		graphic_ppo(t_player *player, char *msg)
{
  t_player	*tmp;
  char		buf[64];
  int		nb;

  if (get_int_from_msg(msg, &nb))
    {
      send_message(player, "suc\n");
      return (0);
    }
  if (!(tmp = get_player_from_id(nb)) || tmp->type == GRAPHIC)
    {
      send_message(player, "sbp\n");
      return (0);
    }
  snprintf(buf, sizeof(buf), "ppo %d %d %d %d\n",
	   nb, tmp->x, tmp->y, tmp->direction);
  send_message(player, buf);
  return (0);
}

int		graphic_plv(t_player *player, char *msg)
{
  char		buf[32];
  t_player	*tmp;
  int		nb;

  if (get_int_from_msg(msg, &nb))
    {
      send_message(player, "suc\n");
      return (0);
    }
  if (!(tmp = get_player_from_id(nb)) || tmp->type == GRAPHIC)
    {
      send_message(player, "sbp\n");
      return (0);
    }
  snprintf(buf, sizeof(buf), "plv %d %d\n",
	   nb, tmp->level);
  send_message(player, buf);
  return (0);
}

int		graphic_pin(t_player *player, char *msg)
{
  t_player	*tmp;
  char		*buf;
  int		nb;

  if (get_int_from_msg(msg, &nb))
    {
      send_message(player, "suc\n");
      return (0);
    }
  if (!(tmp = get_player_from_id(nb)) || tmp->type == GRAPHIC)
    {
      send_message(player, "sbp\n");
      return (0);
    }
  if ((nb = buf_pin(tmp, &buf)))
      return (nb);
  send_message(player, buf);
  return (0);
}

int		graphic_sst(t_player *player, char *msg)
{
  char		buf[16];
  int		nb;

  if (get_int_from_msg(msg, &nb))
    {
      send_message(player, "suc\n");
      return (0);
    }
  if (nb >= 0)
    {
      g_zappy->delay = nb;
      init_player_delays();
    }
  snprintf(buf, sizeof(buf), "sgt %d\n", g_zappy->delay);
  g_zappy->is_paused = nb == 0 ? 1 : 0;
  send_message(player, buf);
  return (0);
}
