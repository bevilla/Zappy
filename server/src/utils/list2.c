/*
** list2.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Wed Jun 17 18:20:59 2015 Alexis Bevillard
** Last update Wed Jun 24 18:05:51 2015 Valentin Potier
*/

#include	<stdlib.h>
#include	"utils/list.h"

void		free_list(t_list *list)
{
  t_list	*tmp;

  while (list)
    {
      tmp = list;
      free(list->data);
      list = list->next;
      free(tmp);
    }
}

void		free_list_no_free_data(t_list *list)
{
  t_list	*tmp;

  while (list)
    {
      tmp = list;
      list = list->next;
      free(tmp);
    }
}

int		del_first_elem_list_no_free(t_list **list)
{
  t_list	*last;
  t_list	*tmp;

  if (*list)
    {
      last = (*list)->last;
      tmp = *list;
      *list = tmp->next;
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

int		del_last_elem_list_no_free(t_list **list)
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
      free(tmp);
      return (0);
    }
  return (-1);
}

int		del_elem_list_no_free(t_list **list, void *data)
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
	    del_first_elem_list_no_free(list);
	  else if (cur == last)
	    del_last_elem_list_no_free(list);
	  else
	    {
	      cur->prev->next = cur->next;
	      cur->next->prev = cur->prev;
	      free(cur);
	    }
	  return (0);
	}
      cur = cur->next;
    }
  return (-1);
}
