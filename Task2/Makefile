

ifndef REDUCED
	CXX_FLAGS_m =  -m -s40000
	CXX_FLAGS_a =  -a -s40000
	ifdef PARINIT
		CXX_FLAGS_a  = -a -s40000 -i
		CXX_FLAGS_m  = -m -s40000 -i
	endif
else
	CXX_FLAGS_m =  -m -s20000
	CXX_FLAGS_a =  -a -s20000
	ifdef PARINIT
		CXX_FLAGS_a  = -a -s20000 -i
		CXX_FLAGS_m  = -m -s20000 -i
	endif
endif

full:
	lscpu
	@echo ------------------------------------------------------------------------------------
	cat /sys/devices/virtual/dmi/id/product_name
	@echo -----------------------------------------------------------------------------------
	numactl --hardware
	@echo ------------------------------------------------------------------------------------
	cat /etc/os-release
	@echo ------------------------------------------------------------------------------------
	./main -N1 ${CXX_FLAGS_m}
	./main -N2 ${CXX_FLAGS_a}
	./main -N4 ${CXX_FLAGS_a}
	./main -N7 ${CXX_FLAGS_a}
	./main -N8 ${CXX_FLAGS_a}
	./main -N16 ${CXX_FLAGS_a}
	./main -N20 ${CXX_FLAGS_a}
	./main -N40 ${CXX_FLAGS_a}


