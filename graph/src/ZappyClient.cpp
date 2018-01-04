//
// ZappyClient.cpp for test in /home/bevill_a/test/socket_cpp
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Sat Jun 27 22:19:41 2015 Alexis Bevillard
// Last update Fri Jul  3 18:44:47 2015 Alexis Bevillard
//

#include		<iostream>
#include		<sys/socket.h>
#include		<netinet/in.h>
#include		<arpa/inet.h>
#include		<sys/types.h>
#include		<sys/time.h>
#include		<unistd.h>
#include		<signal.h>
#include		<netdb.h>
#include		"ZappyClient.hpp"

ZappyClient::ZappyClient(const std::string &addr, int port) :
  _isConnected(false),
  _addr(addr),
  _port(port),
  _bufOffset(0),
  _msgOffset(0),
  _msgLen(0)
{
}

ZappyClient::~ZappyClient()
{
  if (_isConnected)
    close(_fd);
}

void			ZappyClient::setAddr(const std::string &addr)
{
  _addr = addr;
}

void			ZappyClient::setPort(int port)
{
  _port = port;
}

const std::string	&ZappyClient::getAddr() const
{
  return _addr;
}

int			ZappyClient::getPort()
{
  return _port;
}

void			ZappyClient::setWindow(Window &win)
{
  _win = &win;
  _parseCmd.setWindow(win);
}

bool			ZappyClient::connectToServer()
{
  struct hostent	*he;
  struct protoent	*pe;
  struct sockaddr_in	sin;

  if ((pe = getprotobyname("TCP")) == NULL)
    {
      std::cerr << "Error: cannot retrieve TCP protoent structure" << std::endl;
      return false;
    }
  if ((_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) < 0)
    {
      std::cerr << "Error: cannot create socket" << std::endl;
      return false;
    }

  if ((he = gethostbyname(_addr.c_str())) == NULL)
    {
      std::cerr << "Error: '" << _addr << "': unkown address" << std::endl;
      return false;
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(_port);
  sin.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr *)he->h_addr_list[0])));
  std::cout << "Connection to " << inet_ntoa(*((struct in_addr *)he->h_addr_list[0])) << ":" << _port << " ..." << std::flush;
  if (connect(_fd, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
      std::cerr << " KO" << std::endl << "Error: cannot reach the server" << std::endl;
      return false;
    }
  std::cout << " OK !" << std::endl;
  _isConnected = true;
  _parseCmd.setFd(_fd);
  signal(SIGPIPE, SIG_IGN);
  return true;
}

bool			ZappyClient::isConnected() const
{
  return _isConnected;
}

int			is_ending_char(char *buf, int buf_offset, int len)
{
  if (buf[buf_offset] == '\n')
    return (0);
  else if (buf[buf_offset] == '\r' &&
           (buf_offset + 1) < len &&
           buf[buf_offset + 1] == '\n')
    return (0);
  return (-1);
}

bool			ZappyClient::canRead()
{
  struct timeval	tv;
  fd_set		rfds;
  int			retval;

  tv.tv_usec = 0;
  tv.tv_sec = 0;
  FD_ZERO(&rfds);
  FD_SET(_fd, &rfds);
  retval = select(_fd + 1, &rfds, NULL, NULL, &tv);
  if (retval < 0)
    {
      if (_isConnected)
	std::cerr << "Error: select failed" << std::endl;
      disconnect();
      return false;
    }
  else if (retval && FD_ISSET(_fd, &rfds))
    {
      if (_msgLen == _bufOffset)
	{
	  if ((_msgLen = read(_fd, _buf, SIZE_MSG)) <= 0)
	    {
	      std::cerr << "Error: server disconnected" << std::endl;
	      disconnect();
	      return false;
	    }
	  _bufOffset = 0;
	}
    }
  if (_msgLen != _bufOffset)
    {
      while (is_ending_char(_buf, _bufOffset, _msgLen) &&
	     _bufOffset < _msgLen &&
	     _msgOffset < SIZE_MSG)
	_msg[_msgOffset++] = _buf[_bufOffset++];
      _msg[_msgOffset] = '\0';
      if (_buf[_bufOffset] == '\n' || _buf[_bufOffset] == '\r')
	{
	  _bufOffset += (_buf[_bufOffset] == '\n' ? 1 : 2);
	  _msgOffset = 0;
	  return true;
	}
      if (_msgOffset == SIZE_MSG)
	{
	  _msgOffset = 0;
	  return true;
	}
    }
  return false;
}

const std::string	ZappyClient::getMessage() const
{
  return std::string(_msg);
}

bool			ZappyClient::sendMessage(const std::string &msg)
{
  if (write(_fd, msg.c_str(), msg.size()) < 0)
    {
      disconnect();
      return false;
    }
  return true;
}

void			ZappyClient::disconnect()
{
  _isConnected = false;
  close(_fd);
}

bool			ZappyClient::parseMessage(const std::string &msg)
{
  if (!_parseCmd.parseMessage(msg))
    return false;
  _parseCmd.callFunc();
  return true;
}
