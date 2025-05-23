#include <iostream>
#include <thread>
#include <string>
#include <functional>

// Функция, передаваемая в поток
void helloFun(std::string &str)
{
    std::cout << "Hello from a function, " + str << std::endl;
}

// Класс с перегруженным оператором (), используется как функтор
class HelloThread
{
public:
    HelloThread(std::string arg0): _str(arg0){}

    void operator()() const
    {
        std::cout << "Hello from a functor, " + this->_str << std::endl;
    }
private:
    std::string _str; // Аргумент для вывода
};

int main()
{
    // Аргументы для потоков
    std::string thread1_arg{"plus argument 1"};
    std::string thread2_arg{"plus argument 2"};
    std::string thread3_arg{"plus argument 3"};

    // Создание потока с функцией
    std::thread t1(helloFun, std::ref(thread1_arg));

    // Создание потока с функциональным объектом
    HelloThread hello_class(thread2_arg);
    std::thread t2(hello_class);

    // Создание потока с лямбда-функцией
    std::thread t3([thread3_arg]{
                    std::cout << "Hello from a lambda, " 
                    + thread3_arg << std::endl;
                    });

    // Ожидание завершения потоков
    t1.join();
    t2.join();
    t3.join();

    std::cout << std::endl;
    return 0;
}