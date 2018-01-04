/*
** end_zappy.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 20:07:16 2015 Valentin Potier
** Last update Sun Jul  5 15:16:03 2015 Alexis Bevillard
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"zappy.h"
#include	"zappy/player.h"

void		close_fds(t_list *player)
{
  while (player != NULL)
    {
      close(((t_player *)(player->data))->sockfd);
      player = player->next;
    }
}

void		free_players(t_list *players)
{
  t_player	*player;
  t_action	*action;

  while (players)
    {
      player = players->data;
      while ((action = c_buf_get(&(player->actions))))
	free_action(action);
      players = players->next;
    }
  close_fds(g_zappy->players);
  free_list(g_zappy->players);
}

void		free_zappy()
{
  int		i;
  int		j;

  i = 0;
  if (g_zappy->team_name)
    free(g_zappy->team_name);
  while (g_zappy->map && i < g_zappy->height && g_zappy->map[i])
    {
      j = 0;
      while (j < g_zappy->width)
	free_list_no_free_data(g_zappy->map[i][j++].players);
      free(g_zappy->map[i++]);
    }
  if (g_zappy->map)
    free(g_zappy->map);
  free_players(g_zappy->players);
  close(g_zappy->fd);
  if (g_zappy->log)
    fclose(g_zappy->log);
}
