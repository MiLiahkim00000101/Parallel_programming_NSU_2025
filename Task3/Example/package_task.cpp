#include <cmath>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
 
// Функция для вычисления степени числа
int f(int x, int y) { return std::pow(x, y); }
 
// Использование std::packaged_task с лямбда-выражением
void task_lambda()
{
    std::packaged_task<int(int, int)> task([](int a, int b)
    {
        return std::pow(a, b); 
    });
    std::future<int> result = task.get_future();
 
    task(2, 9); // Выполняем задачу
  
    std::cout << "task_lambda:\t" << result.get() << '\n';
}
 
// Использование std::packaged_task с std::bind
void task_bind()
{
    std::packaged_task<int(int)> task(std::bind(f, 2, std::placeholders::_1));
    std::future<int> result = task.get_future();
 
    task(11); // Выполняем задачу
 
    std::cout << "task_bind:\t" << result.get() << '\n';
}
 
// Использование std::packaged_task в потоке
void task_thread()
{
    std::packaged_task<int(int, int)> task(f);
    std::future<int> result = task.get_future();
 
    std::thread task_td(std::move(task), 2, 10); // Передаем задачу в поток
    task_td.join(); // Ожидаем завершения потока
 
    std::cout << "task_thread:\t" << result.get() << '\n';
}
 
int main()
{
    task_lambda();
    task_bind();
    task_thread();
}