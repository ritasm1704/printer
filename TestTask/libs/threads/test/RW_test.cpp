#include <gtest/gtest.h>
#include "threads/reader.h"
#include "threads/writer.h"

TEST(RW_Test, RunningTest) {

    std::shared_ptr<MyQueue<DataMsg>> mq;
    std::shared_ptr<Reader> r = std::make_shared<Reader>(mq);
    std::shared_ptr<Writer> w = std::make_shared<Writer>(mq);
    

    std::thread reader_thread([&]{
        r->read(10, 10);
    });

    std::thread writer_thread([&]{
        w->write(10);
    });

    reader_thread.join();
    writer_thread.join();

}


