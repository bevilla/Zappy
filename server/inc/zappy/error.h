/*
** zappy_error.h for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 21:52:41 2015 Valentin Potier
** Last update Thu Jun 25 11:11:19 2015 Valentin Potier
*/

#ifndef	ZAPPY_ERROR_H_
# define ZAPPY_ERROR_H_

enum		e_server_error
  {
    INVALID_ARG = 1,
    INVALID_NUMBER,
    MALLOC_ERR,
    MISSING_OPTION,
    PROTO_ERR,
    SOCKET_ERR,
    BIND_ERR,
    LISTEN_ERR,
    SELECT_ERR,
    ACCEPT_ERR,
    READ_ERR,
    SOCKOPT_ERR,
  };

int		server_error(int status);

#endif /* !ZAPPY_ERROR_H_ */
