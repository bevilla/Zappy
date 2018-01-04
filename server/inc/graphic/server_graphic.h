/*
** server_graphic.h for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 18:00:02 2015 Valentin Potier
** Last update Wed Jul  1 17:43:08 2015 Alexis Bevillard
*/

#ifndef	SERVER_GRAPHIC_H_
# define SERVER_GRAPHIC_H_

# include	"utils/list.h"
# include	"zappy/player.h"

enum		e_gptr
  {
    G_MSZ = 0,
    G_MCT,
    G_TNA,
    G_SGT,
    G_BCT,
    G_PPO,
    G_PLV,
    G_PIN,
    G_SST,
    G_SUM,
  };

int		graphic_send_players(t_player *graphic);

int		graphic_msz(t_player *player);
int		graphic_mct(t_player *player);
int		graphic_tna(t_player *player);
int		graphic_sgt(t_player *player);
int		graphic_bct(t_player *player, char *msg);
int		graphic_ppo(t_player *player, char *msg);
int		graphic_plv(t_player *player, char *msg);
int		graphic_pin(t_player *player, char *msg);
int		graphic_sst(t_player *player, char *msg);

int		graphic_pfk(t_player *player);
int		graphic_enw(t_player *egg);
int		graphic_eht(t_player *egg);
int		graphic_ebo(t_player *egg);
int		graphic_pdr(t_player *player, int item);
int		graphic_pgt(t_player *player, int item);
int		graphic_pnw(t_player *player);
int		graphic_seg(char *team);
int		graphic_pdi(t_player *player);
int		graphic_pex(t_player *player);
int		graphic_pbc(t_player *player, char *msg);
int		graphic_pic(int x, int y, int lvl, t_list *players);
int		graphic_pie(int x, int y, int res);
int		graphic_auto_ppo(t_player *player);
int		graphic_auto_plv(t_player *player);
int		graphic_auto_pin(t_player *player);

int		buf_pin(t_player *player, char **buf);
int		get_bct_args(char *msg, int *x, int *y);
void		send_to_graphics(char *msg);
int		get_int_from_msg(char *msg, int *nb);
t_player	*get_player_from_id(int id);
int		exec_graphic_action(t_player *player, t_action *action);

# define	GPTR_PREFIX(f)	&graphic_ ## f

#endif /* !SERVER_GRAPHIC_H_ */
