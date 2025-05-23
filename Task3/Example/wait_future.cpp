#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// Функция, которая устанавливает значение в std::promise после задержки
void getAnswer(std::promise<int> intPromise)
{
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(3s); // Имитация задержки вычислений
    intPromise.set_value(42); // Устанавливаем результат в promise
}

int main()
{
    std::promise<int> answerPromise; // Создание promise
    auto fut = answerPromise.get_future(); // Получение future для ожидания результата

    std::thread prodThread(getAnswer, std::move(answerPromise)); // Запуск потока с передачей promise

    std::future_status status{};
    do
    {   
        status = fut.wait_for(std::chrono::milliseconds(200)); // Проверка готовности результата каждые 200 мс
        std::cout << "... doing something else" << std::endl; // Имитируем работу основного потока
    } while (status != std::future_status::ready); // Ожидание завершения
    
    std::cout << std::endl;
    std::cout << "The Answer : " << fut.get() << '\n'; // Получение результата
    
    prodThread.join(); // Ожидание завершения потока
}