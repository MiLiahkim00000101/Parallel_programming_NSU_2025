#include <chrono>
#include <future>
#include <thread>
#include <iostream>

int main()
{
    // Запоминаем время начала выполнения
    auto begin = std::chrono::high_resolution_clock::now();

    // Запуск отложенного (lazy) асинхронного выполнения
    auto asyncLazy = std::async(std::launch::deferred,
                                []{ return std::chrono::high_resolution_clock::now(); });

    // Запуск немедленного (eager) асинхронного выполнения
    auto asyncEager = std::async(std::launch::async,
                                 []{ return std::chrono::high_resolution_clock::now(); });

    // Приостанавливаем главный поток на 1 секунду
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Получаем время запуска задач
    auto lazyStart = asyncLazy.get() - begin;
    auto eagerStart = asyncEager.get() - begin;
    auto lazyDuration = std::chrono::duration<double>(lazyStart).count();
    auto eagerDuration = std::chrono::duration<double>(eagerStart).count();

    // Вывод времени запуска отложенного и немедленного выполнения
    std::cout << "asyncLazy evaluated after : " << lazyDuration
              << " seconds." << std::endl;
    std::cout << "asyncEager evaluated after : " << eagerDuration
              << " seconds." << std::endl;
}