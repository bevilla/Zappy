/*
** speed_mode.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server/src/server
** 
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
** 
** Started on  Sun Jul  5 10:49:42 2015 Alexis Bevillard
** Last update Sun Jul  5 10:51:07 2015 Alexis Bevillard
*/

#include	<string.h>
#include	"zappy.h"

int		set_speed_mode(int *i, char **av, t_zappy *zappy)
{
  if (!strcmp(av[*i], "--speed-mode"))
    {
      (*i)++;
      zappy->speed_mode = 1;
      return (0);
    }
  return (-1);
}
