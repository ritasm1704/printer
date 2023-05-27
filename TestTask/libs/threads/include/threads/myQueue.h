#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

class QueueOverflow {
};

template <typename Type>
class MyQueue
{
private:
    std::queue<Type> buf_queue;
    std::mutex mtx;

public:
    MyQueue() {

    }

    void put(Type value) {
        std::unique_lock<std::mutex> lck(mtx);
        if (buf_queue.size() >= 256) {
            throw QueueOverflow();
        } else {
            buf_queue.push(value);
        }
    }

    Type getValue() {
        std::unique_lock<std::mutex> lck(mtx);
        Type v = buf_queue.front();
        buf_queue.pop();
        return v;
    }

    bool isEmpty() {
        std::unique_lock<std::mutex> lck(mtx);
        return buf_queue.empty();
    }
};

#endif