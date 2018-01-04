/*
** color.h for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
** 
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
** 
** Started on  Fri Jun 19 09:58:32 2015 Alexis Bevillard
** Last update Sun Jul  5 21:51:34 2015 Alexis Bevillard
*/

#ifndef COLOR_H_
# define COLOR_H_

# define PRINTF_RED(s, ...) printf("\033[31m" s "\033[0m", __VA_ARGS__)
# define PRINTF_GRE(s, ...) printf("\033[32m" s "\033[0m", __VA_ARGS__)
# define PRINTF_YEL(s, ...) printf("\033[33m" s "\033[0m", __VA_ARGS__)
# define PRINTF_BLU(s, ...) printf("\033[34m" s "\033[0m", __VA_ARGS__)
# define PRINTF_MAG(s, ...) printf("\033[35m" s "\033[0m", __VA_ARGS__)
# define PRINTF_CYA(s, ...) printf("\033[36m" s "\033[0m", __VA_ARGS__)

# define PRINTF_REDB(s, ...) printf("\033[1m\033[31m" s "\033[0m", __VA_ARGS__)
# define PRINTF_GREB(s, ...) printf("\033[1m\033[32m" s "\033[0m", __VA_ARGS__)
# define PRINTF_YELB(s, ...) printf("\033[1m\033[33m" s "\033[0m", __VA_ARGS__)
# define PRINTF_BLUB(s, ...) printf("\033[1m\033[34m" s "\033[0m", __VA_ARGS__)
# define PRINTF_MAGB(s, ...) printf("\033[1m\033[35m" s "\033[0m", __VA_ARGS__)
# define PRINTF_CYAB(s, ...) printf("\033[1m\033[36m" s "\033[0m", __VA_ARGS__)

# define ECHO_RED(s) printf("\033[31m" s "\033[0m")
# define ECHO_GRE(s) printf("\033[32m" s "\033[0m")
# define ECHO_YEL(s) printf("\033[33m" s "\033[0m")
# define ECHO_BLU(s) printf("\033[34m" s "\033[0m")
# define ECHO_MAG(s) printf("\033[35m" s "\033[0m")
# define ECHO_CYA(s) printf("\033[36m" s "\033[0m")

# define ECHO_REDB(s) printf("\033[1m\033[31m" s "\033[0m")
# define ECHO_GREB(s) printf("\033[1m\033[32m" s "\033[0m")
# define ECHO_YELB(s) printf("\033[1m\033[33m" s "\033[0m")
# define ECHO_BLUB(s) printf("\033[1m\033[34m" s "\033[0m")
# define ECHO_MAGB(s) printf("\033[1m\033[35m" s "\033[0m")
# define ECHO_CYAB(s) printf("\033[1m\033[36m" s "\033[0m")

#endif /* !COLOR_H_ */
