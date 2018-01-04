/*
** voir.h for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 22:35:25 2015 Valentin Potier
** Last update Wed Jun 24 23:15:26 2015 Valentin Potier
*/

#ifndef	VOIR_H_
# define VOIR_H_

# include	"utils/list.h"
# include	"zappy/items.h"

int		append_to_str(char **dest, char *src);
int		append_items_to_str(char **str, int items[NB_ITEM]);
int		append_players_to_str(char **str, t_list *players);

#endif /* !VOIR_H_ */
