#include <iostream>
#include "ThreadPool.hpp"

void *routine(void* data)
{
  int j = 0;
  (void)data;

  std::cout << "Thread " << pthread_self() << " begining of task." << std::endl;
  while (j++ < 1000000000)
    ;
  std::cout << "Thread " << pthread_self() << " ending of task." << std::endl;
  return NULL;
}

int main()
{
  ThreadPool Tp(7);
  int i;

  for (i = 0; i < 2000; ++i)
    Tp.AsyncExec(routine, NULL);
  Tp.WaitThreads();
  return (0);
}
