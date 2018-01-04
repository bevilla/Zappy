/*
** cmd_incantation.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
** 
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
** 
** Started on  Sat Jun 27 08:44:25 2015 Alexis Bevillard
** Last update Sat Jun 27 17:03:54 2015 Alexis Bevillard
*/

#include	<stdio.h>
#include	"zappy.h"
#include	"zappy/player.h"
#include	"zappy/incantation.h"

void		init_incantation_tab1(int (*tab)[NB_LEVEL_INCANTATION])
{
  tab[LEVEL_1_TO_2][INC_NEEDED_PLAYER] = 1;
  tab[LEVEL_1_TO_2][INC_LINEMATE] = 1;
  tab[LEVEL_1_TO_2][INC_DERAUMERE] = 0;
  tab[LEVEL_1_TO_2][INC_SIBUR] = 0;
  tab[LEVEL_1_TO_2][INC_MENDIANE] = 0;
  tab[LEVEL_1_TO_2][INC_PHIRAS] = 0;
  tab[LEVEL_1_TO_2][INC_THYSTAME] = 0;
  tab[LEVEL_2_TO_3][INC_NEEDED_PLAYER] = 2;
  tab[LEVEL_2_TO_3][INC_LINEMATE] = 1;
  tab[LEVEL_2_TO_3][INC_DERAUMERE] = 1;
  tab[LEVEL_2_TO_3][INC_SIBUR] = 1;
  tab[LEVEL_2_TO_3][INC_MENDIANE] = 0;
  tab[LEVEL_2_TO_3][INC_PHIRAS] = 0;
  tab[LEVEL_2_TO_3][INC_THYSTAME] = 0;
  tab[LEVEL_3_TO_4][INC_NEEDED_PLAYER] = 2;
  tab[LEVEL_3_TO_4][INC_LINEMATE] = 2;
  tab[LEVEL_3_TO_4][INC_DERAUMERE] = 0;
  tab[LEVEL_3_TO_4][INC_SIBUR] = 1;
  tab[LEVEL_3_TO_4][INC_MENDIANE] = 0;
  tab[LEVEL_3_TO_4][INC_PHIRAS] = 2;
  tab[LEVEL_3_TO_4][INC_THYSTAME] = 0;
  tab[LEVEL_4_TO_5][INC_NEEDED_PLAYER] = 4;
  tab[LEVEL_4_TO_5][INC_LINEMATE] = 1;
  tab[LEVEL_4_TO_5][INC_DERAUMERE] = 1;
  tab[LEVEL_4_TO_5][INC_SIBUR] = 2;
}

void		init_incantation_tab2(int (*tab)[NB_LEVEL_INCANTATION])
{
  tab[LEVEL_4_TO_5][INC_MENDIANE] = 0;
  tab[LEVEL_4_TO_5][INC_PHIRAS] = 1;
  tab[LEVEL_4_TO_5][INC_THYSTAME] = 0;
  tab[LEVEL_5_TO_6][INC_NEEDED_PLAYER] = 4;
  tab[LEVEL_5_TO_6][INC_LINEMATE] = 1;
  tab[LEVEL_5_TO_6][INC_DERAUMERE] = 2;
  tab[LEVEL_5_TO_6][INC_SIBUR] = 1;
  tab[LEVEL_5_TO_6][INC_MENDIANE] = 3;
  tab[LEVEL_5_TO_6][INC_PHIRAS] = 0;
  tab[LEVEL_5_TO_6][INC_THYSTAME] = 0;
  tab[LEVEL_6_TO_7][INC_NEEDED_PLAYER] = 6;
  tab[LEVEL_6_TO_7][INC_LINEMATE] = 1;
  tab[LEVEL_6_TO_7][INC_DERAUMERE] = 2;
  tab[LEVEL_6_TO_7][INC_SIBUR] = 3;
  tab[LEVEL_6_TO_7][INC_MENDIANE] = 0;
  tab[LEVEL_6_TO_7][INC_PHIRAS] = 1;
  tab[LEVEL_6_TO_7][INC_THYSTAME] = 0;
  tab[LEVEL_7_TO_8][INC_NEEDED_PLAYER] = 6;
  tab[LEVEL_7_TO_8][INC_LINEMATE] = 2;
  tab[LEVEL_7_TO_8][INC_DERAUMERE] = 2;
  tab[LEVEL_7_TO_8][INC_SIBUR] = 2;
  tab[LEVEL_7_TO_8][INC_MENDIANE] = 2;
  tab[LEVEL_7_TO_8][INC_PHIRAS] = 2;
  tab[LEVEL_7_TO_8][INC_THYSTAME] = 1;
}

int		cmp_cell_incantation(t_cell *cell, int level)
{
  t_player	*player;
  t_list	*players;
  int		nb_players;
  int		i;
  int		inc_tab[NB_LEVEL_INCANTATION][NB_SLOT_INCANTATION];

  init_incantation_tab1(inc_tab);
  init_incantation_tab2(inc_tab);
  players = cell->players;
  nb_players = 0;
  while (players)
    {
      player = players->data;
      if (player->level != level)
	return (-1);
      nb_players++;
      players = players->next;
    }
  if (inc_tab[level - 1][INC_NEEDED_PLAYER] != nb_players)
    return (-1);
  i = 0;
  while (++i < NB_SLOT_INCANTATION)
    if (cell->items[i] != inc_tab[level - 1][i])
      return (-1);
  return (0);
}

void		level_up_players(t_cell *cell)
{
  t_player	*player;
  t_list	*players;
  char		buf[32];
  int		i;

  players = cell->players;
  i = 0;
  while (++i < NB_SLOT_INCANTATION)
    cell->items[i] = 0;
  while (players)
    {
      player = players->data;
      player->level++;
      player->vision++;
      snprintf(buf, sizeof(buf), "niveau actuel : %d\n", player->level);
      send_message(player, buf);
      graphic_auto_plv(player);
      players = players->next;
    }
}

int		zappy_incantation(t_player *player)
{
  if (!cmp_cell_incantation(&(g_zappy->map[player->y][player->x]),
			    player->level))
    {
      level_up_players(&(g_zappy->map[player->y][player->x]));
      graphic_pie(player->x, player->y, 1);
    }
  else
    {
      send_message(player, "ko\n");
      graphic_pie(player->x, player->y, 0);
    }
  return (0);
}
