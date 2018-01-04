/*
** list.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Tue Jun 16 10:20:24 2015 Alexis Bevillard
** Last update Wed Jun 24 18:06:14 2015 Valentin Potier
*/

#include	<stdlib.h>
#include	"utils/list.h"

int		add_front_elem_list(t_list **list, void *data)
{
  t_list	*elem;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (-1);
  elem->data = data;
  elem->last = *list ? (*list)->last : elem;
  elem->prev = NULL;
  elem->next = *list ? *list : NULL;
  if (*list)
    (*list)->prev = elem;
  *list = elem;
  return (0);
}

int		add_back_elem_list(t_list **list, void *data)
{
  t_list	*elem;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (-1);
  elem->data = data;
  elem->last = elem;
  elem->prev = *list ? (*list)->last : NULL;
  elem->next = NULL;
  if (*list)
    (*list)->last->next = elem;
  else
    *list = elem;
  (*list)->last = elem;
  return (0);
}

int		del_first_elem_list(t_list **list)
{
  t_list	*last;
  t_list	*tmp;

  if (*list)
    {
      last = (*list)->last;
      tmp = *list;
      *list = tmp->next;
      free(tmp->data);
      free(tmp);
      if (*list)
	{
	  (*list)->prev = NULL;
	  (*list)->last = last;
	}
      return (0);
    }
  return (-1);
}

int		del_last_elem_list(t_list **list)
{
  t_list	*tmp;

  if (*list)
    {
      tmp = (*list)->last;
      if (tmp->prev)
	{
	  (*list)->last = (*list)->last->prev;
	  tmp->prev->next = NULL;
	}
      else
	*list = NULL;
      free(tmp->data);
      free(tmp);
      return (0);
    }
  return (-1);
}

int		del_elem_list(t_list **list, void *data)
{
  t_list	*last;
  t_list	*cur;

  cur = *list;
  last = cur ? cur->last : NULL;
  while (cur)
    {
      if (cur->data == data)
	{
	  if (cur == *list)
	    del_first_elem_list(list);
	  else if (cur == last)
	    del_last_elem_list(list);
	  else
	    {
	      cur->prev->next = cur->next;
	      cur->next->prev = cur->prev;
	      free(cur->data);
	      free(cur);
	    }
	  return (0);
	}
      cur = cur->next;
    }
  return (-1);
}
