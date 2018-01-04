/*
** player.h for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Thu Jun 25 01:08:25 2015 Valentin Potier
** Last update Sun Jul  5 21:50:04 2015 Alexis Bevillard
*/

#ifndef	PLAYER_H_
# define PLAYER_H_

# include		<sys/time.h>
# include		"zappy/items.h"
# include		"zappy/direction.h"
# include		"zappy/client_type.h"
# include		"utils/c_buf.h"
# include		"utils/msg.h"

typedef struct		s_player
{
  int			id;
  int			sockfd;
  int			items[NB_ITEM];
  struct timeval	last_meal;
  int			x;
  int			y;
  char			*team;
  int			level;
  int			vision;
  enum e_direction	direction;
  t_c_buf		actions;
  t_msg			msg;
  enum e_client_type	type;
  struct s_player	*father;
}			t_player;

typedef struct		s_action
{
  char			*msg;
  struct timeval        tv;
  int			flag;
}			t_action;

t_action	*add_action(char *msg);
void		free_action(t_action *action);
int		exec_action(t_player **player, t_action *action);
t_player	*get_player_from_fd(int fd);
void		dump_player(t_player *dest, t_player *src);
int		init_new_egg(t_player *player);

#endif /* !PLAYER_H_ */
