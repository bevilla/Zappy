//
// main.cpp for zappy in /home/chardo_j/rendu/PSU_2014_zappy/graph/src
//
// Made by Julien Chardon
// Login   <chardo_j@epitech.net>
//
// Started on  Wed Jun 10 11:39:28 2015 Julien Chardon
// Last update Tue Jun 30 17:54:46 2015 Alexis Bevillard
//

#include <cstdlib>
#include <iostream>
#include "Window.hpp"

int		launch_win(const std::string &addr, int port)
{
  Window	win(addr, port);

  if (!win.init())
    return EXIT_FAILURE;
  win.manage();
  return EXIT_SUCCESS;
}

bool		isnum(char *port)
{
  while (*(port++))
    if (*(port - 1) < '0' || *(port - 1) > '9')
      return false;
  return true;
}

int		main(int ac, char **av)
{
  if (ac != 3)
    {
      std::cout << "Usage: " << av[0] << " [IP] [PORT]" << std::endl;
      return EXIT_FAILURE;
    }
  if (isnum(av[2]))
    return launch_win(av[1], atoi(av[2]));
  std::cout << "Error: the port must be an integer" << std::endl;
  return EXIT_FAILURE;
}
