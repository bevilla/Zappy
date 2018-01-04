/*
** cell.h for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 22:17:34 2015 Valentin Potier
** Last update Sun Jul  5 21:49:51 2015 Alexis Bevillard
*/

#ifndef	CELL_H_
# define CELL_H_

# include	"utils/list.h"
# include	"zappy/items.h"

typedef struct	s_cell
{
  int		items[NB_ITEM];
  t_list	*players;
}		t_cell;

#endif /* !CELL_H_ */
