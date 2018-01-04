/*
** exec.h for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Thu Jun 25 10:08:22 2015 Valentin Potier
** Last update Fri Jun 26 18:51:38 2015 Valentin Potier
*/

#ifndef	EXEC_H_
# define EXEC_H_

# include	"zappy/update.h"
# include	"graphic/server_graphic.h"

typedef struct	s_exec
{
  int		lens[F_SUM];
  double	delays[F_SUM];
  char		*ptabstr[F_SUM];
  char		*gtabstr[G_SUM];
  int		(*pptr[F_SUM])();
  int		(*gptr[G_SUM])();
}		t_exec;

void		init_player_lens();
void		init_player_delays();
void		init_player_ptabstr();
void		init_player_pptr();
void		init_graphic_gtabstr();
void		init_graphic_gptr();

#endif /* !EXEC_H_ */
