#include <chrono>
#include <thread>
#include <iostream>
#include <mutex>

// Структура, содержащая мьютекс для защиты данных
struct CriticalData
{
    std::mutex mut;
};

// Функция, демонстрирующая ситуацию взаимной блокировки (deadlock)
void deadlock(CriticalData &a, CriticalData &b)
{
    a.mut.lock(); // Блокируем первый мьютекс
    std::cout << "One lock\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Имитация задержки
    b.mut.lock(); // Блокируем второй мьютекс (возможен deadlock)
    std::cout << "Two lock\n";
    
    a.mut.unlock();
    b.mut.unlock();
}

int main()
{
    CriticalData a;
    CriticalData b;

    // Запуск двух потоков, которые могут вызвать взаимную блокировку
    std::thread t1([&]{deadlock(a, b);});
    std::thread t2([&]{deadlock(b, a);});

    t1.join();
    t2.join();

    return 0;
}
