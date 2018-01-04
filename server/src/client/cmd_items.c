/*
** cmd_items.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 18:42:13 2015 Valentin Potier
** Last update Sat Jun 27 17:28:47 2015 Alexis Bevillard
*/

#define		_GNU_SOURCE
#include	<string.h>
#include	<stdio.h>
#include	"zappy.h"
#include	"zappy/player.h"
#include	"zappy/error.h"

int		zappy_inventaire(t_player *player)
{
  char		*str;

  if (asprintf(&str,
	       "{nourriture %d,linemate %d,deraumere %d,sibur %d, \
mendiane %d,phiras %d, thystame %d}\n",
	       player->items[NOURRITURE],
	       player->items[LINEMATE],
	       player->items[DERAUMERE],
	       player->items[SIBUR],
	       player->items[MENDIANE],
	       player->items[PHIRAS],
	       player->items[THYSTAME]) < 0)
    return (server_error(MALLOC_ERR));
  send_message(player, str);
  return (0);
}

static void	init_items_str(char *items_str[NB_ITEM])
{
  items_str[NOURRITURE] = "nourriture";
  items_str[LINEMATE] = "linemate";
  items_str[DERAUMERE] = "deraumere";
  items_str[SIBUR] = "sibur";
  items_str[MENDIANE] = "mendiane";
  items_str[PHIRAS] = "phiras";
  items_str[THYSTAME] = "thystame";
}

int		zappy_prend(t_player *player, char *str)
{
  t_cell	*cell;
  char		*items_str[NB_ITEM];
  int		i;

  init_items_str(items_str);
  cell = &(g_zappy->map[player->y][player->x]);
  i = -1;
  while (++i < NB_ITEM)
    if (!strcmp(items_str[i], str))
      {
	if (cell->items[i] > 0)
	  {
	    (cell->items[i])--;
	    (player->items[i])++;
	    graphic_pgt(player, i);
	    return (send_message(player, "ok\n"));
	  }
	else
	  return (send_message(player, "ko\n"));
      }
  send_message(player, "ko\n");
  return (0);
}

int		zappy_pose(t_player *player, char *str)
{
  t_cell	*cell;
  char		*items_str[NB_ITEM];
  int		i;

  init_items_str(items_str);
  cell = &(g_zappy->map[player->y][player->x]);
  i = -1;
  while (++i < NB_ITEM)
    if (!strcmp(items_str[i], str))
      {
	if (player->items[i] > 0)
	  {
	    (player->items[i])--;
	    (cell->items[i])++;
	    graphic_pdr(player, i);
	    return (send_message(player, "ok\n"));
	  }
	else
	  return (send_message(player, "ko\n"));
      }
  send_message(player, "ko\n");
  return (0);
}
