#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <vector>
#include <iostream>
#include <fstream>

#include "threads/reader.h"
#include "threads/writer.h"

int main(int argc, char *argv[]) {
 
    if (argc < 2) {
        std::cout << "incorrect input" << std::endl;
    } 
    int time_per_sec;
    sscanf(argv[1], "%d", &time_per_sec);
    int size;
    sscanf(argv[2], "%d", &size);

    std::cout << "time_per_sec = " << time_per_sec << ", data size = " << size << "Mb" << std::endl;
    std::condition_variable cv;
    MyQueue<DataMsg> mq;
    bool reading_is_stopped = false;
    std::unique_ptr<Reader> r = std::make_unique<Reader>(cv, mq, reading_is_stopped, size);
    std::unique_ptr<Writer> w = std::make_unique<Writer>(cv, mq, reading_is_stopped);
    
    std::thread reader_thread([&]{
        r->read(time_per_sec);
    });

    std::thread writer_thread([&]{
        w->write(size);
    });

    reader_thread.join();
    
    writer_thread.join();
    
    return 0;
 
}