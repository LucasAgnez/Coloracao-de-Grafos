#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include "Vertice.hpp"
#include <time.h>
#include <iomanip>

class Grafo {
private:
	int n;
  int numero_cromatico;
	std::vector<Vertice*> vertices;
	std::vector<std::vector<Vertice*>> adjacentes;

  public:

	Grafo(int argc, char **arg);
	
  ~Grafo();

  Vertice* max_saturacao(std::set<Vertice*> s);

  void carrega_grafo(std::string nome_arquivo);

	void adiciona_aresta(int u, int v);

	void adiciona_vertice(Vertice *u);
 
	void colore_grafo();
	
	void imprime_lista();
	
	void imprime_vertices();

	void imprime_lista_colorida();
	
	bool eh_pseudografo();

	void calcula_saturacao();
};
#endif
