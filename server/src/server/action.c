/*
** action.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 19:54:05 2015 Valentin Potier
** Last update Thu Jul  2 21:49:52 2015 Alexis Bevillard
*/

#include	<unistd.h>
#include	<sys/time.h>
#include	<stdlib.h>
#include	"utils/list.h"
#include	"utils/utils.h"
#include	"zappy.h"
#include	"zappy/player.h"
#include	"zappy/update.h"
#include	"graphic/server_graphic.h"

t_action	*add_action(char *msg)
{
  t_action	*action;

  if ((action = malloc(sizeof(*action))) == NULL)
    return (NULL);
  action->msg = epur_str(msg);
  gettimeofday(&(action->tv), NULL);
  action->flag = 1;
  return (action);
}

void		free_action(t_action *action)
{
  free(action->msg);
  free(action);
}

int		exec_action(t_player **player, t_action *action)
{
  if ((*player)->type == PLAYER)
    return (g_zappy->is_paused ? -1 : exec_player_action(*player, action));
  else if ((*player)->type == GRAPHIC)
    return (exec_graphic_action(*player, action));
  return (get_client_type(player, action));
}

void		replace_actions(t_list *actions, t_player *player)
{
  t_list	*tmp;

  while (actions)
    {
      tmp = actions;
      c_buf_add(&(player->actions), actions->data);
      actions = actions->next;
      free(tmp);
    }
}
