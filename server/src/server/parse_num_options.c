/*
** parse_num_options.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Wed May 20 11:23:03 2015 Alexis Bevillard
** Last update Sun Jul  5 21:30:57 2015 Alexis Bevillard
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	"zappy/zappy_parse.h"
#include	"zappy/error.h"
#include	"utils/utils.h"

int		parse_p_option(int *i, char **av, t_zappy *zappy)
{
  if (av[++(*i)])
    {
      if (!isnum(av[*i]))
	{
	  fprintf(stderr, "Error: invalid number '%s'\n", av[*i]);
	  return (INVALID_NUMBER);
	}
      zappy->port = atoi(av[(*i)++]);
      return (0);
    }
  fprintf(stderr, "Error: missing port number\n");
  return (MISSING_OPTION);
}

int		parse_x_option(int *i, char **av, t_zappy *zappy)
{
  if (av[++(*i)])
    {
      if (!isnum(av[*i]))
	{
	  fprintf(stderr, "Error: invalid number '%s'\n", av[*i]);
	  return (INVALID_NUMBER);
	}
      zappy->width = atoi(av[(*i)++]);
      return (0);
    }
  fprintf(stderr, "Error: missing width\n");
  return (MISSING_OPTION);
}

int		parse_y_option(int *i, char **av, t_zappy *zappy)
{
  if (av[++(*i)])
    {
      if (!isnum(av[*i]))
	{
	  fprintf(stderr, "Error: invalid number '%s'\n", av[*i]);
	  return (INVALID_NUMBER);
	}
      zappy->height = atoi(av[(*i)++]);
      return (0);
    }
  fprintf(stderr, "Error: missing height\n");
  return (MISSING_OPTION);
}

int		parse_c_option(int *i, char **av, t_zappy *zappy)
{
  if (av[++(*i)])
    {
      if (!isnum(av[*i]))
	{
	  fprintf(stderr, "Error: invalid number '%s'\n", av[*i]);
	  return (INVALID_NUMBER);
	}
      zappy->team_limit = atoi(av[(*i)++]);
      return (0);
    }
  fprintf(stderr, "Error: missing team limit\n");
  return (MISSING_OPTION);
}

int		parse_t_option(int *i, char **av, t_zappy *zappy)
{
  if (av[++(*i)])
    {
      if (!isnum(av[*i]))
	{
	  fprintf(stderr, "Error: invalid number '%s'\n", av[*i]);
	  return (INVALID_NUMBER);
	}
      zappy->delay = atoi(av[*i]);
      if (zappy->delay <= 0)
	{
	  fprintf(stderr, "Error: invalid number '%s'\n", av[*i]);
	  return (INVALID_NUMBER);
	}
      (*i)++;
      return (0);
    }
  fprintf(stderr, "Error: missing time delay\n");
  return (MISSING_OPTION);
}
