/*
** comm.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 19:33:29 2015 Valentin Potier
** Last update Sun Jul  5 21:52:53 2015 Alexis Bevillard
*/

#include		<unistd.h>
#include		<stdio.h>
#include		<string.h>
#include		"zappy.h"
#include		"zappy/player.h"
#include		"utils/color.h"

int			send_message(t_player *player, char *msg)
{
  struct timeval	tv;

  gettimeofday(&tv, NULL);
  if (write(player->sockfd, msg, strlen(msg)) < 0)
    remove_fd(player->sockfd);
  else
    {
      PRINTF_BLUB("%d:%d\tSend to player %d: \"%.*s\"\n",
		  (int)tv.tv_sec,
		  (int)tv.tv_usec,
		  player->id,
		  (int)strlen(msg) - 1, msg);
      new_log_message("> %d:%d\tSend to player %d: \"%.*s\"\n",
		      (int)tv.tv_sec,
		      (int)tv.tv_usec,
		      player->id,
		      (int)strlen(msg) - 1, msg);
    }
  return (0);
}
