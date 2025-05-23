#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// Функция, выполняемая в потоке
void thread_fn() {
    using namespace std::chrono_literals;

    std::this_thread::sleep_for(1s); // Имитация работы
    std::cout << "One\n";
    std::this_thread::sleep_for(1s);
    std::cout << "Two\n";  
}

int main()
{
    // Создание потока
    std::thread t1(thread_fn);
  
    // Отсоединение потока (поток будет выполняться в фоновом режиме)
    t1.detach();
    
    return 0; // Основной поток завершает выполнение, но отсоединенный поток продолжает работу
}
