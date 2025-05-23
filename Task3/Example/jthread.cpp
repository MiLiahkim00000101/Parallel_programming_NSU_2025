#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// Функция, выполняемая в потоке
void thread_fn() {
    using namespace std::chrono_literals;

    std::this_thread::sleep_for(1s);
    std::cout << "One\n";
    std::this_thread::sleep_for(1s);
    std::cout << "Two\n";  
}

int main()
{
    // Создание потока с использованием std::jthread
    std::jthread t1(thread_fn);
    
    // std::jthread автоматически завершает поток в деструкторе
    return 0; 
}
