//
// ZappyError.hpp for zappy in /home/bevill_a/rendu/PSU_2014_zappy/graph/inc
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Tue Jun 30 16:59:23 2015 Alexis Bevillard
// Last update Tue Jun 30 17:00:21 2015 Alexis Bevillard
//

#pragma once

#include	<exception>
#include	<string>

class		ZappyError : public std::exception
{
protected:
  std::string	_message;

public:
  ZappyError(const std::string &message) : _message(message) {}
  virtual ~ZappyError() throw () {}

public:
  const char	*what() const throw() { return _message.c_str(); }
};
