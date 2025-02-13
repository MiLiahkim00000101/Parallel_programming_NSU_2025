DIR = build
CXX_FLAGS = -std=c++17 -Wall

ifdef FLOAT
	CXX_FLAGS += -DFLOATVALUESIN
endif
all: 
	rm -r -f $(DIR)
	mkdir $(DIR)

	cd $(DIR) && g++ ../main.cpp -o main $(CXX_FLAGS)

FLOAT:
	make FLOAT=1
