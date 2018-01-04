/*
** init_exec.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Thu Jun 25 10:14:43 2015 Valentin Potier
** Last update Sun Jun 28 17:19:25 2015 Alexis Bevillard
*/

#include	"graphic/server_graphic.h"
#include	"zappy/update.h"
#include	"zappy.h"

void		init_player_lens()
{
  g_zappy->exec.lens[F_AVANCE] = 6;
  g_zappy->exec.lens[F_DROITE] = 6;
  g_zappy->exec.lens[F_GAUCHE] = 6;
  g_zappy->exec.lens[F_VOIR] = 4;
  g_zappy->exec.lens[F_INVENTAIRE] = 10;
  g_zappy->exec.lens[F_PREND] = 5;
  g_zappy->exec.lens[F_POSE] = 4;
  g_zappy->exec.lens[F_EXPULSE] = 7;
  g_zappy->exec.lens[F_BROADCAST] = 9;
  g_zappy->exec.lens[F_INCANTATION] = 11;
  g_zappy->exec.lens[F_FORK] = 4;
  g_zappy->exec.lens[F_CONNECT] = 7;
}

void		init_player_delays()
{
  g_zappy->exec.delays[F_AVANCE] = 7 / (float)g_zappy->delay;
  g_zappy->exec.delays[F_DROITE] = 7 / (float)g_zappy->delay;
  g_zappy->exec.delays[F_GAUCHE] = 7 / (float)g_zappy->delay;
  g_zappy->exec.delays[F_VOIR] = 7 / (float)g_zappy->delay;
  g_zappy->exec.delays[F_INVENTAIRE] = 1 / (float)g_zappy->delay;
  g_zappy->exec.delays[F_PREND] = 7 / (float)g_zappy->delay;
  g_zappy->exec.delays[F_POSE] = 7 / (float)g_zappy->delay;
  g_zappy->exec.delays[F_EXPULSE] = 7 / (float)g_zappy->delay;
  g_zappy->exec.delays[F_BROADCAST] = 7 / (float)g_zappy->delay;
  g_zappy->exec.delays[F_INCANTATION] = 300 / (float)g_zappy->delay;
  g_zappy->exec.delays[F_FORK] = 42 / (float)g_zappy->delay;
  g_zappy->exec.delays[F_CONNECT] = 0;
}

void		init_player_ptabstr()
{
  g_zappy->exec.ptabstr[F_AVANCE] = "avance";
  g_zappy->exec.ptabstr[F_DROITE] = "droite";
  g_zappy->exec.ptabstr[F_GAUCHE] = "gauche";
  g_zappy->exec.ptabstr[F_VOIR] = "voir";
  g_zappy->exec.ptabstr[F_INVENTAIRE] = "inventaire";
  g_zappy->exec.ptabstr[F_PREND] = "prend";
  g_zappy->exec.ptabstr[F_POSE] = "pose";
  g_zappy->exec.ptabstr[F_EXPULSE] = "expulse";
  g_zappy->exec.ptabstr[F_BROADCAST] = "broadcast";
  g_zappy->exec.ptabstr[F_INCANTATION] = "incantation";
  g_zappy->exec.ptabstr[F_FORK] = "fork";
  g_zappy->exec.ptabstr[F_CONNECT] = "connect_nbr";
}

void		init_player_pptr()
{
  g_zappy->exec.pptr[F_AVANCE] = PPTR_PREFIX(avance);
  g_zappy->exec.pptr[F_DROITE] = PPTR_PREFIX(droite);
  g_zappy->exec.pptr[F_GAUCHE] = PPTR_PREFIX(gauche);
  g_zappy->exec.pptr[F_VOIR] = PPTR_PREFIX(voir);
  g_zappy->exec.pptr[F_INVENTAIRE] = PPTR_PREFIX(inventaire);
  g_zappy->exec.pptr[F_PREND] = PPTR_PREFIX(prend);
  g_zappy->exec.pptr[F_POSE] = PPTR_PREFIX(pose);
  g_zappy->exec.pptr[F_EXPULSE] = PPTR_PREFIX(expulse);
  g_zappy->exec.pptr[F_BROADCAST] = PPTR_PREFIX(broadcast);
  g_zappy->exec.pptr[F_INCANTATION] = PPTR_PREFIX(incantation);
  g_zappy->exec.pptr[F_FORK] = PPTR_PREFIX(fork);
  g_zappy->exec.pptr[F_CONNECT] = PPTR_PREFIX(connect_nbr);
}
