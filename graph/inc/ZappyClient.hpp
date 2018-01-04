//
// ZappyClient.hpp for test in /home/bevill_a/test/socket_cpp
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Sat Jun 27 22:15:05 2015 Alexis Bevillard
// Last update Wed Jul  1 16:28:59 2015 Alexis Bevillard
//

#pragma once

#include		<string>
#include		"ZappyError.hpp"
#include		"ParseCmd.hpp"

#define SIZE_MSG	4096

class			Window;

class			ZappyClient
{
private:
  bool			_isConnected;
  std::string		_addr;
  int			_port;
  int			_fd;
  char			_buf[SIZE_MSG];
  char			_msg[SIZE_MSG + 1];
  int			_bufOffset;
  int			_msgOffset;
  int			_msgLen;
  ParseCmd		_parseCmd;
  Window		*_win;

public:
  ZappyClient(const std::string &addr = "127.0.0.1", int port = 4242);
  ~ZappyClient();

  void			setAddr(const std::string &addr);
  void			setPort(int fd);
  const std::string	&getAddr() const;
  int		        getPort();
  void			setWindow(Window &win);

  bool			connectToServer();
  bool			isConnected() const;
  bool			canRead();
  const std::string	getMessage() const;
  bool			parseMessage(const std::string &msg);
  bool			sendMessage(const std::string &msg);
  void			disconnect();
};
