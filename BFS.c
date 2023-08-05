#include <stdio.h>
#include <stdlib.h>

struct GRAFO{
struct VERTICE *head;
};

struct VERTICE{
struct VERTICE *next;
struct ARESTA *aresta;
int chave;
};

struct ARESTA{
struct ARESTA *next;
struct ARESTA *tail;
struct VERTICE *adj;
};

struct NODE{	
int conteudo;
struct NODE *next; 
};

struct FILA{
struct NODE *head;
struct NODE *tail;
};

typedef struct ARESTA ARESTA;
typedef struct VERTICE VERTICE;
typedef struct GRAFO GRAFO;
typedef struct NODE NODE;
typedef struct FILA FILA;

GRAFO *cria_grafo();
VERTICE *busca_vertice(GRAFO *g, int chave);
void cria_vertice(GRAFO *g, int chave);
void cria_aresta(GRAFO *g, int chave1, int chave2);
void imprimi_grafo(GRAFO *g);
void imprimi_estruturas_bfs(int v, int *d, int *p, char *c);

FILA *cria_fila();
void enqueue(FILA *f, int num);
void dequeue(FILA *f);
void imprimi_fila(FILA *f);

void BFS(GRAFO *g, FILA *f, int vertice_inicio, int v, int *d, int *p, char *c, int cont);

int main(){

	GRAFO *g = cria_grafo();

	int vertice, aresta, vertice_inicio, a, b;
	scanf("%d %d %d", &vertice, &aresta, &vertice_inicio);

	for(int i = 0; i < vertice+1; ++i)
		cria_vertice(g, i);

	while(scanf("%d %d", &a, &b) != EOF)
		cria_aresta(g, a, b);

	int distancia[vertice+1];
	int pred[vertice+1];
	char cor[vertice+1];

	for(int i = 0; i < vertice+1; ++i){
		cor[i] = 'w';
		pred[i] = -1;
		distancia[i] = -1;
	}


	FILA *f = cria_fila();
	BFS(g, f, vertice_inicio, vertice, distancia, pred, cor, 0);
	
	return 0;
	
}

GRAFO *cria_grafo(){
	GRAFO *new_graph = (GRAFO*) malloc(sizeof(GRAFO));
	new_graph->head = NULL;

	return new_graph;
}

VERTICE *busca_vertice(GRAFO *g, int chave){
	VERTICE *aux = g->head;
	
	while(aux != NULL && aux->chave != chave)
		aux = aux->next;
	
	return aux;
}

void cria_vertice(GRAFO *g, int chave){
	if(g == NULL)
		return;

	VERTICE *new_vertice = (VERTICE*) malloc(sizeof(VERTICE));
	new_vertice->chave = chave;
	new_vertice->next = g->head;

	g->head = new_vertice;

	return;
}

void cria_aresta(GRAFO *g, int chave1, int chave2){
	if(g == NULL)
		return;

	VERTICE *v1 = busca_vertice(g, chave1);
	if(v1 == NULL)
		return;

	VERTICE *v2 = busca_vertice(g, chave2);
	if(v2 == NULL)
		return;

	ARESTA *new_aresta1  = (ARESTA*) malloc(sizeof(ARESTA));
	ARESTA *new_aresta2  = (ARESTA*) malloc(sizeof(ARESTA));

	new_aresta1->adj = v2;
	new_aresta1->next = NULL;

	new_aresta2->adj = v1;
	new_aresta2->next = NULL;

	if(v1->aresta == NULL){
		v1->aresta = new_aresta1;
		v1->aresta->tail = new_aresta1;		
	} else {
		v1->aresta->tail->next = new_aresta1;
		v1->aresta->tail = new_aresta1;
	}

	if(v2->aresta == NULL){
		v2->aresta = new_aresta2;
		v2->aresta->tail = new_aresta2;
	} else {
		v2->aresta->tail->next = new_aresta2;
		v2->aresta->tail = new_aresta2;
	}

	return;

}

void imprimi_grafo(GRAFO *g){
    if (g == NULL)
    	return;
    
    VERTICE *v_aux = g->head;

    while(v_aux != NULL){
        printf("%d ->", v_aux->chave);

        ARESTA *a_aux = v_aux->aresta;
        
        while(a_aux != NULL){
            printf(" %d", a_aux->adj->chave);
            a_aux = a_aux->next;
        }
        puts("");
 		
 		v_aux = v_aux->next;

    	free(a_aux);
    }
    free(v_aux);
    return;
}

FILA *cria_fila(){
	FILA *new_fila = (FILA*) malloc(sizeof(FILA));
	new_fila->head = NULL;
	new_fila->tail = NULL;

	return new_fila;
}

void enqueue(FILA *f, int num) {
	NODE *new_node = (NODE*) malloc(sizeof(NODE));
	new_node-> conteudo = num;
	if (f->head == NULL && f->tail == NULL) {
		f->head = new_node;
		f->tail = new_node;
	} else {
		f->tail->next = new_node;
		f->tail = new_node;
	}
	
	new_node->next = NULL;
	return;
}

void dequeue(FILA *f){
	if (f->head == f->tail && f->head != NULL){
		free(f->head);
		f->head = NULL;
		f->tail = NULL;
	} else {
		NODE *aux = f->head->next;
		free(f->head);
		f->head = aux;
	} 
	return;
}

void imprimi_fila(FILA *f){
	printf("FILA: ");
	NODE *aux = f->head;
	while (aux != NULL){
		printf("%d -> ", aux->conteudo);
		aux = aux->next;
	}
	printf("NULL\n\n");
	free(aux);
	return;
}

void imprimi_estruturas_bfs(int v, int *d, int *p, char *c){
	printf(" v   d  p  c\n");
	for(int i = 0; i < v+1; ++i){
		printf("%2d: %2d %2d %2c\n", i, d[i], p[i], c[i]);
	}
}       
    
void BFS(GRAFO *g, FILA *f, int vertice_inicio, int v, int *d, int *p, char *c, int cont){
	if(c[vertice_inicio] == 'b')
		return;

	if(cont == 0){
		enqueue(f, vertice_inicio);
		c[vertice_inicio] = 'g';
		d[vertice_inicio] = 0;
		p[vertice_inicio] = 0;

	}

	++cont;

	VERTICE *v_aux = busca_vertice(g, vertice_inicio);
	ARESTA *a_aux = v_aux->aresta;
        
 
    while(a_aux != NULL){
    	if(c[a_aux->adj->chave] == 'w'){
	    	enqueue(f, a_aux->adj->chave);
	        c[a_aux->adj->chave] = 'g';
	        d[a_aux->adj->chave] = d[vertice_inicio] + 1;
	    	p[a_aux->adj->chave] = vertice_inicio;
    	}
    	
	    a_aux = a_aux->next;
    }

    c[vertice_inicio] = 'b';
    dequeue(f);

    printf("ITERAÇÃO %d:\n", cont);
	imprimi_estruturas_bfs(v, d, p, c);
    printf("\n");
    imprimi_fila(f);
    printf("\n");

    if(f->head == NULL){
    	return;
    }
   
   	BFS(g, f, f->head->conteudo, v, d, p, c, cont);
   	return;
}
