/*
** server_error.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Thu Jun 25 10:38:54 2015 Valentin Potier
** Last update Thu Jun 25 11:14:24 2015 Valentin Potier
*/

#include	<stdio.h>
#include	"zappy/error.h"

int		server_error(int status)
{
  char		*tab[SOCKOPT_ERR];

  tab[INVALID_ARG] = "Error: Invalid argument\n";
  tab[INVALID_NUMBER] = "Error: Invalid number\n";
  tab[MALLOC_ERR] = "Error: Cannot allocate memory\n";
  tab[MISSING_OPTION] = "Error: Missing option\n";
  tab[PROTO_ERR] = "Error: Cannot get TCP protocol info\n";
  tab[SOCKET_ERR] = "Error: Cannot create a socket\n";
  tab[BIND_ERR] = "Error: Cannot bind the server socket\n";
  tab[LISTEN_ERR] = "Error: Cannot listen the server socket\n";
  tab[SELECT_ERR] = "Error: I/O error, select returned -1\n";
  tab[ACCEPT_ERR] = "Warning: cannot accept more connection\n";
  tab[READ_ERR] = "Error: I/O error, read returned -1\n";
  tab[SOCKOPT_ERR] = "Error: cannot set socket option\n";
  fputs(tab[status - 1], stderr);
  return (status);
}
