# Description and tutorial to use programs

Task 1:

This program counts sum of sinus period values with step 1/10^7. 

In this task was implemented two variants of program building using Makefile and CMake.
Also I needed to implement option to change type of variables I use to count sum.(double is default)

This is project which you can build using instruction:

    make
    cd build && ./main


If you want to change double on float:

insead of:

    make

write:

    make FLOAT


Also you can see wrong answer if you use float. This behavior I explained in my both directories in files "main.cpp".

RESULTS:
    Using double: -0.000779278
    Using float: -644532
