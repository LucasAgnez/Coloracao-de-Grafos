#ifndef VERTICE_HPP
#define VERTICE_HPP

#include<vector>

class Vertice {
public:
	int grau_sat; // numero de cores usadas pelos seus vizinhos
	int grau;
	int indice;
	int cor;

	Vertice(int i);
};
#endif