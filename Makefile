GCC = g++
GCC_FLAGS = -I include -std=c++17
PROGRAMA = grafos

$(PROGRAMA): Vertice.o Grafo.o main.o
	$(GCC) $(GCC_FLAGS) -o grafos *.o

Vertice.o: src/Vertice.cpp include/Vertice.hpp
	$(GCC) $(GCC_FLAGS) -c src/Vertice.cpp

Grafo.o: src/Grafo.cpp include/Grafo.hpp
	$(GCC) $(GCC_FLAGS) -c src/Grafo.cpp

main.o: src/main.cpp
	$(GCC) $(GCC_FLAGS) -c src/main.cpp

clean:
	rm *.o $(PROGRAMA)
