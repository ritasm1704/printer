#ifndef READER_H
#define READER_H

#include "threads/myQueue.h"
#include "threads/dataMsg.h"

#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>

class Reader {

private:
    std::condition_variable &cv;
    std::vector<uint8_t> buffer;
    MyQueue<DataMsg> &q;
    size_t size_bloc; //1 байт, который передаем второму потоку

public:
    Reader(std::condition_variable &cv_, MyQueue<DataMsg> &q_, size_t size_bloc_ = 1000'000) : cv(cv_), q(q_), size_bloc(size_bloc_) {

    }

    
    int read(int times_per_sec, size_t size) {

        buffer.resize(256*1000'000*sizeof(uint8_t));
        size_t count = 0;
        for (int i = 0; i < size; i++) {
            //std::cout << "Thread-read - " << i << std::endl;
            for (int j = 0; j < size_bloc; j++) {
                buffer[count] = (uint8_t)(count);
                //std::cout  << count << " ";
                count += 1;
                count %= 256;
            }
            //std::cout << std::endl;
        }

        uint8_t* start = buffer.data();
        std::cout << "Thread-read start - " << (unsigned)*start << " " << (unsigned)*(start + 1) << std::endl;
        for (int i = 0; i < size; i++) {
            DataMsg dm;
            dm.offset = start;
            dm.size = size_bloc;
            try { 
                //std::cout << "Thread-read putting" << std::endl;
                q.put(dm);
            } catch(const QueueOverflow& e)
            {
                std::cout << "queue overflow" << std::endl;
                return 1;
            }
            
            start += size_bloc;
            cv.notify_one();  
            std::cout << "Thread-read " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000/times_per_sec));
        }
        std::cout << "Thread-read in out" << std::endl;
        return 0;
    }
};


#endif