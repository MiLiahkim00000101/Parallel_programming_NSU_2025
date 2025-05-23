#include <iostream>     // Для ввода-вывода в консоль
#include <cmath>        // Для математических функций, таких как sin()
#include <chrono>       // Для измерения времени выполнения
#include <iomanip>      // Для форматированного вывода
#include <memory>       // Для умных указателей std::unique_ptr

#include "boost/program_options.hpp" // Библиотека для обработки аргументов командной строки
#include "openacc.h"                 // Поддержка OpenACC


#ifdef CUBLAS
    #include "cublas_v2.h"           // cuBLAS API (если используется)
#endif

int main(int argc, char const *argv[])
{
    // Упрощаем доступ к пространству имён библиотеки опций
    namespace opt = boost::program_options;

    // Описание доступных аргументов командной строки
    opt::options_description desc("Example");
    desc.add_options()
        ("nelements,n", opt::value<std::size_t>()->required(), // обязательный параметр — размер массива
                        "elements array")
        ("num_device,d", opt::value<int>()->default_value(0),  // номер GPU (по умолчанию 0)
                         "number gpu")
        ("help", "example sum sin [0..pi]")                     // вывод справки
    ;

    // Объект для хранения аргументов
    opt::variables_map vm;

    // Парсим и сохраняем аргументы
    opt::store(opt::parse_command_line(argc, argv, desc), vm);

    // Если указан флаг --help, выводим справку и выходим
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    // Проверяем, что обязательные параметры были переданы
    try {
        opt::notify(vm);
    } catch (const opt::required_option& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 2;
    }

    // Устанавливаем номер устройства GPU для OpenACC
    acc_set_device_num(vm["num_device"].as<int>(), acc_device_nvidia);

    #ifdef CUBLAS
        // Инициализация cuBLAS
        cublasStatus_t stat;
        cublasHandle_t handle;
        stat = cublasCreate(&handle);
        if (stat != CUBLAS_STATUS_SUCCESS) {
            std::cout << "CUBLAS initialization failed\n";
            std::cout << "NAME: " << cublasGetStatusName(stat) << '\n';
            std::cout << "DES: " << cublasGetStatusString(stat) << '\n';
            return 3;
        }
    #endif

    // Получаем размер массива из аргументов
    std::size_t array_size = vm["nelements"].as<std::size_t>();

    // Выделяем память под массив значений
    std::unique_ptr<double[]> array = std::make_unique<double[]>(array_size);

    // Указатель на данные
    double *array_point = array.get();

    // Создаем вектор из единиц
    std::vector<double> array_ones(array_size, 1);

    // Указатель на вектор из единиц
    double *array_ones_point = array_ones.data();

    // Константа Pi * 2
    double pi2 = 2 * 3.1415926535;

    // Переменная для хранения суммы
    double sum = 0;
    
    double time_sec{};

    // Область OpenACC, создающая массив на устройстве и копирующая туда значения
    #pragma acc data create(array_point[0:array_size]) copyin(pi2, array_size, array_ones_point[0:array_size]) copy(sum)
    {   
        // Засекаем начальное время для измерения производительности
        auto start_time = std::chrono::steady_clock::now();

        // Параллельное вычисление sin(pi * i / array_size) в каждом элементе массива
        std::size_t i{0};
        #pragma acc parallel loop private(i)
        for(i = 0; i < array_size; ++i){
            array_point[i] = sin(pi2 / array_size * i);
        }

        // Параллельная редукция — суммирование значений массива
        #ifndef CUBLAS
                #pragma acc parallel loop private(i) reduction(+:sum)
                for(i = 0; i < array_size; ++i){
                    sum += array_point[i] * array_ones_point[i];
                } 
        #endif  

        #ifdef CUBLAS
            /*
            Директива "#pragma acc host_data use_device(array_point)" в OpenACC сообщает компилятору, что внутри блока фигурных скобок array_point 
            должен быть заменён на указатель на массив в памяти устройства (GPU), а не на обычный указатель CPU.
            Это необходимо, потому что вызов cublasDasum — это низкоуровневый CUDA API, который работает с данными, уже находящимися на GPU.
            Передаю указатель на sum хоста.
            */
            #pragma acc host_data use_device(array_point, array_ones_point, sum) 
            {
                stat = cublasDdot(handle, array_size, array_point, 1, array_ones_point, 1, &sum);
                if (stat != CUBLAS_STATUS_SUCCESS) {
                std::cout << "cublasDasum failed\n";
                std::cout << "NAME: " << cublasGetStatusName(stat) << '\n';
                std::cout << "DES: " << cublasGetStatusString(stat) << '\n';
                }
            }  
            cublasDestroy(handle);
        #endif  
         // Засекаем финальное время
        auto elapsed = std::chrono::steady_clock::now() - start_time;
        auto time_microsec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        time_sec = static_cast<double>(time_microsec) / 1000000;
    }

    // Вывод результатов
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Duratioan programm: " << time_sec<< " seconds" << std::endl;

    std::cout << std::fixed << std::setprecision(16);
    std::cout << "sum = " << sum << std::endl;

    return 0;
} 