/*
** c_buf.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Mon Jun 22 11:39:39 2015 Alexis Bevillard
** Last update Sat Jun 27 10:20:35 2015 Alexis Bevillard
*/

#include	<stdlib.h>
#include	"utils/c_buf.h"

int		c_buf_create(t_c_buf *c_buf)
{
  size_t	i;

  i = 0;
  c_buf->get_pos = 0;
  c_buf->add_pos = 0;
  c_buf->size = C_BUF_SIZE;
  while (i < C_BUF_SIZE)
    c_buf->data[i++] = NULL;
  return (0);
}

void		*c_buf_get(t_c_buf *c_buf)
{
  void		*elem;

  elem = c_buf->data[c_buf->get_pos];
  c_buf->data[c_buf->get_pos] = NULL;
  c_buf->get_pos = (c_buf->get_pos + 1) % c_buf->size;
  return (elem);
}

int		c_buf_add(t_c_buf *c_buf, void *elem)
{
  if (!c_buf->data[c_buf->add_pos])
    {
      c_buf->data[c_buf->add_pos] = elem;
      c_buf->add_pos = (c_buf->add_pos + 1) % c_buf->size;
      return (0);
    }
  return (1);
}

void		*c_buf_get_first(t_c_buf *c_buf)
{
  return (c_buf->data[c_buf->get_pos]);
}
