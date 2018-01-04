/*
** cmd_mort.c for zappy in /home/potier_v/rendu/PSU_2014_zappy/server
**
** Made by Valentin Potier
** Login   <potier_v@epitech.net>
**
** Started on  Wed Jun 24 19:31:33 2015 Valentin Potier
** Last update Sun Jun 28 17:16:40 2015 Alexis Bevillard
*/

#include	"zappy.h"
#include	"zappy/player.h"

int		zappy_mort(t_player *player)
{
  send_message(player, "mort\n");
  return (0);
}
