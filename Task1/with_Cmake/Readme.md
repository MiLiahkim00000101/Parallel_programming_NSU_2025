# Description and tutorial to use programs

Task 1:

This program counts sum of sinus period values with step 1/10^7. 

In this task was implemented two variants of program building using Makefile and CMake.
Also I needed to implement option to change type of variables I use to count sum.(double is default)
There is three directories in this task.

First is test:
    It was just helped me code while debugging and understanding of my code is correct.

Second is with_CMake:
    This is project which you can build using instruction:
        cmake -S. -B build
        cmake --build build
        cd build && ./main

    If you want to change double on float:
        insead of: cmake -S. -B build
        write: cmake -S. -B build -DFLOAT=ON

Third is with_Make:
    This is project which you can build using instruction:
        make
        cd build && ./main

    If you want to change double on float:
        insead of: make
        write: make FLOAT


Also you can see wrong answer if you use float. This behavior I explained in my both directories in files "main.cpp".