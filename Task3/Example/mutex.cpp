#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
#include <vector>

std::mutex mut; // Глобальный мьютекс для синхронизации потоков

// Функция работы с ресурсом, использующая ручную блокировку и разблокировку мьютекса
void workOnResource()
{
    mut.lock(); // Захват мьютекса
    std::cout << "lock \n";
    std::cout << "id thread " << std::this_thread::get_id() << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Имитация работы
    mut.unlock(); // Освобождение мьютекса
}

int main()
{
    std::vector<std::thread> threads;
    size_t num_threads = 10;

    // Создание 10 потоков
    for (size_t i = 0; i < num_threads; ++i)
    {
        threads.push_back(std::thread(workOnResource));
    }

    // Ожидание завершения всех потоков
    for (size_t i = 0; i < num_threads; ++i)
    {
        threads[i].join();
    }
    
    return 0;
}