/*
** epur_test.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Mon Jun 22 18:15:24 2015 Valentin Potier
** Last update Tue Jun 23 16:39:10 2015 Valentin Potier
*/

#include	<string.h>

char		*epur(char *str)
{
  int		back;
  int		i;

  i = 0;
  while (str[i])
    {
      while (str[i] && str[i] != ' ' && str[i] != '\t')
	i++;
      if (str[i] == 0)
	return (str);
      str[i] = ' ';
      i++;
      back = i;
      while (str[i] && (str[i] == ' ' || str[i] == '\t'))
	i++;
      if (str[i] == 0)
	{
	  str[back - 1] = 0;
	  return (str);
	}
      memmove(str + back, str + i, strlen(str + i) + 1);
      i = back;
    }
  return (str);
}

char		*epur_str(char *str)
{
  int		i;

  if (str == NULL)
    return (NULL);
  i = 0;
  while (str[i] && (str[i] == ' ' || str[i] == '\t'))
    i++;
  if (!str[i])
    {
      *str = 0;
      return (str);
    }
  memmove(str, str + i, strlen(str) - i + 1);
  return (epur(str));
}
