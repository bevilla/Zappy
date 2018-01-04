/*
** msg.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Mon Jun 22 10:37:04 2015 Alexis Bevillard
** Last update Sat Jun 27 19:23:52 2015 Alexis Bevillard
*/

#include	<unistd.h>
#include	"utils/msg.h"

int		is_ending_char(char *buf, int buf_offset, int len)
{
  if (buf[buf_offset] == '\n')
    return (0);
  else if (buf[buf_offset] == '\r' &&
	   (buf_offset + 1) < len &&
	   buf[buf_offset + 1] == '\n')
    return (0);
  return (-1);
}

int		get_msg(int fd, t_msg *msg)
{
  if (msg->len == msg->buf_offset)
    {
      if ((msg->len = read(fd, msg->buf, SIZE_MSG)) <= 0)
	return (-1);
      msg->buf_offset = 0;
    }
  while (is_ending_char(msg->buf, msg->buf_offset, msg->len) &&
	 msg->buf_offset < msg->len &&
	 msg->msg_offset < SIZE_MSG)
    msg->msg[msg->msg_offset++] = msg->buf[msg->buf_offset++];
  msg->msg[msg->msg_offset] = '\0';
  if (msg->buf[msg->buf_offset] == '\n' || msg->buf[msg->buf_offset] == '\r')
    {
      msg->buf_offset += (msg->buf[msg->buf_offset] == '\n' ? 1 : 2);
      msg->msg_offset = 0;
      return (0);
    }
  if (msg->msg_offset == SIZE_MSG)
    {
      msg->msg_offset = 0;
      return (0);
    }
  return (1);
}

void		init_msg(t_msg *msg)
{
  msg->buf_offset = 0;
  msg->msg_offset = 0;
  msg->len = 0;
}
