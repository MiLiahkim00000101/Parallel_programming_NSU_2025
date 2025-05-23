#include <iostream>
#include <thread>

// Функция, передаваемая в поток
void helloFun()
{
    std::cout << "Hello from a function." << std::endl;
}

// Класс с перегруженным оператором (), используемый как функтор
class HelloThread
{
public:
    void operator()() const
    {
        std::cout << "Hello from a functor." << std::endl;
    }
};

int main()
{
    // Создание потока с функцией
    std::thread t1(helloFun);

    // Создание потока с функтором
    HelloThread hello_class;
    std::thread t2(hello_class);

    // Создание потока с лямбда-функцией
    std::thread t3([]{std::cout << "Hello from a lambda." << std::endl;});

    // Ожидание завершения потоков
    t1.join();
    t2.join();
    t3.join();

    std::cout << std::endl;
    return 0;
}
