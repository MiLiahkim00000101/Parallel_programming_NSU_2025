#ifndef ___WRITEFILE___
#define ___WRITEFILE___

#include <string>
#include <fstream>
#include <iostream>

extern std::ofstream file_vec_matr_mult_20000;
extern std::ofstream file_vec_matr_mult_40000;
extern std::ofstream file_integr_40000000;

void openFiles();
void closeFiles();
void clearFiles();

#endif