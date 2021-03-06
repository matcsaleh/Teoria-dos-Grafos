#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAXVERTICES 100
#define MAXARESTAS  1000


typedef struct{
      int n;             //número de vértices do grafo
      int e;             //número de arestas do grafo
      int MAdj[MAXVERTICES][MAXVERTICES];
      int ultimo;       // indice do ultimo vertice inserido
      int cor[MAXVERTICES];
      int pi[MAXVERTICES];
      int q[MAXVERTICES];
	  int d[MAXVERTICES];
	  int f[MAXVERTICES];
	  int comp; //componentes
}TGrafo;
typedef struct{
	
	
	int pred;	
}Vertices;

void inicializa(TGrafo *grafo)
{
	 int i;
     grafo->n = 0;
     grafo->e = 0;
     grafo->ultimo = 0;
    

}

void insereVertice (TGrafo *grafo)
{
      int i;
 
      for (i = 0; i <= grafo->n; i++){
         grafo->MAdj[grafo->n][i] = 0;
         grafo->MAdj[i][grafo->n] = 0;
      }
      grafo->n++;
      grafo->ultimo++;    
}

void imprimeGrafo (TGrafo grafo)
{
     int i,j;
 
      for (i = 0; i < grafo.n; i++)
       {
        printf("\n");
        for (j = 0; j < grafo.n; j++)
         printf("%d\t",grafo.MAdj[i][j]);
       }  
		printf("Vertice: %i Aresta: %i",grafo.n,grafo.e);
}

void insereAresta (TGrafo *grafo, int a, int b) 
{
      if (grafo->MAdj[a][b]==0) {
         if (a != b) {
            grafo->e++;
            grafo->MAdj[a][b]  = 1;
            grafo->MAdj[b][a]  = 1;
         }
      }   

}
void aleatorio(TGrafo *grafo, int n)
{
int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i!=j){// se o vertice não for igual ele seta valores aleatorios na matriz
			
				if(rand()%100 > 50)
				{
					grafo->MAdj[i][j] = 1;
					grafo->MAdj[j][i] = 1;
		    	}
				else
				{
					grafo->MAdj[i][j] = 0;
					grafo->MAdj[j][i] = 0;	
				}
			
			grafo->e++;
		}
		}
	}
	
}
void imprimeMenu()
{
     printf("\n\n\t1 - Inserir Vertice");
     printf("\n\t2 - Inserir Aresta");
     printf("\n\t3 - Verificar Euleriano");
     printf("\n\t4 - Grafo completo ");
     printf("\n\t5 - Completar Grafo ");
     printf("\n\t6 - Grafo arvore ");
     printf("\n\t7 - Vertives Pendentes ");
     printf("\n\t99 - Gerar grafo Aleatório ");
     printf("\n\t--------------------");
     printf("\n\t8 - Busca em Largura ");
     printf("\n\t9 - Busca em Profundidade ");
     printf("\n\t10 - Numero de Componentes ");
     printf("\n\t11 - Algoritmo de Dijkstra ");
     printf("\n\t0 - Sair");
     printf("\n\tOpcao -> ");
    
}

int grau(TGrafo grafo, int vertice)
{
    int i, cont=0;
    for(i=0; i<grafo.n; i++)
      cont += grafo.MAdj[vertice][i];
      
    return cont;  
    
}

int euleriano(TGrafo grafo)
{
    int i;
    for (i=0; i<grafo.n; i++)
     if (grau(grafo,i) % 2 != 0)
       return 0;
       
    return 1;
}

int grafoCompleto(TGrafo grafo)
{
	
	int i,j;
	int aux = 0;
	for(i=0;i<grafo.n;i++){
			for(j=0;j<grafo.n;j++){
				aux =aux + grafo.MAdj[i][j];
			}	
	}
	if(aux == (grafo.n * (grafo.n-1))){
			return 1;	
	}
	return 0;
}
void completaGrafo(TGrafo *grafo, int n)
{
int i,j;
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(grafo->MAdj[i][j] == 0 && i != j ){
				grafo->MAdj[i][j] = 1;
				grafo->MAdj[j][i] = 1;
				grafo->e ++;
			}
		}
	}
}
	
int grafoArvore(TGrafo grafo)
{
	
	if(grafo.e == (grafo.n-1))
	{
		return 1;
	}
	return 0;		
}	
int verticesPendentes(TGrafo grafo)
{
int i,j,aux = 0;
	for(i=0;i<grafo.n;i++)
	{
		for(j=0;j<grafo.n;j++)
		{
			aux = aux +	grafo.MAdj[i][j];
		}
		if(aux == 1)
		{
			return 1;
		}
	}
return 0;
}
void buscaProfundidade(TGrafo grafo)
{
int i;
int time = 0;


	for(i=0;i<=grafo.n;i++)
	{
		if(grafo.cor != 1)
		{
			printf("Chegou aqui1");
			getch();
			grafo.comp++;
			visit(&grafo,i,&time);
		}
    }

}
void visit(TGrafo *grafo, int vertice, int *time)
{
	printf("Chegou aqui2");
	getch();
	int i;
	grafo->cor[vertice] = 1;
	*time++;
	grafo->d[vertice] = *time; 
	
	for(i=0;i<=grafo->n;i++)
	{
		//printf("chegou aqui3");
		if(grafo->MAdj[vertice][i] == 1 && grafo->cor[vertice] != 1)
		{
			printf("chegou aqui4");
			getch();
			visit(grafo,i,time);
		}	
		
		
	}
	grafo->f[vertice] = *time;
	*time++;	
	
}
void iniciarBuscas(TGrafo *grafo)
{
int i;
 	for(i=0;i<grafo->n;i++)// seta cor branco e predecessor nill
{
		grafo->pi[i] = 0;
		grafo->cor[i] = 0;
		grafo->f[i] = 0;
		grafo->d[i]= 0;
		grafo->f[i]= 0;
	
}
	
}	

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "Portuguese");//habilita a acentuação para o português
  TGrafo grafo;
  int op, vert1, vert2, s;
 
  
  system("cls");

  
 
 do
 { 
  system("cls");
  printf("\t\t\tMATRIZ ADJACENCIAS\n");  
  imprimeGrafo(grafo); 
  imprimeMenu();
  scanf("%d", &op);
  
  if (op == 1) //Inserindo vértices
    insereVertice(&grafo);
  
  if (op == 2) //Inserindo arestas
   {
         printf("\nInserindo aresta...");
         printf("\t1o. vertice: ");
         scanf("%d", &vert1);
         printf("\n\t\t\t2o. vertice: ");
         scanf("%d", &vert2);
         if ((vert1< 0) || (vert1>=grafo.n) || (vert2<0) || (vert2>=grafo.n))
          {
            printf("\n\tVertice inexistente!");
            getch();
          }
         else
          if (vert1 == vert2)
            {
            printf("\n\tImpossivel inserir loop!");
            getch();
            }
            else
             insereAresta(&grafo,vert1,vert2);
         
            
   }
  
  
  if (op==3)
  {
    if (grafo.n == 0)
     printf("Nao existe grafo ainda...");
    else
    { 
     if(euleriano(grafo) == 0)
      printf("Nao eh euleriano!");
     else 
      printf("Eh euleriano!");
    }
    getch();
  }
  
 if(op==4)
 {
 	if(grafoCompleto(grafo) == 1){
		 printf("Completo");
	 }
 	
 	else{
 		printf("incompleto");
	 }	
 	getch(); 	
	
 }
 if(op==5){
 	completaGrafo(&grafo,grafo.n);
 }
 if(op==6)
 {
 	int aux = grafoArvore(grafo);
 	if(aux == 1)
	 {
 		printf("Grafo é uma arvore");
     }
 	else
 	{
 		printf("Não é uma arvore");
    }
 	getch();
 }
 if(op == 7)
 {
 	if(verticesPendentes(grafo) == 1)
 	{
		printf("Existem vertices pendentes") ;
	}
 	else
 	{
 		printf("Não existem vertices pendetes");
	}
 	getch();
 }
 if(op == 99)
 {
 	aleatorio(&grafo,grafo.n);
 	
 }
 if(op == 9)
 {
	int i;

	iniciarBuscas(&grafo);
 	buscaProfundidade(grafo);
 	
 		for(i=0;i<grafo.n;i++)
	{
			printf("Vertice[%d],Finaliza:%i ,Fila:%i \n",i,grafo.f[i],grafo.d[i]);	
	}
	getch();
 }
 if(op == 10)
 {
 	buscaProfundidade(grafo);
 	printf("\n\n%d, Componentes",grafo.comp);
 	getch();
 }
 } while(op!=0); 


// printf("\n\n"); 
 // system("PAUSE");	
  return 0;
}
