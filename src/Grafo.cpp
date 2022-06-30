#include "Grafo.hpp"

using namespace std;

Grafo::Grafo(int argc, char **arg){
  if(argc != 2){
    cout << "USO: ./grafos <nome_do_arquivo>" << endl;
  }
  string nome_arquivo;
  stringstream s;
  s << arg[1];
  s >> nome_arquivo;
  nome_arquivo = "data/" + nome_arquivo;
  carrega_grafo(nome_arquivo);
  //imprime_lista();
  colore_grafo();
}
Grafo::~Grafo() {
  adjacentes.clear(); 
  vertices.clear();
}

Vertice* Grafo::max_saturacao(set<Vertice*> s) {
	set<Vertice*>::iterator it = s.begin();
	Vertice* u = *it;
	for(auto v : s){
		if(u->grau_sat > v->grau_sat){}
		else if(u->grau_sat < v->grau_sat){
			u = v;
		}
		else if (u->grau_sat == v->grau_sat){
			if(u->grau < v->grau){
				u = v;
			}
			else if(u->grau > v->grau){}
			else if (u->grau == v->grau){
				if(u->indice > v->indice){
				}
				else if(u->indice < v->indice){
					u = v;
				}
      }
		}
	}
	return u;
};

void Grafo::adiciona_aresta(int u, int v){
	if (u >= n){
		cout << "\tERRO: \t Indice do primeiro vertice fora dos limites (" << u  << ")" << "\tLimite: " << n-1 << endl;
		return;
	}
	if (v >= n){
		cout << "\tERRO: \t Indice do segundo vertice fora dos limites (" << v  << ")" << "\tLimite: " << n-1 << endl;
		return;
  }
	// cout << "\tAresta Adicionada: (" << u << ", " << v << ")"<< endl;
	if(u == v){
		adjacentes[u].push_back(vertices[v]);
		vertices[u]->grau++;
		return;
	}
	adjacentes[u].push_back(vertices[v]);
	vertices[u]->grau++;
	adjacentes[v].push_back(vertices[u]);
	vertices[v]->grau++;
}

void Grafo::adiciona_vertice(Vertice *u){
	if (u->indice >= n){
		cout << "\tERRO: \t Indice do vertice fora dos limites (" << u->indice  << ")" << "\tLimite: " << n-1 << endl;
		return;
	}
	vertices[u->indice] = u;
	//cout << "\tVértice Adicionado: (" << u->indice << ")"<< endl;
}
 
bool Grafo::eh_pseudografo(){
	for(Vertice* i: vertices){
		for (Vertice *v : adjacentes[i->indice]){
			if (i->indice == (v->indice)){
				cout << "\tImpossível colorir, é Pseudografo!" << i->indice << v->indice << endl;
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
  time_t start, end;
  time(&start);
  ios_base::sync_with_stdio(false);
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
    time(&end);
	//imprime_lista_colorida();
    imprime_vertices();
    double time_taken = double(end - start);
    cout << "Tempo para colorir o grafo: " << fixed
         << time_taken << setprecision(7);
    cout << " seg " << endl;
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
    numero_cromatico = 0;
	cout << "----------------------------------------------------------------" << endl << "\tVERTICES: " << endl;
	for(Vertice* v : vertices){
	    cores.insert(v->cor);
		cout <<  "\tIndice: " << v->indice << ",\t Sat: " << v->grau_sat << ",\t Grau:" << v->grau << ",\t Cor:" << v->cor << endl;
	}
    numero_cromatico = cores.size();
	cout << "\tTOTAL DE CORES: " << numero_cromatico << endl;
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
	ifstream arquivo(nome_arquivo);	
  if (!arquivo) {
    cerr << "Arquivo não pode ser aberto!" << endl;
    exit(-1);
  }
  string linha;
  string lixo;
  int num_vert;
  int id_vert1;
  int id_vert2;		
  while(getline(arquivo, linha)){
    if (linha.size() == 0) {
      continue;
    }
    if(linha.find("c")!= string::npos){
      continue;
    }
    if(linha.find("p")!= string::npos){
      stringstream stream(linha);
      stream >> lixo;
      stream >> lixo;
      stream >> num_vert;
      stream >> lixo;
      n = num_vert;
      vertices.resize(n);
      adjacentes.resize(n, vector<Vertice*>());
      for(int i = 0; i < num_vert; i++){
        Vertice *a = new Vertice(i);
        adiciona_vertice(a);
      }
      continue;
    }
    if(linha.find("e")!= string::npos){
      stringstream stream(linha);
      stream >> lixo;
      stream >> id_vert1;
      stream >> id_vert2;
      id_vert1 = id_vert1-1;
      id_vert2 = id_vert2-1;
      adiciona_aresta(id_vert1, id_vert2);
    }
	}
	arquivo.close();
}
