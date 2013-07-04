
#include "ThreadPool.hpp"

  ThreadTask::ThreadTask(const ThreadTask &cpy):
  func(cpy.func),
  data(cpy.data)
  {
  }

  ThreadTask::ThreadTask(const funcPtr cpyFunc, void * const cpyData):
  func(cpyFunc),
  data(cpyData)
  {
  }

void ThreadTask::ThreadTaskExec(void)
{
  func(data);
}

ThreadQueue::ThreadQueue() :
  terminated(false)
{
  pthread_cond_init(&cond, NULL);
  pthread_mutex_init(&mutex, NULL);
}

void ThreadQueue::setTerminated(bool b)
  {
    pthread_mutex_lock(&mutex);
    terminated = b;
    if (b == true)
      list.clear();
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
  }

unsigned ThreadQueue::getNbTask(void)
{
  return list.size();
}

void	ThreadQueue::addTask(ThreadTask *task)
{
  if (!task)
    return;
  pthread_mutex_lock(&mutex);
  list.push_front(new ThreadTask(*task));
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
}

ThreadTask *ThreadQueue::popTask()
  {
    pthread_mutex_lock(&mutex);
    if (terminated)
      {
	pthread_mutex_unlock(&mutex);
	return NULL;
      }
    while (list.size() == 0)
      {
	pthread_cond_wait(&cond, &mutex);
	if (terminated)
	  {
	    pthread_mutex_unlock(&mutex);
	    return NULL;
	  }
      }
    ThreadTask *task = list.front();
    list.pop_front();
    pthread_mutex_unlock(&mutex);
    return task;
  }



void *ThreadRoutine(void *data)
{
  ThreadPool *pool;
  
  pool = static_cast<ThreadPool*>(data);
  if (!pool)
    return NULL;
  return pool->PoolRoutine();
}


ThreadPool::ThreadPool(unsigned nbThreads):
  thread_count(0)
  {
    unsigned i;
    pthread_t thread;

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutexCondWaitThread, NULL);
    pthread_cond_init(&condWaitThread, NULL);
    threads.resize(nbThreads);
    for(i = 0; i < nbThreads; ++i)
      {
	if (pthread_create(&thread, NULL, ThreadRoutine, (void*)(this)) != -1)
	  {
	    threads[i] = thread;
	    ++thread_count;
	  }
      }
  }

  ThreadPool::~ThreadPool()
  {
    queue.setTerminated(true);    
    WaitThreads();
  }

  void ThreadPool::WaitThreads(void)
  {
    std::vector<pthread_t>::iterator it = threads.begin();
    std::vector<pthread_t>::iterator end = threads.end();
    void *ret;

    pthread_mutex_lock(&mutexCondWaitThread);
    while (queue.getNbTask() != 0)
      pthread_cond_wait(&condWaitThread, &mutexCondWaitThread);
    pthread_mutex_unlock(&mutexCondWaitThread);
    queue.setTerminated(true);
    for (; it != end; ++it)
      {
	pthread_join(*it, &ret);
	// pthread_destroy(*it);
      }
    threads.clear();
  }

  bool ThreadPool::PoolExec(ThreadTask::funcPtr function, void *data)
  {
    ThreadTask *task;

    if (!function)
      return false;
    task = new ThreadTask(function, data);
    queue.addTask(task);
    delete task;
    return true;
  }

  void *ThreadPool::PoolRoutine(void)
  {
    ThreadTask *task;

    pthread_mutex_lock(&mutex);
    ++thread_init;
    pthread_mutex_unlock(&mutex);
    while ((task = queue.popTask()) != NULL)
      {
	task->ThreadTaskExec();
	delete task;
	pthread_mutex_lock(&mutexCondWaitThread);
	pthread_cond_broadcast(&condWaitThread);
	pthread_mutex_unlock(&mutexCondWaitThread);
      }
    return (NULL);
  }
  
  bool ThreadPool::AsyncExec(ThreadTask::funcPtr function, void *data)
  {
    return PoolExec(function, data);
  }
