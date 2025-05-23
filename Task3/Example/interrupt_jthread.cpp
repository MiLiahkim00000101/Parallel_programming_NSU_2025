#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    // Поток без возможности прерывания
    std::jthread non_interrupt([]
                               {
        int counter{0};
        while (counter < 10)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cerr << "nonInterruptable: " << counter << '\n';
            ++counter;
        } });

    // Поток с возможностью прерывания через stop_token
    std::jthread interrupt([](std::stop_token stoken)
                           {
        int counter{0};
        while (counter < 10)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            if (stoken.stop_requested()) return; // Проверка запроса на остановку
            std::cerr << "interruptable: " << counter << '\n';
            ++counter;
        } });

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cerr << '\n';
    std::cerr << "Main thread interrupts both jthreads" << "\n";
    non_interrupt.request_stop(); // Прерывание потока (не сработает)
    interrupt.request_stop(); // Прерывание потока с поддержкой stop_token

    std::cout << '\n';
}
