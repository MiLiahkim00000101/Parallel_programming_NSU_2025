#include <iostream>
#include <string>
#include <mutex>
#include <thread>

std::mutex coutMutex; // Мьютекс для защиты вывода в консоль

// thread_local переменная, уникальная для каждого потока
thread_local std::string s("hello from ");

// Функция, использующая thread_local переменную
void addThreadLocal(std::string const &s2)
{
    s += s2; // Добавление уникального значения для каждого потока
    
    // Защищаем std::cout мьютексом
    std::lock_guard<std::mutex> guard(coutMutex);
    std::cout << s << std::endl;
    std::cout << "& s : " << &s << std::endl;
    std::cout << std::endl;
}

int main()
{
    std::cout << std::endl;
    
    // Создание потоков, каждый из которых использует свою копию thread_local переменной
    std::thread t1(addThreadLocal, "t1");
    std::thread t2(addThreadLocal, "t2");
    std::thread t3(addThreadLocal, "t3");
    std::thread t4(addThreadLocal, "t4");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}