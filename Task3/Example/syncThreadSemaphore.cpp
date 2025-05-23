#include <iostream>
#include <semaphore>
#include <thread>
#include <vector>

std::vector<int> myVec{}; // Вектор, который будет изменяться в потоках
std::counting_semaphore<1> prepareSignal(0); // Семафор для синхронизации потоков

// Поток, подготавливающий данные
void prepareWork()
{
    myVec.insert(myVec.end(), {0, 1, 0, 3}); // Добавление данных в вектор
    std::cout << "Sender : Data prepared." << '\n';
    prepareSignal.release(); // Разрешение выполнения следующего потока
}

// Поток, ожидающий готовности данных
void completeWork()
{
    std::cout << "Waiter: Waiting for data." << '\n';
    prepareSignal.acquire(); // Ожидание сигнала о готовности данных
    myVec[2] = 2; // Изменение данных
    std::cout << "Waiter : Complete the work." << '\n'; 
    
    // Вывод финального состояния вектора
    for (auto i : myVec) std::cout << i << " ";
    std::cout << '\n';
}

int main()
{
    std::cout << '\n';

    std::thread t1(prepareWork);
    std::thread t2(completeWork);

    t1.join();
    t2.join();

    std::cout << '\n';
}