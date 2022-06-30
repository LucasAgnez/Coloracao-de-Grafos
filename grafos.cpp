#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <sstream>

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
 
	Grafo(string nome_arquivo){
		carrega_grafo(nome_arquivo);
	}
	~Grafo() { 
		adjacentes.clear(); 
		vertices.clear();
	}
	void carrega_grafo(string nome_arquivo);

	void adiciona_aresta(Vertice *u, Vertice *v);

	void adiciona_vertice(Vertice *u);
 
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
	cout << "\tAresta Adicionada: (" << u->indice << ", " << v->indice << ")"<< endl;
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

void Grafo::adiciona_vertice(Vertice *u){
	if (u->indice >= n){
		cout << "\tERRO: \t Indice do vertice fora dos limites (" << u->indice  << ")" << "\tLimite: " << n-1 << endl;
		return;
	}
	vertices[u->indice] = u;
	cout << "\tVértice Adicionado: (" << u->indice << ")"<< endl;
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
	cout << "a" << endl;
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

void Grafo::carrega_grafo(string nome_arquivo){
	fstream arquivo;	
	arquivo.open(nome_arquivo, ios::in);
	if(arquivo.is_open()){
		string linha;
		string lixo;
		int num_vert;
		int id_vert1;
		int id_vert2;		
		stringstream stream;
		while(getline(arquivo, linha)){
			if (linha.size() == 0) {
      			continue;
      		}
      		if(linha.find("c")!= string::npos){
      			continue;
      		}
      		if(linha.find("p")!= string::npos){
      			stream << linha;
      			stream >> lixo;
      			stream >> lixo;
      			stream >> num_vert;
      			stream >> lixo;
      			n = num_vert
      			vertices.resize(n);
				adjacentes.resize(n, vector<Vertice*>());
      			for(int i = 0; i < num_vert; i++){
      				Vertice vert(i);
      				adiciona_vertice(&vert);
      			}
      		}
      		if(linha.find("e")!= string::npos){
      			stream << linha;
      			stream >> lixo;
      			stream >> id_vert1;
      			stream >> id_vert2;
      			id_vert1--;
      			id_vert2--;
      			adiciona_aresta(vertices[id_vert1], vertices[id_vert2]);
      		}

		}
	}
	arquivo.close();
}

int main(int argc, char** argv){
	Grafo G("fpsol2.i.1.col");
	return 1;
}
