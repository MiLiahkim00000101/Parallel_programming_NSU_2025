#include <chrono>
#include <thread>
#include <iostream>
#include <mutex>

// Структура, содержащая мьютекс для защиты данных
struct CriticalData
{
    std::mutex mut;
};

// Функция, демонстрирующая безопасное захватывание нескольких мьютексов
void deadlock(CriticalData &a, CriticalData &b)
{
    std::scoped_lock scop_lock(a.mut, b.mut); // Используем scoped_lock для предотвращения deadlock
    std::cout << "One lock\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Имитация работы
    std::cout << "Two lock\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main()
{
    CriticalData a;
    CriticalData b;

    // Запуск потоков, передающих ресурсы в разном порядке
    std::thread t1([&]{deadlock(a,b);});
    std::thread t2([&]{deadlock(b,a);});

    t1.join();
    t2.join();

    return 0;
}