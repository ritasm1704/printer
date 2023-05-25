#ifndef WRITER_H
#define WRITER_H

#include <mutex>
#include <condition_variable>
#include <fstream>

#include "threads/myQueue.h"
#include "threads/dataMsg.h"

class Writer {

private:
    std::condition_variable &cv;
    std::mutex mtx;
    MyQueue<DataMsg> &q;

public:
    bool reading_is_stopped = false;

    Writer(std::condition_variable &cv_, MyQueue<DataMsg> &q_) : cv(cv_), q(q_) {
        //q = std::shared_ptr<MyQueue<DataMsg>>(q_);
    }

    void write(size_t size) {
        std::ofstream fout;
        fout.open("out_file.txt");
        int count = 0;
        time_t start, end;
        time(&start);
        while (true)
        {
            std::cout << "Thread-write " << count << std::endl;
            std::unique_lock<std::mutex> lck(mtx);
            while (q.isEmpty())
            {
                if (reading_is_stopped) {
                    break;
                }
                //std::cout << "Thread-write is weiting" << std::endl;
                cv.wait(lck);
            }
            if (reading_is_stopped) {
                break;
            }
            //std::cout << "Thread-write " << count << std::endl;
            DataMsg dm = q.getValue();
            uint8_t* data = dm.offset;
            size_t size_bloc = dm.size;
            uint8_t* i = data;
            //std::cout << "Thread-write - " << (unsigned)*data << " " << (unsigned)*(data + 1) << std::endl;
            while (i != data + size_bloc) {
                fout << (unsigned)*i;
                i += 1;
            }
            count++;

            if (count == size)  {
                break;
            }
            //std::cout << "Thread-write in out2" << count << std::endl;
        }

        fout.close();

        time(&end);
        double time_taken = double(end - start);
        std::cout << "write speed: "<< size / time_taken << "Mb/sec" << std::endl;

        std::cout << "Thread-write in out" << std::endl;
    }
};


#endif