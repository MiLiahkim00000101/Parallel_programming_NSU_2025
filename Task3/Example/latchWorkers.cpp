#include <iostream>
#include <mutex>
#include <thread>
#include <latch>

// latch для синхронизации 6 потоков
std::latch workDone(6);
std::mutex coutMutex;

// Потокобезопасный вывод в консоль
void synchronizedOut(const std::string &s)
{
    std::lock_guard<std::mutex> lo(coutMutex);
    std::cout << s;
}

// Класс-работник, который выполняет задачи и синхронизируется с другими
class Worker
{
public:
    Worker(std::string n) : name(n){};

    void operator()()
    {
        synchronizedOut(name + ": " + "Work done !\n");
        workDone.arrive_and_wait(); // Ожидание завершения всех потоков
        synchronizedOut(name + ": " + "See you tomorrow !\n");
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
