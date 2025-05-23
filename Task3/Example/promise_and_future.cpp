#include <future>
#include <iostream>
#include <thread>
#include <utility>

// Функция для вычисления произведения с передачей результата через std::promise
void product(std::promise<int> &&intPromise, int a, int b)
{
    intPromise.set_value(a * b); // Устанавливаем результат в promise
}

// Функтор для выполнения деления с обработкой исключений
struct Div
{
    void operator()(std::promise<int> &&intPromise, int a, int b) const
    {
        try
        {   
            if (b == 0) throw std::runtime_error("Div zero!"); // Проверяем деление на 0
            int temp = a / b;
            intPromise.set_value(temp);
        }
        catch (...)
        {
            try
            {
                // Передаем исключение в promise
                intPromise.set_exception(std::current_exception());
            }
            catch (...) // Обработка возможных исключений
            {
            }
        }
    }
};

int main()
{
    int a = 20;
    int b = 0;

    // Определяем promise для передачи результатов
    std::promise<int> prodPromise;
    std::promise<int> divPromise;

    // Получаем future для получения результатов
    std::future<int> prodResult = prodPromise.get_future();
    std::future<int> divResult = divPromise.get_future();

    try
    {
        // Создаем потоки для выполнения вычислений
        std::jthread prodThread(product, std::move(prodPromise), a, b);
        Div div;
        std::jthread divThread(div, std::move(divPromise), a, b);

        // Получаем результаты вычислений
        std::cout << a <<  " * " << b << " = " << prodResult.get() << std::endl;
        std::cout << a <<  " / " << b << " = " << divResult.get() << std::endl;
    }
    catch (const std::exception &excep)
    {
        std::cout << "\nException from the thread: " << excep.what() << '\n';
    }
    
    std::cout << std::endl;
}
