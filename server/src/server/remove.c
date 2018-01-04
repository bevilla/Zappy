/*
** remove.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 19:41:56 2015 Valentin Potier
** Last update Sun Jul  5 15:36:53 2015 Alexis Bevillard
*/

#include	<unistd.h>
#include	<string.h>
#include	<stdio.h>
#include	"zappy.h"
#include	"zappy/player.h"
#include	"utils/color.h"

void		remove_fd_player2(t_player *player, t_list *tmp)
{
  if (player->items[NOURRITURE] > 0 && player->type == PLAYER)
    {
      player->type = GHOST;
      PRINTF_YEL("Player %d is now in GHOST mode\n", player->id);
      new_log_message("* Player %d is now in GHOST mode\n", player->id);
    }
  else
    {
      PRINTF_YEL("Player %d disconnected\n", player->id);
      new_log_message("* Player %d disconnected\n", player->id);
      del_elem_list(&(g_zappy->players), tmp->data);
    }

}

static void	remove_fd_player(int fd)
{
  t_list	*tmp;
  t_action	*action;
  t_player	*player;

  tmp = g_zappy->players;
  while (tmp != NULL && ((t_player *)tmp->data)->sockfd != fd)
    tmp = tmp->next;
  if (tmp == NULL)
    PRINTF_RED("WARNING: fd(%d) not in players", fd);
  if (tmp == NULL)
    return ;
  player = tmp->data;
  while ((action = c_buf_get(&(player->actions))))
    free_action(action);
  del_elem_list_no_free(&(g_zappy->map[player->y][player->x].players), player);
  remove_fd_player2(player, tmp);
}

static void	remove_read(int fd)
{
  int		highest;
  int		i;

  i = g_zappy->read.fdl[0];
  while (i > 1 && g_zappy->read.fdl[i] != fd)
    i--;
  if (i == 1)
    {
      PRINTF_RED("WARNING: fd(%d) not in read fdl\n", fd);
      return ;
    }
  (*(g_zappy->read.fdl))--;
  i--;
  while (++i <= *(g_zappy->read.fdl))
    g_zappy->read.fdl[i] = g_zappy->read.fdl[i + 1];
  if (fd != *(g_zappy->highest))
    return;
  i = g_zappy->read.fdl[0] + 1;
  highest = 0;
  while (--i > 0)
    if (g_zappy->read.fdl[i] > highest)
      highest = g_zappy->read.fdl[i];
  if (highest > *(g_zappy->highest))
    g_zappy->highest = &highest;
}

static void	remove_write(int fd)
{
  int		highest;
  int		i;

  i = g_zappy->write.fdl[0];
  while (i > 0 && g_zappy->write.fdl[i] != fd)
    i--;
  if (i == 0)
    {
      PRINTF_RED("WARNING: fd(%d) not in write fdl\n", fd);
      return ;
    }
  (*(g_zappy->write.fdl))--;
  i--;
  while (++i <= g_zappy->write.fdl[0])
    g_zappy->write.fdl[i] = g_zappy->write.fdl[i + 1];
  if (fd != *(g_zappy->highest))
    return;
  i = g_zappy->write.fdl[0] + 1;
  highest = 0;
  while (--i > 0)
    if (g_zappy->write.fdl[i] > highest)
      highest = g_zappy->write.fdl[i];
  if (highest > *(g_zappy->highest))
    g_zappy->highest = &highest;
}

void		remove_fd(int fd)
{
  t_player	*player;
  int		flag;

  if ((player = get_player_from_fd(fd)))
    {
      flag = player->items[NOURRITURE] <= 0 || player->type != PLAYER;
      remove_fd_player(fd);
      if (flag)
	{
	  close(fd);
	  remove_write(fd);
	  remove_read(fd);
	}
    }
}
