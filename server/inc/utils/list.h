/*
** list.h for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
** 
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
** 
** Started on  Tue Jun 16 10:18:42 2015 Alexis Bevillard
** Last update Tue Jun 23 10:29:39 2015 Alexis Bevillard
*/

#ifndef LIST_H_
# define LIST_H_

typedef struct	s_list
{
  void		*data;
  struct s_list	*last;
  struct s_list	*prev;
  struct s_list	*next;
}		t_list;

int		add_front_elem_list(t_list **list, void *data);
int		add_back_elem_list(t_list **list, void *data);
int		del_first_elem_list(t_list **list);
int		del_last_elem_list(t_list **list);
int	        del_elem_list(t_list **list, void *data);
int		del_first_elem_list_no_free(t_list **list);
int		del_last_elem_list_no_free(t_list **list);
int		del_elem_list_no_free(t_list **list, void *data);
void		free_list(t_list *list);
void		free_list_no_free_data(t_list *list);

#endif /* !LIST_H_ */
