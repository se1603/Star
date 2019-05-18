#include "threadpool.h"
#include <iostream>

ThreadPool::ThreadPool(int number) :
    stop(false)
{
    if(number <= 0 || number > Max_THREADS)
        throw std::exception();
    for(int i = 0; i < number;i++)
    {
        std::cout << "创建第" << i + 1 << "个线程" << std::endl;
        work_threads.emplace_back(ThreadPool::worker,this);
    }
}

ThreadPool::~ThreadPool()
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    stop = true;

    condition.notify_all();
    for(auto &&w : work_threads)
        w.join();
}

bool ThreadPool::append(Task task)
{
    queue_mutex.lock();
    tasks_queue.push(task);
    queue_mutex.unlock();
    condition.notify_one();  //通知等待线程
    return true;
}

void *ThreadPool::worker(void *arg)
{
    ThreadPool *pool = (ThreadPool *)arg;
    pool->run();
    return pool;
}

void ThreadPool::run()
{
    while(!stop)
    {
        std::unique_lock<std::mutex> lock(this->queue_mutex);

        //队列为空会阻塞
        this->condition.wait(lock,[this]{
            return !this->tasks_queue.empty();
        });

        //队列不为空会停下来等待唤醒
        if(this->tasks_queue.empty())
        {
            continue;
        }
        else
        {
            Task task = tasks_queue.front();
            tasks_queue.pop();
            lock.unlock();
            task();
        }
    }
}
