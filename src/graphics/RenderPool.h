#ifndef GL_ADAGIO_RENDERPOOL_H
#define GL_ADAGIO_RENDERPOOL_H

#include <string>
#include <vector>

template <typename T> class RenderPool {
public:
  RenderPool();

  void createNew(int number);

  T *getNext();

  void begin();

  void debugInfo(std::string poolName);

private:
  int current;
  std::vector<T> pool;
};

#include "RenderPool-impl.h"

#endif // GL_ADAGIO_RENDERPOOL_H
