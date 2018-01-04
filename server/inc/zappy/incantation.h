/*
** incantation.h for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
** 
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
** 
** Started on  Fri Jun 26 18:54:12 2015 Alexis Bevillard
** Last update Sat Jun 27 12:05:42 2015 Alexis Bevillard
*/

#ifndef INCANTATION_H_
# define INCANTATION_H_

enum		e_level_incantation
  {
    LEVEL_1_TO_2,
    LEVEL_2_TO_3,
    LEVEL_3_TO_4,
    LEVEL_4_TO_5,
    LEVEL_5_TO_6,
    LEVEL_6_TO_7,
    LEVEL_7_TO_8,
    NB_LEVEL_INCANTATION
  };

enum		e_slot_incantation
  {
    INC_NEEDED_PLAYER,
    INC_LINEMATE,
    INC_DERAUMERE,
    INC_SIBUR,
    INC_MENDIANE,
    INC_PHIRAS,
    INC_THYSTAME,
    NB_SLOT_INCANTATION
  };

void		init_incantation_tab1(int (*tab)[NB_LEVEL_INCANTATION]);
void		init_incantation_tab2(int (*tab)[NB_LEVEL_INCANTATION]);
int		cmp_cell_incantation(t_cell *cell, int level);
void		level_up_players(t_cell *cell);

#endif /* !INCANTATION_H_ */
