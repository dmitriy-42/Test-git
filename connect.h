#ifndef CONNECT_H
#define CONNECT_H

#endif // CONNECT_H

/*
#ifdef __WIN32__
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif
*/


class Connect
{
public:
  Connect() = default;
  ~Connect() = default;
  virtual void send() = 0;
  virtual void recv() = 0;
};
