/*
** isnum.c for zappy in /home/bevill_a/rendu/PSU_2014_zappy/server
** 
** Made by Alexis Bevillard
** Login   <bevill_a@epitech.net>
** 
** Started on  Wed May 20 11:24:33 2015 Alexis Bevillard
** Last update Wed May 20 11:24:38 2015 Alexis Bevillard
*/

int		isnum(char *str)
{
  while (*str)
    {
      if (*str < '0' || *str > '9')
	return (0);
      str++;
    }
  return (1);
}
