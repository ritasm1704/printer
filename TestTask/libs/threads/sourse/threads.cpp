#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <vector>
#include <iostream>
#include <fstream>

std::mutex mtx;
std::condition_variable cv;
std::queue<uint8_t*> buf_queue;
bool reading_is_stopped = false;
size_t size_bloc = 1000'000; //1 байт, который передаем второму потоку


void write(size_t size)
{
  //std::cout << "Thread-write: size = " << size << std::endl;
  std::ofstream fout;
  fout.open("out_file.txt");
  int count = 0;
  while (true)
  {
    //std::cout << "Thread-write " << count << std::endl;
    if (count == size || reading_is_stopped)  {
      break;
    }
    
    //int data[2];
    std::unique_lock<std::mutex> lck(mtx);
    
    while (buf_queue.empty())
    {
      if (reading_is_stopped) {
        break;
      }
      cv.wait(lck);
    }
    if (buf_queue.empty() && reading_is_stopped) {
      break;
    }
    //std::cout << "Thread-write " << count << std::endl;
    uint8_t* data = buf_queue.front();
    uint8_t* i = data;
    std::cout << "Thread-write - " << (unsigned)*data << " " << (unsigned)*(data + 1) << std::endl;
    while (i != data + size_bloc) {
      fout << (unsigned)*i;
      i += 1;
    }
    buf_queue.pop();
    count++;
    //std::cout << "Thread-write in out2" << count << std::endl;
  }
  fout.close();
  std::cout << "Thread-write in out" << std::endl;
}

// количество раз в секкунду, объем данных
void read(int times_per_sec, size_t size)
{
  std::thread func_wr(write, size);

  std::vector<uint8_t> buffer;
  buffer.resize(256*1000'000*sizeof(uint8_t));
  size_t count = 0;
  for (int i = 0; i < size; i++) {
    std::cout << "Thread-read - " << i << std::endl;
    for (int j = 0; j < size_bloc; j++) {
      buffer[count] = (uint8_t)(count % 256);
      //std::cout  << count << " ";
      count += 1;
    }
    //std::cout << std::endl;
  }

  uint8_t* start = buffer.data();
  std::cout << "Thread-read start - " << (unsigned)*start << " " << (unsigned)*(start + 1) << std::endl;
  for (int i = 0; i < size; i++) {
    {
      std::unique_lock<std::mutex> lck(mtx);
      if (buf_queue.size() == 256) {
        std::cout << "Thread-read is stopped, buf_queue.size() == 256" << std::endl;
        reading_is_stopped = true;
        cv.notify_one();
        break;
      }
      buf_queue.push(start);
      start += size_bloc;
      cv.notify_one();
    }
    //std::cout << "Thread-read " << i << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000/times_per_sec));
  }

  func_wr.join();
  std::cout << "Thread-read in out" << std::endl;
}

int main() {
 
    std::thread func_read(read, 10000, 10);
 
    func_read.join();
    
    
    return 0;
 
}