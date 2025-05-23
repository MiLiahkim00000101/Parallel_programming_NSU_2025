#include <future>
#include <thread>
#include <iostream>

int main()
{
    std::cout << std::endl;

    int res;
    
    // Использование std::thread
    std::thread t([&]{ res = 2000 + 11; });
    t.join(); // Ожидание завершения потока

    std::cout << "res : " << res << std::endl;
    
    // Использование std::async для выполнения задачи в отдельном потоке
    auto fut = std::async([]{ return 2000 + 11; });

    std::cout << "fut.get() : " << fut.get() << std::endl;
    std::cout << std::endl;
}
