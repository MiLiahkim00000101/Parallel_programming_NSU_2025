#include "file_manage.h"

std::ofstream file_vec_matr_mult_20000;
std::ofstream file_vec_matr_mult_40000;
std::ofstream file_integr_40000000;

void openFiles() {
    file_vec_matr_mult_20000.open("res_mult_20000.csv", std::ios::app);
    file_vec_matr_mult_40000.open("res_mult_40000.csv", std::ios::app);
    file_integr_40000000.open("res_integr_40000000.csv", std::ios::app);

    if (!file_vec_matr_mult_20000.is_open())
        std::cerr << "Ошибка открытия res_mult_20000.csv!" << std::endl;
    if (!file_vec_matr_mult_40000.is_open())
        std::cerr << "Ошибка открытия res_mult_40000.csv!" << std::endl;
    if (!file_integr_40000000.is_open())
        std::cerr << "Ошибка открытия res_integr_40000000.csv!" << std::endl;
}

void closeFiles() {
    file_vec_matr_mult_20000.close();
    file_vec_matr_mult_40000.close();
    file_integr_40000000.close();
}

void clearFiles() {
    std::ofstream clearFile;

    clearFile.open("res_mult_20000.csv", std::ios::trunc);
    clearFile.close();

    clearFile.open("res_mult_40000.csv", std::ios::trunc);
    clearFile.close();

    clearFile.open("res_integr_40000000.csv", std::ios::trunc);
    clearFile.close();

    std::cout << "Файлы очищены." << std::endl;
}
