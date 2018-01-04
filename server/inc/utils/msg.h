/*
** msg.h for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
** 
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
** 
** Started on  Mon Jun 22 10:32:35 2015 Alexis Bevillard
** Last update Mon Jun 22 10:47:43 2015 Alexis Bevillard
*/

#ifndef MSG_H_
# define MSG_H_

# define SIZE_MSG	256

typedef struct		s_msg
{
  char			buf[SIZE_MSG];
  char			msg[SIZE_MSG + 1];
  int			buf_offset;
  int			msg_offset;
  int			len;
}			t_msg;

int			get_msg(int fd, t_msg *test);
void			init_msg(t_msg *msg);

#endif /* !MSG_H_ */
