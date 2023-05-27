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
    ReadingStatus &rs;
    size_t data_size;
    size_t size_bloc; //1 байт, который передаем второму потоку

public:
    Reader(std::condition_variable &cv_, MyQueue<DataMsg> &q_, ReadingStatus &rs_, size_t data_size_, size_t size_bloc_ = 1000'000) : 
    cv(cv_), q(q_), rs(rs_), data_size(data_size_), size_bloc(size_bloc_) {

        buffer.resize(256*1000'000*sizeof(uint8_t));
        size_t count = 0;
        for (int i = 0; i < data_size; i++) {
            for (int j = 0; j < size_bloc; j++) {
                buffer[count] = (uint8_t)(count);
                count += 1;
                count %= 256;
            }
        }
    }

    
    void read(int times_per_sec) {

        uint8_t* start = buffer.data();
        std::cout << "Thread-read start - " << (unsigned)*start << " " << (unsigned)*(start + 1) << std::endl;
        for (int i = 0; i < data_size; i++) {
            DataMsg dm;
            dm.offset = start;
            dm.size = size_bloc;
            try { 
                //std::cout << "Thread-read putting" << std::endl;
                q.put(dm);
            } catch(const QueueOverflow& e)
            {
                rs = ReadingStatus::reading_is_stopped;
                cv.notify_one();  
                std::cout << "queue overflow" << std::endl;
                break;
            }
            
            start += size_bloc;
            cv.notify_one();  
            std::cout << "Thread-read " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000/times_per_sec));
        }
        std::cout << "Thread-read in out" << std::endl;
    }
};


#endif