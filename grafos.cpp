#include <iostream>
#include <set>
#include <vector>

using namespace std;
 
class Vertice {
public:
	int grau_sat; // numero de cores usadas pelos seus vizinhos
	int grau;
	int indice;
	int cor;

	Vertice(int i){
		indice = i;
		grau_sat = 0;
		grau = 0;
		cor = -1;
	}
};

Vertice* max_saturacao(set<Vertice*> s) {
	set<Vertice*>::iterator it = s.begin();
	Vertice* u = *it;
	for(auto v : s){

		if(u->grau_sat > v->grau_sat){}
		else if(u->grau_sat < v->grau_sat){
			Vertice* u = v;
		}
		else if (u->grau_sat == v->grau_sat){
			if(u->grau < v->grau){
				Vertice* u = v;
			}
			else if(u->grau > v->grau){}
			else if (u->grau == v->grau){
				if(u->indice > v->indice){
				}
				else if(u->indice < v->indice){
					Vertice* u = v;
				}
			}
		}
	}
	return u;
};

class Grafo {
public:
	int n;
	vector<Vertice*> vertices;
	vector<vector<Vertice*>> adjacentes;
 
	Grafo(int n_vertices){
		n = n_vertices;
		vertices.resize(n);
		adjacentes.resize(n, vector<Vertice*>());
	}
	~Grafo() { 
		adjacentes.clear(); 
		vertices.clear();
	}
 
	void adiciona_aresta(Vertice *u, Vertice *v);
 
	void colore_grafo();
	
	void imprime_lista();
	
	void imprime_vertices();

	void imprime_lista_colorida();
	
	bool eh_pseudografo();

	void calcula_saturacao();
};
 
void Grafo::adiciona_aresta(Vertice *u, Vertice *v){
	if (u->indice >= n){
		cout << "\tERRO: \t Indice do primeiro vertice fora dos limites (" << u->indice  << ")" << "\tLimite: " << n-1 << endl;
		return;
	}
	if (v->indice >= n){
		cout << "\tERRO: \t Indice do segundo vertice fora dos limites (" << v->indice  << ")" << "\tLimite: " << n-1 << endl;
		return;
	}
	vertices[u->indice] = u;
	vertices[v->indice] = v;
	cout << "\tAdicionado: (" << u->indice << ", " << v->indice << ")"<< endl;
	if(u == v){
		adjacentes[u->indice].push_back(v);
		u->grau++;
		return;
	}
	adjacentes[u->indice].push_back(v);
	u->grau++;
	adjacentes[v->indice].push_back(u);
	v->grau++;
}
 
bool Grafo::eh_pseudografo(){
	for(Vertice* i: vertices){
		for (Vertice *v : adjacentes[i->indice]){
			if (i->indice == (v->indice)){
				cout << "\tImpossível colorir, é Pseudografo!" << endl;
				return true;
			}
		}
	}
	return false;
}

void Grafo::calcula_saturacao(){
	for(Vertice* i : vertices){
	    set<int> cores;
		int grau_sat_de_i = 0;
		for (Vertice *v : adjacentes[i->indice]){ //checa as cores adjacentes a cada vertice do grafo
			if(v->cor != -1){
				cores.insert(v->cor); 
			}
		}
		grau_sat_de_i = cores.size();
		i->grau_sat=grau_sat_de_i;
	}
}

void Grafo::colore_grafo(){
	if(!eh_pseudografo()){
		while(true){
			calcula_saturacao();
			set<Vertice*> fila;
			for(Vertice* v : vertices){ //adiciona os vertices não-coloridos a fila
				if(v->cor == -1){
					fila.insert(v);
				}
			}
			
			if(fila.empty()){ //se a fila está vazia, a coloração está completa
				break;
			}
			Vertice *maior_sat = max_saturacao(fila);
			vector<int> cores(n, 0);
			for(Vertice* u : adjacentes[maior_sat->indice]){ //checa as cores adjacentes ao vertice de maior saturação da fila
				if(u->cor != -1){
					cores[u->cor] = 1;
				}
			}
			for(int c = n-1; c>=0; c--){ //colore o vertice com a menor cor disponível
				if(cores[c]==0){
					maior_sat->cor = c;
				}
			}
		}
	imprime_vertices();
	imprime_lista_colorida();
	}
	
}

void Grafo::imprime_lista(){
	cout << "----------------------------------------------------------------" << endl << "\tLISTA DE ADJACENCIA: " << endl;
	for(Vertice* i : vertices){
		cout <<  "v[" << i->indice << "] = ";
		for (Vertice *v : adjacentes[i->indice]){
			cout << v->indice << ", ";
		}
		cout << endl;
	}
}

void Grafo::imprime_vertices(){
    set<int> cores;
    int total_cores = 0;
	cout << "----------------------------------------------------------------" << endl << "\tVERTICES: " << endl;
	for(Vertice* v : vertices){
	    cores.insert(v->cor);
		cout <<  "\tIndice: " << v->indice << ",\t Sat: " << v->grau_sat << ",\t Grau:" << v->grau << ",\t Cor:" << v->cor << endl;
	}
    total_cores = cores.size();
	cout << "\tTOTAL DE CORES: " << total_cores << endl;
}

void Grafo::imprime_lista_colorida(){
	cout << "----------------------------------------------------------------" << endl << "\tLISTA ADJACENCIA COLORIDA: " << endl;
	for(Vertice* i : vertices){
		cout  << "\t" << i->indice << "(" << i->cor << ") : ";
		for (Vertice *v : adjacentes[i->indice]){
			cout << "\t" << v->indice << "(" << v->cor << ")" << ", ";
		}
		cout << endl;
	}
}
 
int main(){
	cout << "##################################################################" << endl;
    cout << "GRAFO 0:" << endl;
	Vertice v0(0);
	Vertice v1(1);
	Vertice v2(2);
	Vertice v3(3);
	Vertice v4(4);
	Vertice v5(5);
	Vertice v6(6);
	Grafo G(7);
	G.adiciona_aresta(&v0, &v1);
	G.adiciona_aresta(&v0, &v2);
	G.adiciona_aresta(&v0, &v3);
	G.adiciona_aresta(&v0, &v4);
	G.adiciona_aresta(&v0, &v5);
	G.adiciona_aresta(&v0, &v6);
	G.adiciona_aresta(&v1, &v2);
	G.adiciona_aresta(&v1, &v3);
	G.adiciona_aresta(&v1, &v4);
	G.adiciona_aresta(&v1, &v5);
	G.adiciona_aresta(&v1, &v6);
	G.adiciona_aresta(&v2, &v3);
	G.adiciona_aresta(&v2, &v4);
	G.adiciona_aresta(&v2, &v5);
	G.adiciona_aresta(&v2, &v6);
	G.adiciona_aresta(&v3, &v4);
	G.adiciona_aresta(&v3, &v5);
	G.adiciona_aresta(&v3, &v6);
	G.adiciona_aresta(&v4, &v5);
	G.adiciona_aresta(&v4, &v6);
	G.adiciona_aresta(&v5, &v6);
	G.colore_grafo();
	cout << endl << "##################################################################" << endl;
	cout << "GRAFO 1:" << endl;

    Vertice G1v0(0);
	Vertice G1v1(1);
	Vertice G1v2(2);
	Vertice G1v3(3);
	Vertice G1v4(4);
	Vertice G1v5(5);
	Vertice G1v6(6);
	Vertice G1v7(7);
	Vertice G1v8(8);
	Grafo G1(9);
	G1.adiciona_aresta(&G1v0, &G1v3);
	G1.adiciona_aresta(&G1v0, &G1v4);
	G1.adiciona_aresta(&G1v0, &G1v7);
	G1.adiciona_aresta(&G1v1, &G1v2);
	G1.adiciona_aresta(&G1v1, &G1v6);
	G1.adiciona_aresta(&G1v2, &G1v6);
	G1.adiciona_aresta(&G1v3, &G1v5);
	G1.adiciona_aresta(&G1v3, &G1v4);
	G1.adiciona_aresta(&G1v3, &G1v8);
	G1.adiciona_aresta(&G1v4, &G1v8);
	G1.adiciona_aresta(&G1v5, &G1v7);
	G1.adiciona_aresta(&G1v6, &G1v7);
	G1.colore_grafo();
	
	cout << endl << "##################################################################" << endl;
	cout << "GRAFO 2:" << endl;
	Vertice G2v0(0);
	Vertice G2v1(1);
	Vertice G2v2(2);
	Vertice G2v3(3);
	Vertice G2v4(4);
	Vertice G2v5(5);
	Vertice G2v6(6);
	Vertice G2v7(7);
	Vertice G2v8(8);
	Grafo G2(9);
	G2.adiciona_aresta(&G2v0, &G2v1);
	G2.adiciona_aresta(&G2v0, &G2v5);
	G2.adiciona_aresta(&G2v2, &G2v3);
	G2.adiciona_aresta(&G2v2, &G2v5);
	G2.adiciona_aresta(&G2v2, &G2v7);
	G2.adiciona_aresta(&G2v4, &G2v1);
	G2.adiciona_aresta(&G2v6, &G2v5);
	G2.adiciona_aresta(&G2v6, &G2v7);
	G2.adiciona_aresta(&G2v8, &G2v1);
	G2.colore_grafo();


	return 1;
}