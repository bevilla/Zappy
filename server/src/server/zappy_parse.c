/*
** zappy_parse.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Wed May 20 11:21:35 2015 Alexis Bevillard
** Last update Sun Jul  5 10:48:51 2015 Alexis Bevillard
*/

#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>
#include	"zappy/zappy_parse.h"
#include	"zappy/error.h"

int		parse_n_option(int *i, char **av, t_zappy *zappy)
{
  int		n;

  zappy->nb_team = 0;
  (*i)++;
  while (av[zappy->nb_team + *i] && *av[zappy->nb_team + *i] != '-')
    zappy->nb_team++;
  if (zappy->nb_team == 0)
    {
      fprintf(stderr, "Error: empty team names\n");
      return (MISSING_OPTION);
    }
  if ((zappy->team_name = malloc(sizeof(char *) * zappy->nb_team)) == NULL)
    return (server_error(MALLOC_ERR));
  n = 0;
  while (n < zappy->nb_team)
    {
      if (!strcmp(av[*i], "GRAPHIC"))
	{
	  fprintf(stderr, "Error: you cannot use 'GRAPHIC' as a team name\n");
	  return (MISSING_OPTION);
	}
      zappy->team_name[n++] = av[(*i)++];
    }
  return (0);
}

static void	init_zappy_parse(t_zappy_parse *zappy_parse)
{
  zappy_parse->zappy.port = DEFAULT_PORT;
  zappy_parse->zappy.width = DEFAULT_WIDTH;
  zappy_parse->zappy.height = DEFAULT_HEIGHT;
  zappy_parse->zappy.nb_team = -1;
  zappy_parse->zappy.team_name = NULL;
  zappy_parse->zappy.team_limit = DEFAULT_LIMIT;
  zappy_parse->zappy.delay = DEFAULT_DELAY;
  zappy_parse->zappy.speed_mode = DEFAULT_MODE;
  zappy_parse->f[0] = &parse_p_option;
  zappy_parse->f[1] = &parse_x_option;
  zappy_parse->f[2] = &parse_y_option;
  zappy_parse->f[3] = &parse_n_option;
  zappy_parse->f[4] = &parse_c_option;
  zappy_parse->f[5] = &parse_t_option;
  zappy_parse->options[0] = "-p";
  zappy_parse->options[1] = "-x";
  zappy_parse->options[2] = "-y";
  zappy_parse->options[3] = "-n";
  zappy_parse->options[4] = "-c";
  zappy_parse->options[5] = "-t";
}

static int	parse_loop(int ac, char **av, t_zappy_parse *zappy_parse)
{
  int		flag;
  int		err;
  int		i;
  int		j;

  i = 1;
  while (i < ac)
    {
      flag = 1;
      j = -1;
      while (++j < NB_OPTIONS)
	if (!strcmp(zappy_parse->options[j], av[i]))
	  {
	    flag = 0;
	    if ((err = zappy_parse->f[j](&i, av, &(zappy_parse->zappy))))
	      return (err);
	    j = NB_OPTIONS;
	  }
      if (flag && set_speed_mode(&i, av, &(zappy_parse->zappy)))
	{
	  fprintf(stderr, "Error: invalid options '%s'\n", av[i]);
	  return (INVALID_ARG);
	}
    }
  return (0);
}

static int	check_args(t_zappy_parse *zappy_parse)
{
  int		tab[NB_OPTIONS];
  int		i;

  tab[0] = zappy_parse->zappy.port;
  tab[1] = zappy_parse->zappy.width;
  tab[2] = zappy_parse->zappy.height;
  tab[3] = zappy_parse->zappy.nb_team;
  tab[4] = zappy_parse->zappy.team_limit;
  tab[5] = zappy_parse->zappy.delay;
  i = 0;
  while (i < NB_OPTIONS)
    {
      if (tab[i] < 0)
	{
	  fprintf(stderr, "Error: missing '%s' option\n",
		  zappy_parse->options[i]);
	  return (MISSING_OPTION);
	}
      i++;
    }
  if (zappy_parse->zappy.nb_team == 1)
    fprintf(stderr, "Error: at least 2 teams are needed, only 1 given\n");
  return (zappy_parse->zappy.nb_team == 1 ? MISSING_OPTION : 0);
}

int		parse_args(int ac, char **av, t_zappy_parse *zappy_parse)
{
  int		err;

  init_zappy_parse(zappy_parse);
  if ((err = parse_loop(ac, av, zappy_parse)))
    return (err);
  if ((err = check_args(zappy_parse)))
    return (err);
  return (0);
}
