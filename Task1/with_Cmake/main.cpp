#include <iostream>
#include <cmath>
#include <vector>

#ifdef FLOATVALUESIN
    float temp = 0;
    float temp_sin_val;
    std::vector<float> sin_values; 
    float res = 0;
#else
    double temp = 0;
    double temp_sin_val;
    std::vector<double> sin_values;
    double res = 0;
#endif

size_t size_of_temp = sizeof(temp);

int main(){
    
    for (int i = 0; i < 10000000; ++i){

        temp_sin_val = sin(temp);

        res += temp_sin_val;
        sin_values.push_back(temp_sin_val);
        temp += 2 * M_PI / 10000000; // здесь за такое огромное количество итераций если выбран
        // float накапливается большая ошибка из игнорирования малых значений после запятой
        //(мне кажется, что ошибка накапливается за счет игнорирования значений
        // после 10 знака(после запятой) до того, как мы получили целую часть и после 5-7 после). 
        // Из-за устройства чисел с плавающей запятой в компьютерах, чем дальше от нуля число 
        // тем менее точно оно будет определяться.
        // Здесь вышла именно такая ситуация, ведь отдаляясь от нуля значение temp начинает меняться
        // все медленнее и медленнее, в итоге мы даже не можем пройти весь период((((
        //std::cout << i << ", val: " << temp_sin_val << std::endl;

        // В случае с float здесь точность до 3 знаков после запятой ну то бишь почти ноль
    }

    std::cout << res << std::endl;

    return 0;

}