#include <iostream>
#include <mutex>
#include <thread>
#include <barrier>

std::mutex coutMutex;

// Функция для потокобезопасного вывода в консоль
void synchronizedOut(const std::string &s)
{
    std::lock_guard<std::mutex> lo(coutMutex);
    std::cout << s;
}

// Барьер, который будет синхронизировать 6 потоков
std::barrier workDone(6, []{
                        synchronizedOut("Work end!\n\n");
});

class Worker
{
public:
    Worker(std::string n) : name(n){};

    void operator()()
    {
        // Вывод сообщения перед первой синхронизацией
        synchronizedOut(name + ": " + "Morning work done!\n");
        workDone.arrive_and_wait(); // Ожидание всех потоков

        // Вывод сообщения перед второй синхронизацией
        synchronizedOut(name + ": " + "Afternoon work done!\n");
        workDone.arrive_and_wait();
    }
private:
    std::string name;
};

int main()
{
    std::cout << '\n';

    // Создание и запуск 6 рабочих потоков
    Worker herb(" Herb");
    std::thread herbWork(herb);

    Worker scott("  Scott");
    std::thread scottWork(scott);

    Worker bjarne("   Bjarne");
    std::thread bjarneWork(bjarne);

    Worker andrei("     Andrei");
    std::thread andreiWork(andrei);

    Worker andrew("      Andrew");
    std::thread andrewWork(andrew);

    Worker david("       David");
    std::thread davidWork(david);

    // Ожидание завершения всех потоков
    herbWork.join();
    scottWork.join();
    bjarneWork.join();
    andreiWork.join();
    andrewWork.join();
    davidWork.join();
}