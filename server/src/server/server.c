/*
** server.c for lele in /home/potier_v/rendu/PSU_2014_zappy/zizi
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Tue Jun 16 10:57:30 2015 Valentin Potier
** Last update Sun Jul  5 10:53:14 2015 Alexis Bevillard
*/

#define			_BSD_SOURCE
#include		<netdb.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<bits/socket.h>
#include		<fcntl.h>
#include		<unistd.h>
#include		<stdlib.h>
#include		"zappy.h"
#include		"zappy/update.h"
#include		"zappy/error.h"

static void		set_read()
{
  int			i;

  i = *(g_zappy->read.fdl);
  FD_ZERO(&(g_zappy->read.fds));
  while (i > 0)
    {
      FD_SET(g_zappy->read.fdl[i], &(g_zappy->read.fds));
      i--;
    }
}

static void		set_write()
{
  int			i;

  i = *(g_zappy->write.fdl);
  FD_ZERO(&(g_zappy->write.fds));
  while (i > 0)
    {
      FD_SET(g_zappy->write.fdl[i], &(g_zappy->write.fds));
      i--;
    }
}

static int		get_actions()
{
  int			err;
  int			i;

  if ((i = check_new_player()))
    return (i);
  i = *(g_zappy->read.fdl);
  while (i > 1)
     {
       if (FD_ISSET(g_zappy->read.fdl[i], &(g_zappy->read.fds))
	   && (err = add_new_message(g_zappy->read.fdl[i])))
	 return (err);
       i--;
     }
  return (0);
}

static int		recv_client()
{
  struct timeval	tv;
  int			ret;

  tv.tv_sec = 0;
  tv.tv_usec = 0;
  set_read();
  set_write();
  if ((ret = select(*(g_zappy->highest) + 1,
		    &(g_zappy->read.fds),
		    &(g_zappy->write.fds), NULL, &tv)) < 0)
    return (server_error(SELECT_ERR));
  else if (ret == 0)
    return (0);
  return (get_actions());
}

int			manage_client()
{
  int			highest;
  int			err;

  g_zappy->read.fdl[0] = 1;
  g_zappy->read.fdl[1] = g_zappy->fd;
  g_zappy->write.fdl[0] = 0;
  highest = g_zappy->fd;
  g_zappy->highest = &highest;
  g_zappy->is_paused = 0;
  while (1)
    {
      if ((err = recv_client()))
	return (err);
      if ((err = update()))
	return (err);
      if ((err = is_game_ended()) >= 0)
	return (err);
      if (!g_zappy->is_paused)
	update_nourriture();
      if (!g_zappy->speed_mode)
	usleep(10000);
    }
  return (0);
}
