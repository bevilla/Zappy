/*
** graphic_exec.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server/src/graphic
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 17:38:09 2015 Valentin Potier
** Last update Sun Jun 28 17:19:26 2015 Alexis Bevillard
*/

#include	<string.h>
#include	"zappy.h"
#include	"graphic/server_graphic.h"

void		init_graphic_gtabstr()
{
  g_zappy->exec.gtabstr[G_MSZ] = "msz";
  g_zappy->exec.gtabstr[G_MCT] = "mct";
  g_zappy->exec.gtabstr[G_TNA] = "tna";
  g_zappy->exec.gtabstr[G_SGT] = "sgt";
  g_zappy->exec.gtabstr[G_BCT] = "bct";
  g_zappy->exec.gtabstr[G_PPO] = "ppo";
  g_zappy->exec.gtabstr[G_PLV] = "plv";
  g_zappy->exec.gtabstr[G_PIN] = "pin";
  g_zappy->exec.gtabstr[G_SST] = "sst";
}

void		init_graphic_gptr()
{
  g_zappy->exec.gptr[G_MSZ] = GPTR_PREFIX(msz);
  g_zappy->exec.gptr[G_MCT] = GPTR_PREFIX(mct);
  g_zappy->exec.gptr[G_TNA] = GPTR_PREFIX(tna);
  g_zappy->exec.gptr[G_SGT] = GPTR_PREFIX(sgt);
  g_zappy->exec.gptr[G_BCT] = GPTR_PREFIX(bct);
  g_zappy->exec.gptr[G_PPO] = GPTR_PREFIX(ppo);
  g_zappy->exec.gptr[G_PLV] = GPTR_PREFIX(plv);
  g_zappy->exec.gptr[G_PIN] = GPTR_PREFIX(pin);
  g_zappy->exec.gptr[G_SST] = GPTR_PREFIX(sst);
}

static int	graphicactiontok(t_action *action)
{
  int		i;

  i = -1;
  while (++i < G_SUM)
    if (!strncmp(action->msg, g_zappy->exec.gtabstr[i], 3))
      return (i);
  return (-1);
}

int		exec_graphic_action(t_player *player, t_action *action)
{
  int		tok;

  if ((tok = graphicactiontok(action)) < 0)
    return (send_message(player, "suc\n"));
  if (tok >= G_BCT)
    return (g_zappy->exec.gptr[tok](player, action->msg + 4));
  return (g_zappy->exec.gptr[tok](player));
}
