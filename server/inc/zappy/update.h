/*
** update.h for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Fri Jun 19 17:03:45 2015 Alexis Bevillard
** Last update Thu Jul  2 18:52:22 2015 Alexis Bevillard
*/

#ifndef UPDATE_H_
# define UPDATE_H_

# include		<sys/time.h>
# include		"zappy/player.h"
# include		"utils/list.h"

enum			e_fptr
  {
    F_AVANCE = 0,
    F_DROITE,
    F_GAUCHE,
    F_VOIR,
    F_INVENTAIRE,
    F_PREND,
    F_POSE,
    F_EXPULSE,
    F_BROADCAST,
    F_INCANTATION,
    F_FORK,
    F_CONNECT,
    F_SUM
  };

# define		PPTR_PREFIX(f)	&zappy_ ## f

int			zappy_avance(t_player *player);
int			zappy_droite(t_player *player);
int			zappy_gauche(t_player *player);
int			zappy_voir(t_player *player);
int			zappy_inventaire(t_player *player);
int			zappy_prend(t_player *player, char *msg);
int			zappy_pose(t_player *player, char *msg);
int			zappy_expulse(t_player *player);
int			zappy_broadcast(t_player *player, char *msg);
int			zappy_incantation(t_player *player);
int			zappy_fork(t_player *player);
int			zappy_connect_nbr(t_player *player);
int			zappy_mort(t_player *player);
void			send_map_size(t_player *player);
int			exec_player_action(t_player *player, t_action *action);
int			check_new_player();
int			append_to_str(char **dest, char *src);
void			replace_actions(t_list *actions, t_player *player);
int			set_team_name(t_player **player, t_action *action);
int			is_game_ended();
void			update_nourriture();

#endif /* !UPDATE_H_ */
