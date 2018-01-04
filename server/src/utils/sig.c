/*
** sig.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Fri Jun 19 15:11:24 2015 Valentin Potier
** Last update Wed Jun 24 23:44:47 2015 Valentin Potier
*/

#include	<signal.h>
#include	<stdlib.h>
#include	<stdio.h>

void		free_zappy();

void		sighandler(int sig)
{
  if (sig == SIGINT)
    {
      free_zappy();
      fprintf(stderr, "====== Received sig %d, exiting =====\n", sig);
      exit(sig);
    }
}
