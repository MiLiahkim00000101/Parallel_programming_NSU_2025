all:
	
	g++ hello_world.cpp -fopenmp -o hello_world
	g++ hello_world_with_def_num_thr.cpp -fopenmp -o hello_world_with_def_num_thr
	g++ list_of_threads.cpp -fopenmp -o list_of_threads -fpermissive

	./hello_world
	./hello_world_with_def_num_thr
	./list_of_threads && ps -eLo pid,tid,psr,args | grep hello

	