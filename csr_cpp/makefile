
CXX := gcc
INCLUDE := /usr/local/include
CXXFLAGS := -pedantic -lstdc++ -I$(INCLUDE) -Wall -Werror
LIB := /usr/local/lib


clean:
	rm -f *.o

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

csr: CSR.h CSR.c++ RunSP.c++
	$(CXX) $(CXXFLAGS) CSR.c++ RunSP.c++ -o csr.o
