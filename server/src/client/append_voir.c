/*
** append_voir.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 18:31:56 2015 Valentin Potier
** Last update Thu Jun 25 11:09:38 2015 Valentin Potier
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	"zappy/error.h"
#include	"zappy/items.h"
#include	"utils/list.h"

int		append_to_str(char **dest, char *src)
{
  char		*str;

  if ((str = malloc(sizeof(char) * ((*dest ? strlen(*dest) : 0) +
				    strlen(src) + 1))) == NULL)
    {
      fprintf(stderr, "Error: malloc failed\n");
      return (-1);
    }
  str[0] = '\0';
  if (*dest)
    strcat(str, *dest);
  strcat(str, src);
  if (*dest)
    free(*dest);
  *dest = str;
  return (0);
}

int		append_items_to_str(char **str, int items[NB_ITEM])
{
  char		*items_str[NB_ITEM];
  int		i;
  int		j;

  items_str[NOURRITURE] = " nourriture";
  items_str[LINEMATE] = " linemate";
  items_str[DERAUMERE] = " deraumere";
  items_str[SIBUR] = " sibur";
  items_str[MENDIANE] = " mendiane";
  items_str[PHIRAS] = " phiras";
  items_str[THYSTAME] = " thystame";
  i = 0;
  while (i < NB_ITEM)
    {
      j = 0;
      while (j < items[i])
	{
	  if (append_to_str(str, items_str[i]))
	    return (server_error(MALLOC_ERR));
	  j++;
	}
      i++;
    }
  return (0);
}

int		append_players_to_str(char **str, t_list *players)
{
  while (players)
    {
      if (append_to_str(str, " joueur"))
	return (server_error(MALLOC_ERR));
      players = players->next;
    }
  return (0);
}
