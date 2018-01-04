/*
** update.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Fri Jun 19 17:09:47 2015 Alexis Bevillard
** Last update Sun Jul  5 21:52:22 2015 Alexis Bevillard
*/

#include		<strings.h>
#include		<string.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		"zappy.h"
#include		"zappy/update.h"
#include		"zappy/player.h"
#include		"zappy/error.h"
#include		"utils/color.h"
#include		"graphic/server_graphic.h"

int			get_client_type(t_player **player, t_action *action)
{
  if (!strcmp(action->msg, "GRAPHIC"))
    {
      (*player)->type = GRAPHIC;
      graphic_msz(*player);
      graphic_sgt(*player);
      graphic_mct(*player);
      graphic_tna(*player);
      if (graphic_send_players(*player))
	return (MALLOC_ERR);
    }
  else if (!set_team_name(player, action))
    {
      (*player)->type = PLAYER;
      zappy_connect_nbr(*player);
      send_map_size(*player);
    }
  else
    {
      send_message(*player, "ko\n");
      remove_fd((*player)->sockfd);
    }
  return (0);
}

static void		remove_life(t_player *p)
{
  double		diff;
  struct timeval	d;

  gettimeofday(&d, NULL);
  diff = (double)(d.tv_sec - p->last_meal.tv_sec) +
    (d.tv_usec - p->last_meal.tv_usec) / 1000000.0;
  if (diff > 126 / (float)g_zappy->delay && p->type != EGG)
    {
      p->items[NOURRITURE]--;
      gettimeofday(&(p->last_meal), NULL);
    }
  else if (diff > 600 / (float)g_zappy->delay && p->type == EGG)
    {
      p->type = graphic_eht(p) ? GHOST : GHOST;
      gettimeofday(&(p->last_meal), NULL);
      PRINTF_YEL("Egg %d hatched at (%d, %d)\n", p->id, p->x, p->y);
      new_log_message("Egg %d hatched at (%d, %d)\n", p->id, p->x, p->y);
    }
  if (p->items[NOURRITURE] <= 0)
    {
      if (p->type == PLAYER)
	send_message(p, "mort\n");
      graphic_pdi(p);
      remove_fd(p->sockfd);
    }
}

void			fill_end_game_tab(int *tab)
{
  int			i;
  t_list		*players;
  t_player		*player;

  i = 0;
  while (i < g_zappy->nb_team)
    {
      players = g_zappy->players;
      while (players)
	{
	  player = players->data;
	  if (g_zappy->team_name[i] == player->team && player->level == 8)
	    tab[i]++;
	  players = players->next;
	}
      i++;
    }
}

int			is_game_ended()
{
  int			*tab;
  int			i;

  if ((tab = malloc(sizeof(*tab) * g_zappy->nb_team)) == NULL)
    {
      fprintf(stderr, "Error: malloc failed\n");
      return (MALLOC_ERR);
    }
  bzero(tab, sizeof(*tab) * g_zappy->nb_team);
  fill_end_game_tab(tab);
  i = 0;
  while (i < g_zappy->nb_team)
    {
      if (tab[i] >= 6)
	{
	  PRINTF_GREB("L'équipe '%s' remporte la victoire !\n",
		      g_zappy->team_name[i]);
	  free(tab);
	  return (graphic_seg(g_zappy->team_name[i]));
	}
      i++;
    }
  free(tab);
  return (-1);
}

int			update()
{
  t_list		*players;
  t_player		*player;
  t_action		*action;

  players = g_zappy->players;
  while (players)
    {
      player = players->data;
      if ((player->type == PLAYER || player->type == GHOST ||
	   player->type == EGG) && !g_zappy->is_paused)
	remove_life(player);
      if ((action = c_buf_get_first(&(player->actions))))
	{
	  if (exec_action(&player, action) >= 0)
	    {
	      c_buf_get(&(player->actions));
	      if ((action = c_buf_get_first(&(player->actions))))
		gettimeofday(&(action->tv), NULL);
	    }
	  else
	    action->flag = 0;
	}
      players = players->next;
    }
  return (0);
}
