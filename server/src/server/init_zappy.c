/*
** init_zappy.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Thu Jun 18 17:33:34 2015 Alexis Bevillard
** Last update Sun Jul  5 16:59:44 2015 Louis Bouteillon
*/

#include		<sys/types.h>
#include		<sys/socket.h>
#include		<netdb.h>
#include		<stdlib.h>
#include		<unistd.h>
#include		<stdio.h>
#include		<time.h>
#include		"zappy.h"
#include		"zappy/exec.h"
#include		"zappy/error.h"
#include		"utils/color.h"

static void		init_cell(t_cell *cell)
{
  int		i;

  i = 0;
  while (i < NB_ITEM)
    {
      cell->items[i] = rand() % ITEM_GEN_RATE;
      cell->items[i++] += rand() % (ITEM_GEN_RATE << 2) ? 0 : 1;
    }
  cell->players = NULL;
}

void			init_exec()
{
  time_t		now;
  struct tm		*tm;
  char			buf[32];

  init_player_lens();
  init_player_delays();
  init_player_ptabstr();
  init_player_pptr();
  init_graphic_gtabstr();
  init_graphic_gptr();
  gettimeofday(&(g_zappy->nourriture_pop), NULL);
  now = time(NULL) + 7200;
  tm = gmtime(&now);
  snprintf(buf, sizeof(buf), ".%04d%02d%02d_%02d%02d%02d.zappylog",
	   tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
	   tm->tm_hour, tm->tm_min, tm->tm_sec);
  if ((g_zappy->log = fopen(buf, "w+")) == NULL)
    ECHO_RED("Warning: cannot open the log file\n");
}

int			init_zappy()
{
  int			i;
  int			j;

  g_zappy->players = NULL;
  if (!(g_zappy->map = malloc(sizeof(*(g_zappy->map)) * g_zappy->height)))
    return (server_error(MALLOC_ERR));
  i = -1;
  while (++i < g_zappy->height)
    {
      if (!(g_zappy->map[i] =
	    malloc(sizeof(**(g_zappy->map)) * g_zappy->width)))
	return (server_error(MALLOC_ERR));
      j = 0;
      while (j < g_zappy->width)
	init_cell(&(g_zappy->map[i][j++]));
    }
  g_zappy->nb_client = 0;
  init_exec();
  return (0);
}

void			init_random()
{
  time_t		t;

  t = time(NULL);
  srand(getpid() * (t == ((time_t)-1) ? 1 : t));
}

int			init_server()
{
  struct protoent	*proto;
  struct sockaddr_in	sin;
  int			optval;

  if (!(proto = getprotobyname("TCP")))
    return (server_error(PROTO_ERR));
  if ((g_zappy->fd = socket(AF_INET, SOCK_STREAM, proto->p_proto)) < 0)
    return (server_error(SOCKET_ERR));
  optval = 1;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(g_zappy->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (setsockopt(g_zappy->fd, SOL_SOCKET, SO_REUSEADDR, &optval,
		 sizeof(optval)) < 0)
    return (server_error(SOCKOPT_ERR));
  if (bind(g_zappy->fd, (struct sockaddr*)&sin, sizeof(sin)))
    return (server_error(BIND_ERR));
  if (listen(g_zappy->fd, MAX_CLIENT))
    return (server_error(LISTEN_ERR));
  return (0);
}
