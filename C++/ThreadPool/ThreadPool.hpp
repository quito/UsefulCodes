
#ifndef THREAD_HPP_
# define THREAD_HPP_

# include <list>
# include <pthread.h>
# include <vector>
# include <iostream>

class ThreadTask
{
public :
  
  typedef void *(*funcPtr)(void *data);

private :

    funcPtr func;
    void *data;

public :

  ThreadTask(const ThreadTask &cpy);
  ThreadTask(const funcPtr cpyFunc, void * const cpyData);
  void ThreadTaskExec(void);
};

typedef std::list<ThreadTask*> ThreadTaskList;

class ThreadQueue
{
private :

  pthread_mutex_t	mutex;
  pthread_cond_t	cond;
  ThreadTaskList	list;
  bool terminated;


public :

  ThreadQueue();
  void setTerminated(bool b);
  unsigned getNbTask(void);
  void	addTask(ThreadTask *task);
  ThreadTask *popTask();
};


extern "C"
void *ThreadRoutine(void *data);

class ThreadPool
{
  pthread_mutex_t mutex;
  ThreadQueue queue;
  std::vector<pthread_t> threads;
  size_t thread_init;
  size_t thread_count;
  pthread_cond_t condWaitThread;
  pthread_mutex_t mutexCondWaitThread;

public:
  ThreadPool(unsigned nbThreads);
  ~ThreadPool();

  void WaitThreads(void);
  bool PoolExec(ThreadTask::funcPtr function, void *data);
  void *PoolRoutine(void);
  bool AsyncExec(ThreadTask::funcPtr function, void *data);
};


#endif
