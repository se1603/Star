/* Author:王梦娟
 * Date:2019-4-25
 * Note:线程池
*/
#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <memory>
#include <functional>
#include <condition_variable>

const int Max_THREADS = 100;   //最大线程数

typedef std::function<void(void)> Task;

class ThreadPool
{
public:
    ThreadPool(int number = 10);   //默认开一个线程
    ~ThreadPool();

    bool append(Task task);    //添加任务

private:
    static void *worker(void *arg);
    void run();

private:
    std::vector<std::thread> work_threads;  //工作线程
    std::queue<Task> tasks_queue;           //任务队列

    std::mutex queue_mutex;
    std::condition_variable condition;      //条件变量
    bool stop;
};

#endif // THREADPOOL_H
