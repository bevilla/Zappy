/*
** new_message.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 20:10:34 2015 Valentin Potier
** Last update Sun Jul  5 21:52:45 2015 Alexis Bevillard
*/

#define			_GNU_SOURCE
#include		<stdarg.h>
#include		<unistd.h>
#include		<string.h>
#include		<stdio.h>
#include		"zappy.h"
#include		"zappy/player.h"
#include		"zappy/error.h"
#include		"utils/color.h"
#include		"utils/list.h"

void			new_log_message(char *str, ...)
{
  va_list		ap;

  if (g_zappy->log)
    {
      va_start(ap, str);
      vfprintf(g_zappy->log, str, ap);
      va_end(ap);
    }
}

t_player		*get_player_from_fd(int fd)
{
  t_player		*player;
  t_list		*tmp;

  tmp = g_zappy->players;
  while (tmp)
    {
      player = tmp->data;
      if (player->sockfd == fd)
	return (player);
      tmp = tmp->next;
    }
  return (NULL);
}

int			add_new_message(int fd)
{
  struct timeval	tv;
  t_player		*player;
  char			*data;
  int			res;
  t_action		*action;

  if ((player = get_player_from_fd(fd)) == NULL)
    return (PRINTF_RED("Warning: cannot retrieve player from fd %d\n", fd)
	    ? 0 : 0);
  if ((res = get_msg(fd, &(player->msg))) < 0)
    remove_fd(fd);
  else if (res == 0)
    {
      if ((data = strdup(player->msg.msg)) == NULL)
	return (server_error(MALLOC_ERR));
      gettimeofday(&tv, NULL);
      PRINTF_MAGB("%d:%d\tReceived from player %d: \"%s\"\n",
		  (int)tv.tv_sec, (int)tv.tv_usec, player->id, data);
      new_log_message("< %d:%d\tReceived from player %d: \"%s\"\n",
		      (int)tv.tv_sec, (int)tv.tv_usec, player->id, data);
      if (c_buf_add(&(player->actions), (action = add_action(data))))
	free_action(action);
    }
  return (0);
}
