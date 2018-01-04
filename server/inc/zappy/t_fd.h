/*
** t_fd.h for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 22:20:13 2015 Valentin Potier
** Last update Mon Jun 29 11:06:04 2015 Alexis Bevillard
*/

#ifndef	T_FD_H_
# define T_FD_H_

# include		<sys/types.h>
# include		<sys/socket.h>
# include		<sys/select.h>
# include		"zappy/items.h"

# define MAX_CLIENT     100000

typedef struct		s_fd
{
  int			fdl[MAX_CLIENT + 1];
  fd_set		fds;
}			t_fd;

#endif /* !T_FD_H_ */
