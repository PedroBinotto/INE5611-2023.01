#ifndef __ICLIENT_H__
#define __ICLIENT_H__

#include <utility>

class InterfaceClient {
  long _board;
  void draw(void);

public:
  InterfaceClient(void);
  std::pair<int, int> start(void);
  void stop(void);
  void setBoard(long state);
  void ref(void);
};

#endif
