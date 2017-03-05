CXX := g++
INCLUDE := /usr/local/include
#CXXFLAGS := -pedantic -lstdc++ -I$(INCLUDE) -Wall -Werror -std=c++11
CXXFLAGS := -std=c++11
LIB := /usr/local/lib

clean:
	rm -f *.o

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

chaotic: chaoticExperiment.cpp CSR.cpp Worklist.cpp SSSP.cpp Parser.cpp
	$(CXX) $(CXXFLAGS) chaoticExperiment.cpp CSR.cpp Worklist.cpp SSSP.cpp Parser.cpp -o chaotic.o

dijkstra: dijkstraExperiment.cpp CSR.cpp Worklist.cpp SSSP.cpp Parser.cpp
	$(CXX) $(CXXFLAGS) dijkstraExperiment.cpp CSR.cpp Worklist.cpp SSSP.cpp Parser.cpp -o dijkstra.o

delta: deltaStepExperiment.cpp CSR.cpp Worklist.cpp SSSP.cpp Parser.cpp
	$(CXX) $(CXXFLAGS) deltaStepExperiment.cpp CSR.cpp Worklist.cpp SSSP.cpp Parser.cpp -o delta.o

deltaOptimal: deltaOptimalExperiment.cpp CSR.cpp Worklist.cpp SSSP.cpp Parser.cpp
	$(CXX) $(CXXFLAGS) deltaOptimalExperiment.cpp CSR.cpp Worklist.cpp SSSP.cpp Parser.cpp -o deltaOptimal.o

degree: getLargestOutDegree.cpp CSR.cpp Parser.cpp
	$(CXX) $(CXXFLAGS) getLargestOutDegree.cpp CSR.cpp Parser.cpp -o degree.o
