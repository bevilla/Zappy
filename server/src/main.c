/*
** main.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Tue May 19 09:55:19 2015 Alexis Bevillard
** Last update Sun Jul  5 21:52:25 2015 Alexis Bevillard
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<signal.h>
#include	"zappy/zappy_parse.h"
#include	"utils/color.h"

t_zappy		*g_zappy;

void		display_usage(char *progname)
{
  printf("Usage: %s [OPTIONS]\n", progname);
  printf("  -p port (Default value: %d)\n", DEFAULT_PORT);
  printf("  -x width of the world (Default value: %d)\n", DEFAULT_WIDTH);
  printf("  -y height of the world (Default value: %d)\n", DEFAULT_HEIGHT);
  printf("  -n name_of_team_1 name_of_team_2 ... (No default value)\n");
  printf("  -c number of clients allowed at the game beginning \
(Default value: %d)\n", DEFAULT_LIMIT);
  printf("  -t time delay for executing actions (Default value: %d)\n",
	 DEFAULT_DELAY);
  printf("  --speed-mode remove the sleep in the server loop\n");
}

void		print_config()
{
  int		i;

  i = -1;
  ECHO_GRE("Configuration :\n");
  PRINTF_GREB("\tPort:\t\t%d\n", g_zappy->port);
  PRINTF_GREB("\tWidth:\t\t%d\n", g_zappy->width);
  PRINTF_GREB("\tHeight:\t\t%d\n", g_zappy->height);
  PRINTF_GREB("\tT:\t\t%d\n", g_zappy->delay);
  PRINTF_GREB("\tMax players:\t%d\n", g_zappy->team_limit);
  PRINTF_GREB("\t%d teams:\t", g_zappy->nb_team);
  while (++i < g_zappy->nb_team)
    PRINTF_GREB("%s%s",
		g_zappy->team_name[i],
		i == (g_zappy->nb_team - 1) ? "\n" : ", ");
  PRINTF_GREB("\tSpeed mode:\t%s\n", g_zappy->speed_mode ? "true" : "false");
  ECHO_GRE("Generating world...");
}

int		server()
{
  int		err;

  init_random();
  print_config();
  if ((err = init_zappy()))
    return (err);
  ECHO_GRE(" OK\n");
  if ((err = init_server()))
    return (err);
  if ((err = manage_client()))
    return (err);
  return (0);
}

int		main(int ac, char **av)
{
  t_zappy_parse	zappy_parse;
  int		err;

  setvbuf(stdout, NULL, _IONBF, 0);
  if ((err = parse_args(ac, av, &zappy_parse)))
    {
      if (zappy_parse.zappy.team_name)
	free(zappy_parse.zappy.team_name);
      display_usage(av[0]);
      return (err);
    }
  g_zappy = &(zappy_parse.zappy);
  signal(SIGINT, &sighandler);
  signal(SIGPIPE, SIG_IGN);
  err = server();
  free_zappy();
  return (err);
}
