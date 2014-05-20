#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>
using namespace std;

//map visitados para verificar os nos visitados. Obs, o valor podia ser boolean ao invés de int;
map <int,int> visitados;
//map grafo com chave int e valor do tipo vector<> para armazenar mais de um valor na mesma chave;
map<int, vector<int> > grafo;
			
int cont,total_nos, fila[64];


int bFS ( int X, int T) 
{     
	//Poderia usar queue para usar como fila
	int inicio = 0, fim = 0, pivo, i;
    //Marco o nó de partida como visitado
	visitados[X] = 1;
	//Decremento cont, que estava com o total de nos
	cont--;
	//Jogo na fila na posição de fim=0, o valor do no de partida, e incremento fim
    fila[fim++] = X;	
	
	//Enquanto inicio for diferente de fim ele procura
    while (inicio != fim)
	{
		//pivo recebe o elemento da posiciao inicio, na primeira vez igual a 0, da fila;
		pivo = fila[inicio++];
		//printf("Pivo - %d fila[%d]=%d\nQtdVertAdj = %d\n", pivo, inicio, fila[inicio-1], arestas[pivo][0]);
		//printf("Pivo - %d fila[%d]=%d\nGrau = %d\nT = %d\nCont = %d\n\n", pivo, inicio, fila[inicio-1], visitados[pivo], T, cont);
		//printf("Tamanho: %d", grafo[pivo].size());
		
		/*Se o valor de visitados na posição do pivo for maior que TTL então sai. 
		Obs: Está T+1 eu comecei com 1, devia ter começado com 0 e verivicado se visitados[] == -1 para poder visitado  */
		if( visitados[pivo] == T+1 )
			return 1;
		
		//Percorro a quantidade de elementos que o pivo tem no vector<>;
        for (i = 0; i < grafo[pivo].size(); i++) 
		{   
			//Se ele não foi visitado então...
			if ( visitados.count(grafo[pivo][i]) == 0) 
			{      
				//Na posição fim, que se for a primeira vez é = 1, da fila grava o novo nó que será percorrido
				fila[fim++] = grafo[pivo][i];
				//visitados[] na posição do no visitado = 1 + o valor de visitados[] na posição do pivo
                visitados[grafo[pivo][i]] += 1 + visitados[pivo];
				//Decrementa cont;
				cont--;
			}														
			
		}
							
	}
	return 0;
	
}


// ######Tentar fazer dfs com map##########
void dfs( long long int X, long long int T, long long int ant )
{
	if( T == -1 )
		return;
		
	if( visitados[X]==0 )
	{
		cont--;
		visitados[X] = 1;
	}
			
	for(int i=1;i<=arestas[X][0];i++)
	{
		if( ant == arestas[X][i] )
			continue;
		dfs(arestas[X][i], T-1, X);
	}	
	
}

int main()
{
	int N, A, B, X, T,i,caso=0;
	int aux=0;	
		
	scanf("%d", &N);
	
	while( N!=0 )
	{					
				
		total_nos=0;
		//Tira todos os elementos de grafo
		grafo.clear();
		//printf("Cria Grafo\n");
		for(i=0;i<N;i++)
		{
			scanf("%d %d ", &A, &B);
			//printf(" A = %d B = %d\nTem A = %d Tem B = %d\n\n", A, B, grafo.count(A), grafo.count(B) );
			if( grafo.count(A) == 0 ) //grafo.count(A) volta a quantidade de elementos com o valor de A se for == 0 quer dizer que não existe
				total_nos++;
			grafo[A].push_back(B); //Insere na posição da Chave de valor A, no vector o valor que ele esta ligado: map<int, vector<int> >
			
			if( grafo.count(B) == 0 )//grafo.count(B) volta a quantidade de elementos com o valor de B se for == 0 quer dizer que não existe
				total_nos++;
			grafo[B].push_back(A); //Insere na posição da Chave de valor A, no vector o valor que ele esta ligado: map<int, vector<int> >
									
		}				
		//printf("Total Nos: %d\n", total_nos);
		
		/*
		//Verificar os elemtos da lista
		//Criar um const_iterator para percorrer o map, pode ser o interator tbm, mas recomenda-se que se for somente leitura compensa o const_iterator
		map<int,vector<int> >::const_iterator itr; //O mesmo tipo do elemento a ser percorrido
        //o iterator = o primeiro elento da lista; enquanto ele for diferente do ultimo ele entre no loop
		for(itr = grafo.begin(); itr != grafo.end(); ++itr){
			//.first é o elemnto Chave
			printf("\n%d -> ", (*itr).first);
			//Como o .second é um elemento vector<>, precisa-se criar um for para percorrer todos os elementos desse vector, para isso usa-se .size()
			for (int j = 0; j <(*itr).second.size(); ++j)
			{				 
				 printf("%d - ", (*itr).second[j]);
			}
        }
		*/
				
		scanf("%d %d", &X, &T);
		
		//printf("X = %d T = %d Nos = %d diff = %d\n", X, T, total_nos, (abs(X)+abs(T)) );
		
		while( (abs(X)+abs(T)) != 0 )
		{
			
			caso++;
			cont = total_nos;
			visitados.clear(); //Limpa o map visitados
			//dfs(X,T, 0);
			if( T <= 0 )
				cont = total_nos - 1; //Caso T seja <= 0, retornar Total_Nos - 1
			else	
				aux=bFS(X,T); //Caso contrario percorre os caminhos
				
			printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n", caso, cont, X, T);						
			scanf("%d %d", &X, &T);
			
		}
		
		scanf("%d", &N);		
				
	}
	
	
	return 0;
}
