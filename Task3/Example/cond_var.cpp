#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

std::mutex mutex_;
std::condition_variable condVar;

bool dataReady{false};

// Функция обработки данных
void doTheWork()
{
    std::cout << "Processing shared data." << std::endl;
}

// Поток, ожидающий сигнал о готовности данных
void waitingForWork()
{
    std::cout << "Worker: Waiting for work." << std::endl;

    std::unique_lock<std::mutex> lck(mutex_);
    // Ожидание, пока dataReady станет true
    condVar.wait(lck, [] { return dataReady; });
    doTheWork();
    std::cout << "Work done." << std::endl;
}

// Поток, устанавливающий готовность данных
void setDataReady()
{
    {
        std::lock_guard<std::mutex> lck(mutex_);
        dataReady = true;
    }

    std::cout << "Sender : Data is ready." << std::endl;
    condVar.notify_one(); // Оповещение ожидающего потока
}

int main()
{
    std::cout << std::endl;
    std::thread t1(waitingForWork);
    std::thread t2(setDataReady);

    t1.join();
    t2.join();

    std::cout << std::endl;
    return 0;
}
