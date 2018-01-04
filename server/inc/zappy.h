/*
** zappy.h for zappy in /home/bevill_a/rendu/PSU_2014_zappy
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Tue May 19 10:30:04 2015 Alexis Bevillard
** Last update Sun Jul  5 15:28:20 2015 Alexis Bevillard
*/

#ifndef ZAPPY_H_
# define ZAPPY_H_

# include		<sys/types.h>
# include		<stdarg.h>
# include		<stdio.h>
# include		"utils/list.h"
# include		"zappy/t_fd.h"
# include		"zappy/player.h"
# include		"zappy/cell.h"
# include		"zappy/exec.h"

# define ITEM_GEN_RATE	2
# define SIN_LEN	sizeof(struct sockaddr_in)
# define READ_SIZE	16384

typedef struct		s_zappy
{
  int			port;
  int			fd;
  int			width;
  int			height;
  int			nb_team;
  char			**team_name;
  int			team_limit;
  int			delay;
  t_list		*players;
  t_cell		**map;
  int			nb_client;
  int			*highest;
  t_fd			read;
  t_fd			write;
  t_exec		exec;
  struct timeval	nourriture_pop;
  int			is_paused;
  int			speed_mode;
  FILE			*log;
}			t_zappy;

extern t_zappy		*g_zappy;

int			add_new_message(int fd);
int			send_message(t_player *player, char *msg);
int			init_new_player(int sockfd);
int			get_client_type(t_player **player, t_action *action);
void			remove_fd(int fd);
int			update();
int			init_zappy();
void			init_random();
int			init_server();
int			manage_client();
void			sighandler(int sig);
void			free_zappy();
void			new_log_message(char *str, ...);

#endif /* !ZAPPY_H_ */
