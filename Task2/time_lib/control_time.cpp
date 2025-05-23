#include "control_time.h"

double start_time;
double end_time;

double Start_Clock(){
    start_time =  std::chrono::duration_cast<std::chrono::duration<double>>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
    return start_time;
}
double Check_Clock(){
    end_time =  std::chrono::duration_cast<std::chrono::duration<double>>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
    return end_time - start_time;
}