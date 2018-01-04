/*
** send_to_graphics.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Sat Jun 27 12:20:17 2015 Valentin Potier
** Last update Sat Jun 27 12:21:20 2015 Valentin Potier
*/

#include	"zappy.h"

void		send_to_graphics(char *msg)
{
  t_list	*tmp;
  t_player	*tmplayer;

  tmp = g_zappy->players;
  while (tmp)
    {
      tmplayer = tmp->data;
      if (tmplayer->type == GRAPHIC)
	send_message(tmplayer, msg);
      tmp = tmp->next;
    }
}
