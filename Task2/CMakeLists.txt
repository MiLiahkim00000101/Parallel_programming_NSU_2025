cmake_minimum_required(VERSION 3.10)

#set_property(CXX_STANDARD 17)
#set_property(CXX_STANDARD_REQUIRED 17)

add_library(watch_time_lib STATIC time_lib/control_time.cpp time_lib/control_time.h)
add_library(func_lib STATIC func_lib/integr.cpp func_lib/integr.h func_lib/mult_matr_vec.cpp func_lib/mult_matr_vec.h)
add_library(file_lib STATIC work_with_file_lib/file_manage.cpp work_with_file_lib/file_manage.h)

add_executable(main nain.cpp)

target_link_libraries(main watch_time_lib func_lib file_lib)
