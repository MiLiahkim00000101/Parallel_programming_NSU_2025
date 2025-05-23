#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
#include <vector>

std::mutex mut; // Глобальный мьютекс для синхронизации потоков

// Функция работы с ресурсом с использованием std::lock_guard
void workOnResource()
{
    std::lock_guard<std::mutex> lock{mut}; // Автоматическая блокировка мьютекса
    std::cout << "lock \n";
    std::cout << "id thread " << std::this_thread::get_id() << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Имитация работы
}

// Функция работы с ресурсом с использованием std::unique_lock
void workOnResource_unique()
{
    std::unique_lock<std::mutex> u_lock{mut, std::defer_lock}; // Отложенная блокировка
    u_lock.lock(); // Явная блокировка
    std::cout << "lock \n";
    std::cout << "id thread " << std::this_thread::get_id() << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    u_lock.unlock(); // Явное освобождение мьютекса
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
    for (auto& thr: threads)
    {
        thr.join();
    }
    
    return 0;
}