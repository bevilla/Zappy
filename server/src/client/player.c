/*
** player.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Fri Jun 19 09:08:52 2015 Alexis Bevillard
** Last update Sun Jul  5 15:45:25 2015 Alexis Bevillard
*/

#include	<sys/time.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	"utils/color.h"
#include	"zappy.h"
#include	"zappy/player.h"
#include	"zappy/error.h"
#include	"graphic/server_graphic.h"

static void	init_player_field(int sockfd, t_player *player)
{
  int		item;

  player->id = ++(g_zappy->nb_client);
  player->sockfd = sockfd;
  player->items[NOURRITURE] = 10;
  item = LINEMATE;
  while (item < NB_ITEM)
    player->items[item++] = 0;
  gettimeofday(&(player->last_meal), NULL);
  player->x = rand() % g_zappy->width;
  player->y = rand() % g_zappy->height;
  player->team = NULL;
  player->level = 1;
  player->vision = 1;
  player->direction = rand() % 4 + NORTH;
  player->type = NONE;
  player->father = NULL;
  init_msg(&(player->msg));
  c_buf_create(&(player->actions));
}

int		init_new_egg(t_player *player)
{
  t_player	*egg;
  int		err;

  if ((egg = malloc(sizeof(*egg))) == NULL)
    return (server_error(MALLOC_ERR));
  init_player_field(-1, egg);
  egg->x = player->x;
  egg->y = player->y;
  egg->team = player->team;
  egg->type = EGG;
  egg->father = player;
  PRINTF_YEL("Added a new egg %d at (%d, %d)\n", egg->id, egg->x, egg->y);
  new_log_message("Added a new egg %d at (%d, %d)\n", egg->id, egg->x, egg->y);
  if ((add_back_elem_list(&(g_zappy->map[egg->y][egg->x].players), egg)) < 0)
    return (server_error(MALLOC_ERR));
  if ((err = add_back_elem_list(&(g_zappy->players), egg)))
    return (err);
  return (0);
}

int		init_new_player(int sockfd)
{
  t_player	*player;
  int		err;

  if ((player = malloc(sizeof(*player))) == NULL)
    return (server_error(MALLOC_ERR));
  init_player_field(sockfd, player);
  PRINTF_YEL("Added a new player %d at (%d, %d)\n",
	     player->id, player->x, player->y);
  new_log_message("* Added a new player %d at (%d, %d)\n",
		  player->id, player->x, player->y);
  if ((add_back_elem_list(&(g_zappy->map[player->y][player->x].players),
			  player)) < 0)
    return (server_error(MALLOC_ERR));
  if ((err = add_back_elem_list(&(g_zappy->players), player)))
    return (err);
  send_message(player, "BIENVENUE\n");
  return (0);
}

void		dump_player(t_player *dest, t_player *src)
{
  int		i;

  i = -1;
  while (++i < NB_ITEM)
    dest->items[i] = src->items[i];
  dest->last_meal = src->last_meal;
  dest->x = src->x;
  dest->y = src->y;
  dest->team = src->team;
  dest->level = src->level;
  dest->vision = src->vision;
  dest->direction = src->direction;
  dest->type = PLAYER;
}
