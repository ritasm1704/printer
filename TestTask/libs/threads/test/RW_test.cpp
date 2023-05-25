#include <gtest/gtest.h>
#include "threads/reader.h"
#include "threads/writer.h"

TEST(RW_Test, RunningTest) {

    std::condition_variable cv;
    MyQueue<DataMsg> mq;
    std::shared_ptr<Reader> r = std::make_shared<Reader>(cv, mq);
    std::shared_ptr<Writer> w = std::make_shared<Writer>(cv, mq);
    
    size_t s = 500;
    int ex = -1;
    std::thread reader_thread([&]{
        ex = r->read(1000, s);
        if (ex == 1) {
            w->reading_is_stopped = true;
            cv.notify_one();
        }
    });

    std::thread writer_thread([&]{
        w->write(s);
    });

    reader_thread.join();
    
    writer_thread.join();

}


