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

    std::cout << "time_per_sec = " << time_per_sec << ", size = " << size << "Mb" << std::endl;
    std::condition_variable cv;
    MyQueue<DataMsg> mq;
    std::shared_ptr<Reader> r = std::make_shared<Reader>(cv, mq);
    std::shared_ptr<Writer> w = std::make_shared<Writer>(cv, mq);
    
    int ex = -1;
    std::thread reader_thread([&]{
        ex = r->read(time_per_sec, size);
        if (ex == 1) {
            w->reading_is_stopped = true;
            cv.notify_one();
        }
    });

    std::thread writer_thread([&]{
        w->write(size);
    });

    reader_thread.join();
    
    writer_thread.join();
    
    return 0;
 
}