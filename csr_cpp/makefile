CXX := gcc
INCLUDE := /usr/local/include
CXXFLAGS := -pedantic -lstdc++ -I$(INCLUDE) -Wall -Werror -std=c++11
LIB := /usr/local/lib

clean:
	rm -f *.o

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

prog: main.cpp CSR.cpp Worklist.cpp SSSP.cpp
	$(CXX) $(CXXFLAGS) main.cpp CSR.cpp Worklist.cpp SSSP.cpp -o prog