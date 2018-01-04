/*
** c_buf.h for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Mon Jun 22 11:39:16 2015 Alexis Bevillard
** Last update Sat Jun 27 10:20:43 2015 Alexis Bevillard
*/

#ifndef C_BUF_H_
# define C_BUF_H_

# define C_BUF_SIZE	10

# include		<sys/types.h>

typedef struct		s_c_buf
{
  void			*data[C_BUF_SIZE];
  size_t		get_pos;
  size_t		add_pos;
  size_t		size;
}			t_c_buf;

int			c_buf_create(t_c_buf *c_buf);
void			*c_buf_get(t_c_buf *c_buf);
int			c_buf_add(t_c_buf *c_buf, void *elem);
void			*c_buf_get_first(t_c_buf *c_buf);

#endif /* !C_BUF_H_ */
