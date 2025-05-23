#include <iostream>
#include <csignal>

// Функция-обработчик сигнала деления на ноль
void signal_handler(int signal)
{
    std::cout << "Division by zero detected!\n";
    std::exit(1); // Завершаем программу с ошибкой
}

int main() 
{ 
    // Устанавливаем обработчик сигнала SIGFPE (ошибка арифметики)
    std::signal(SIGFPE, signal_handler);

    try 
    { 
        int result = 1 / 0; // Попытка деления на ноль (неопределенное поведение)
        std::cout << "Result: " << result << std::endl; 
    } 
    catch (const std::exception& e) 
    { 
        std::cout << "Exception caught: " << e.what()  << std::endl; 
    } 
  
    return 0; 
}