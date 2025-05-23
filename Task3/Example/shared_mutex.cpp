#include <iostream>
#include <map>
#include <thread>
#include <shared_mutex>
#include <string>
#include <chrono>

// Телефонный справочник (общий ресурс)
std::map<std::string, int> telebook{
    {"Scott", 1}, {"Ritchie", 9}, {"Dijkstra", 22}};

std::shared_mutex telebookMutex; // Общий мьютекс для потоков чтения и записи

// Функция добавления записи в справочник (требует эксклюзивной блокировки)
void addTeleBook(const std::string &name, int number)
{
    std::lock_guard<std::shared_mutex> writeLock(telebookMutex);
    std::cout << "STARTING UPDATE " << name << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Имитация задержки
    telebook[name] = number;
    std::cout << "... ENDING UPDATE " << name << std::endl;
}

// Функция поиска номера в справочнике (разделяемая блокировка)
void printNumber(const std::string &name)
{
    std::shared_lock<std::shared_mutex> readerLock(telebookMutex);
    auto searchEntry = telebook.find(name);
    if (searchEntry != telebook.end())
    {
        std::cout << searchEntry->first << ": " << searchEntry->second << std::endl;
    }
    else
    {
        std::cout << name << " not found!" << std::endl;
    }
}

int main()
{
    // Потоки чтения
    std::thread reader1([]{ printNumber("Scott"); });
    std::thread reader2([]{ printNumber("Ritchie"); });
    
    // Потоки записи
    std::thread writer1([]{ addTeleBook("Scott", 1968); });
    std::thread writer2([]{ addTeleBook("Bjarne", 1965); });
    
    // Дополнительные потоки чтения
    std::thread reader3([]{ printNumber("Dijkstra"); });
    std::thread reader4([]{ printNumber("Scott"); });
    std::thread reader5([]{ printNumber("Bjarne"); });
    
    // Ожидание завершения всех потоков
    reader1.join();
    reader2.join();
    reader3.join();
    reader4.join();
    reader5.join();
    writer1.join();
    writer2.join();
    
    // Вывод обновленного справочника
    std::cout << "\nThe new telephone book:" << std::endl;
    for (const auto &entry : telebook)
    {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
}