/*
** zappy_parse.h for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
**
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
**
** Started on  Tue May 19 13:33:36 2015 Alexis Bevillard
** Last update Sun Jul  5 10:49:33 2015 Alexis Bevillard
*/

#ifndef ZAPPY_PARSE_H_
# define ZAPPY_PARSE_H_

# include		"zappy.h"

# define NB_OPTIONS	6

# define DEFAULT_PORT	4242
# define DEFAULT_WIDTH	20
# define DEFAULT_HEIGHT	20
# define DEFAULT_LIMIT	1
# define DEFAULT_DELAY	100
# define DEFAULT_MODE	0

typedef struct		s_zappy_parse
{
  int			(*f[NB_OPTIONS])(int *, char **, t_zappy *);
  char			*options[NB_OPTIONS];
  t_zappy		zappy;
}			t_zappy_parse;

int			parse_args(int, char **, t_zappy_parse *);
int			parse_p_option(int *, char **, t_zappy *);
int			parse_x_option(int *, char **, t_zappy *);
int			parse_y_option(int *, char **, t_zappy *);
int			parse_n_option(int *, char **, t_zappy *);
int			parse_c_option(int *, char **, t_zappy *);
int			parse_t_option(int *, char **, t_zappy *);
int		        set_speed_mode(int *, char **, t_zappy *);

#endif /* !ZAPPY_PARSE_H_ */
