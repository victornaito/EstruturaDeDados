#include <stdio.h>
#include <stdlib.h> /* Para uso das funções malloc e free */

typedef struct cel {
	int info;
	int l; /* linha */
	int c; /* coluna */
	struct cel* s; /* prox linha */
	struct cel* e; /* prox coluna */
}Celula;

/* Cria uma matriz esparsa nula com n linhas e m colunas */
void inicializacao(Celula**, int, int);
/* Recebe uma matriz esparsa raiz(endereço da matriz) e imprime raiz */
void imprime(Celula*);
/* Atribui x a uma matriz esparsa raiz na linha l e coluna c */
void atribui(int x, int l, int c, Celula* raiz);
Celula* busca(int x, Celula* raiz);
Celula* soma(Celula* a, Celula* b);
Celula* multi(Celula*a, Celula* b);

int main()
{
	int n = 0;
	int m = 0;
	int x = 0;
	int l = 0;
	int c = 0;

	Celula* raiz = NULL;

	scanf("%d", &n);
	scanf("%d", &m);

	inicializacao(&raiz, n, m);

	printf("\nInsira x e sua coordenada: ");
	scanf("%d", &x);
	printf("\n Insira linha: ");
	scanf("%d", &l);
	printf("\nInsira coluna: ");
	scanf("%d", &c);
	atribui(x, l, c, raiz);

	imprime(raiz);

	/*for(i = 0; i < n; i++) 
		free(&raiz[i]); 
	printf("AQUI\n");
  	free(raiz);*/      
	
	return 0;
}

void inicializacao(Celula** raiz, int n, int m)
{
	int i = 0;
	Celula* ultima = NULL;
	Celula* ultim = NULL;
	Celula* atual;
	Celula* root;

	/* Criação da raiz */

	*raiz = (Celula*)malloc(sizeof(Celula));

	root = *raiz; /* estático */
	atual = *raiz; /* móvel */

	(*root).info = 0;
	(*root).l = -1;
	(*root).c = -1;

	/* Criação dos nós intermediários da lista de linhas, tirando o último nó */

	for(i = 0; i< n-1; i++)
	{
		Celula* linha = (Celula*) malloc(sizeof(Celula));
		(*atual).s = linha;
		(*atual).e = atual;
		linha->l = i;
		linha->c = -1;
		atual = linha; /* atual apontando para raíz */
	}

	/* Tratamento do último nó na criação das linhas */
	
	ultima = (Celula*) malloc(sizeof(Celula));
	(*atual).s = ultima;
	(*atual).e = atual;
	atual = ultima;
	ultima->s = root;
	ultima->e = ultima;
	ultima->l = n-1;
	ultima->c = -1;
	atual = (*atual).s; /* atual apontando para raíz */

	/* Fim do tratamento */	
		
	/* criaçao das colunas */

	for(i = 0; i< m-1; i++)
	{	
		Celula* coluna = (Celula*) malloc(sizeof(Celula));
		(*atual).e = coluna;
		coluna->s = coluna;
		atual = coluna;
		(*atual).c = i;
		(*atual).l = -1;
	} 
	
	/* Tratamento do último nó na criação das colunas */

	ultim = (Celula*) malloc(sizeof(Celula));
	(*atual).e = ultim;
	atual = ultim;
	(*atual).e = root; 
	(*atual).s = ultim;
	(*ultim).l = -1;
	(*ultim).c = m-1;

	atual = (*atual).e;

	printf("Fim do bloco inicializacao\n");	
}

void imprime(Celula* raiz)
{ 	
	int interation = 0;
	int i = 0;
	int tamLinha = 0;
	int tamColuna = 0;
	Celula* aux = NULL;
	Celula* aux2 = NULL;
	Celula* linha = NULL;
	Celula* percorreColuna = NULL;

	raiz = raiz->s;
	while(raiz->l != -1)
	{
		raiz = raiz->s;
		tamLinha++;
	}

	raiz = raiz->e;
	while(raiz->c != -1)
	{
		raiz = raiz->e;
		tamColuna++;
	}

	linha = raiz->s;
	percorreColuna = raiz->e;

	while(linha->l != -1)
	{
		if (linha->e == linha)
		{
			for(i = 0; i < tamColuna; i++)
			{
				printf(" 0 ");
			}
			printf("\n");
			linha = linha->s;
		}
		else
		{
			aux = linha;
			aux2 = linha->e;
			do
			{
				if(aux == linha)
				{
					interation = aux2->c - (aux->c + 1);
					for (i = 0; i < interation; i++)
					{
						printf(" 0 ");
					}
					printf(" %d ", aux2->info);	
					aux = aux->e;
					aux2 = aux2->e;
				}
				else if(aux2->c != -1)
				{
					interation = aux2->c - (aux->c + 1);
					for (i = 0; i < interation; i++)
					{
						printf(" 0 ");
					}
					printf(" %d ", aux2->info);	
					aux = aux->e;
					aux2 = aux2->e;
				}
				else if(aux2 == linha)
				{
					interation = tamColuna - (aux->c);
					for (i = 0; i < interation; i++)
					{
						printf(" 0 ");
					}
					
				}
				else if(aux2->e == linha)
				{
					linha = linha->s;
					printf(" 0 ");
				}
			}
			while(linha->c != -1);
		linha = linha->s;
		printf("\n");
		/*linha = linha->e;*/
		/*printf("%d %d\n",linha->l, linha->c);*/		
		}
	}		
}

void atribui(int x, int l, int c, Celula* raiz)
{
	Celula* linha = raiz;
	Celula* coluna = raiz;
	Celula* nova = NULL;
	Celula* percorreLinha = NULL;
	Celula* percorreColuna = NULL;
	Celula* aux = NULL;

	nova = (Celula*) malloc(sizeof(Celula));
	nova->info = x;
	nova->l = l;
	nova->c = c;

/* Percorrendo as linhas */

	while(linha->l < l)
	{
		linha = linha->s;
	}
	percorreLinha = linha; /* Guarda a referência da linha */

	while(coluna->c < c)
	{
		coluna = coluna->e;
	}
	percorreColuna = coluna; /* Guarda a referência da coluna */

	if (linha->e == linha && coluna->s == coluna)
	{
		linha->e = nova;
		nova->e = linha;
		nova->s = coluna;
		coluna->s = nova;
	}

	else if(linha->e != linha && coluna->s == coluna)
	{
		nova->s = coluna;
		coluna->s = nova;

		while(percorreLinha->c < c)
		{
			percorreLinha = percorreLinha->e; /* Ao final deste While, percorreLinha estará apontando para o anterior(linha anterior) */
		}
		aux = percorreLinha->e; /* aux apontará para o próximo elemento que será apontado pelo novo */
		percorreLinha->e = nova;
		nova->e = aux;
	}

	else if(linha->e == linha && coluna->s != coluna)
	{
		linha->e = nova;
		nova->e = linha;

		while(percorreLinha->l < l)
		{
			percorreColuna = percorreColuna->s; /* Ao final deste While, percorreColuna estará apontando para o anterior(linha anterior) */
		}
		aux = percorreColuna->s; /* aux apontará para o próximo elemento que será apontado pelo novo */
		percorreColuna->s = nova;
		nova->s = aux;
	}
}
