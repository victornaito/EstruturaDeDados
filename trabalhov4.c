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
Celula *buscaPeloIndice (Celula *raiz, int L, int C);
Celula* soma(Celula* a, Celula* b);
Celula* multi(Celula*a, Celula* b);

int main()
{
	int n = 0;
	int m = 0;
	int x = 0;
	int l = 0;
	int c = 0;
	int num, i;

	Celula* matrizA = NULL;
    Celula* matrizB = NULL;
    Celula* matrizC = NULL;

	printf("Insira a quantidade n de linhas da matriz A: ");
	scanf("%d", &n);
	printf("\nInsira a quantidade m de colunas da matriz A: ");
	scanf("%d", &m);
	inicializacao(&matrizA, n, m);

	printf("\nInsira a quantidade de números que você deseja inserir na matriz A: ");
	scanf("%d", &num);
	for(i = 0; i < num; i++)
	{
		printf("\nInsira o elemento X: ");
		scanf("%d", &x);
		printf("\n Insira a linha: ");
		scanf("%d", &l);
		printf("\nInsira a coluna: ");
		scanf("%d", &c);
		atribui(x, l, c, matrizA);
	}
    printf("\n");
	imprime(matrizA);

    printf("Insira a quantidade n de linhas da matriz B: ");
    scanf("%d", &n);
    printf("\nInsira a quantidade m de colunas da matriz B: ");
    scanf("%d", &m);
    inicializacao(&matrizB, n, m);

    printf("\n\nInsira a quantidade de números que você deseja inserir na matriz B: ");
    scanf("%d", &num);
    for(i = 0; i < num; i++)
    {
        printf("\nInsira o elemento X: ");
        scanf("%d", &x);
        printf("\n Insira a linha: ");
        scanf("%d", &l);
        printf("\nInsira a coluna: ");
        scanf("%d", &c);
        atribui(x, l, c, matrizB);
        
    }
    printf("\n");

    imprime(matrizB);

    matrizC = soma(matrizA, matrizB);

    printf("\n");
    imprime(matrizC);

   /* matrizC = soma(matrizA, matrizB);*/
    /*imprime(matrizC);*/

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
    int valor = 0;
    int i = 0;
    int tamLinha = 0;
    int tamColuna = 0;
    Celula* aux = NULL;
    Celula* linha = NULL;
    Celula* percorreLinha = NULL;

    // os 2 proximos while encontram o tamanho da matriz
    raiz = raiz->s;
    while(raiz->l != -1)
    {
        tamLinha++;
        raiz = raiz->s;
    }
    /*printf("tamLinha = %d\n", tamLinha);*/
    raiz = raiz->e;
    while(raiz->c != -1)
    {
        tamColuna++;
        raiz = raiz->e;
    }
    /*printf("tamColuna = %d\n", tamColuna);*/
    // fim encontrou tamanho matriz

    linha = raiz->s; // posiciona ponteiro em 0x-1
    percorreLinha = raiz->s; // posiciona ponteiro em 0x-1

            while(linha->l != -1)
            {
                aux = percorreLinha->e; // aux recebe prox
                if(aux == linha)
                { // linha vazia
                    for(i = 0; i < tamColuna; i++)
                    {
                        printf("0 "); // imprime zero para cada coluna
                    }
                    printf("\n");
                    linha = linha->s; // salta para prox linha
                    percorreLinha = linha;
                }else{
                    while(aux->c != -1){
                        valor = (percorreLinha->c) + 1;
                        for(i = valor; i < aux->c; i++){
                            printf("0 ");
                        }
                        printf("%d ", aux->info);
                        aux = aux->e;
                        percorreLinha = percorreLinha->e;
                        // unico numero na linha
                        if(aux->c == -1){ 
                            valor = (percorreLinha->c) + 1;
                            for(i = valor; i < tamColuna; i++){
                                printf("0 ");
                            }
                            printf("\n");
                        }
                    }
                    linha = linha->s;
                    percorreLinha = linha;
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

    // cria nova celula
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
    
    // percorrer coluna enquanto o indice da linha for 
    // inferior ou igual (caso ja exista uma celula no local) 
    // a a linha que quero inserir
    aux = percorreLinha->e;
    while(aux->c < c && aux->c != -1)
    {
        aux = aux->e;
        percorreLinha = percorreLinha->e;
    }
    if(aux->c == c)
    {
        aux->info = x;
        // destruir nova
    }
    else
    {
        nova->e = percorreLinha->e;
        percorreLinha->e = nova;
    }

    // percorrer linha enquanto o indice da coluna for
    // inferior ou igual (caso ja exista uma celula no local)
    // a a coluna que quero inserir
    aux = percorreColuna->s;
    while(aux->l < l && aux->l != -1){
        aux = aux->s;
        percorreColuna = percorreColuna->s;
    }
    if(aux->l == l){
        aux->info = x;
    }
    else{
        nova->s = percorreColuna->s;
        percorreColuna->s = nova;
    }
}

Celula* soma(Celula* a, Celula* b)
{
    Celula* matrizC = NULL;
    Celula* lC = NULL;
    Celula* cC = NULL;
    Celula* percorreLinhaC = NULL;
    Celula* percorreColunaC = NULL;
    Celula* novo = NULL;

    Celula* linhaA = a;
    Celula* colunaA = a;
    Celula* linhaB = b;
    Celula* colunaB = b;
    Celula* auxA = NULL;
    Celula* auxB = NULL;

    Celula* percorreLinhaA = NULL;
    Celula* percorreColunaA = NULL;
    Celula* percorreLinhaB = NULL;
    Celula* percorreColunaB = NULL;

    int booli;
    int indiceAuxA = 0;
    int indiceAuxB = 0;
    int tamLinhaA = 0;
    int tamColunaA = 0;
    int tamLinhaB = 0;
    int tamColunaB = 0;
    int resultado = 0;
     /* os 2 próximos while's encontram as dimensões da matriz A */
    a = a->s; /* tamanho da linha */
    while(a->l != -1)
    {
        tamLinhaA++;
        a = a->s;
    }
    a = a->e; /* tamanho da coluna */
    while(a->c != -1)
    {
        tamColunaA++;
        a = a->e;
    }
    /* Encontrou as dimensões da matriz A */

     /* os 2 próximos while's encontram as dimensões da matriz B */
    b = b->s;
    while(b->l != -1)
    {
        tamLinhaB++;
        b = b->s;
    }
    b = b->e;
    while(b->c != -1)
    {
        tamColunaB++;
        b = b->e;
    }
    /* Encontrou as dimensões da matriz B */
    linhaA = a->s; // posiciona ponteiro em 0x-1
    percorreLinhaA = a->s; // posiciona ponteiro em 0x-1
    linhaB = b->s; // posiciona ponteiro em 0x-1
    percorreLinhaB = b->s; // posiciona ponteiro em 0x-1
    auxA = a->e;
    auxA = auxA->s;
    auxB = b->e;
    auxB = auxB->s;

    /* Verifica se as matrizes possuem as mesmas dimensões */
    if(tamLinhaA == tamLinhaB && tamColunaA == tamColunaB)
    {
        /* Inicializar a matriz de resposta "matrizC" */
        inicializacao(&matrizC, tamLinhaA, tamColunaA);
        lC = matrizC->s;
        cC = matrizC->e;
        /*Percorrer posicão MatrizA[i][j], MatrizB[i][j]*/
        // percorreLinhaA = percorreLinhaA->s;
        // percorreLinhaB = percorreLinhaB->s;
        
        while(linhaA->l != -1 && linhaB->l != -1)
        {    
            /* caso as linhas não tenham elementos, pula para a próxima linha das matrizes A, B e C*/
            if(percorreLinhaA->e == percorreLinhaA && percorreLinhaB->e == percorreLinhaB)
            {
                percorreLinhaA = percorreLinhaA->s; 
                percorreLinhaB = percorreLinhaB->s;
                lC = lC->s; /* linha da matriz C */
            }
            /* caso da linha da matriz A ter elemento e a linha da matriz B não ter elemento */
            else if(percorreLinhaA->e != percorreLinhaA && percorreLinhaB->e == percorreLinhaB)
            {
                int linhaLA = percorreLinhaA->l;
                int linhaCA = percorreLinhaA->c;
                int info = percorreLinhaA->info;
                atribui(info, linhaLA, linhaCA, matrizC);
            }

                
            /* caso da linha da matriz A não ter elemento e a linha da matriz B ter elemento */
            else if(percorreLinhaA->e == percorreLinhaA && percorreLinhaB->e != percorreLinhaB)
            {
                int linhaLB = percorreLinhaB->l;
                int linhaCB = percorreLinhaB->c;
                int info = percorreLinhaB->info;
                atribui(info, linhaLB, linhaCB, matrizC);
            }   

            /* caso das duas linhas terem elementos */
            else if(auxA->c != -1 && auxB->c != -1)
            {
                int infoSoma = 0;
                // printf("%d %d\n", auxA->c, auxB->c);

                while(auxA->c != -1 && auxB->c != -1)
                {
                    if(auxA->c == auxB->c)
                    {   
                        infoSoma = auxA->info + auxB->info;
                        // printf("info: %d\n", infoSoma);
                        atribui(infoSoma, auxA->l, auxA->c, matrizC);
                        auxA = auxA->e;
                        auxB = auxB->e;
                    }

                    else if(auxB->c < auxA->c)
                    {
                        while(auxB->e != percorreLinhaB && auxB->c < auxA->c)
                        {
                            atribui(auxB->info, auxB->l, auxB->c, matrizC);
                            auxB = auxB->e;
                        }
                    }
                    else if(auxA->c < auxB->c)
                    {
                        while(auxA->e != percorreLinhaA && auxA->c < auxB->c)
                        {
                            atribui(auxA->info, auxA->l, auxA->c, matrizC);
                            auxA = auxA->e;
                        }
                    }
                    if(auxA->c == -1 && auxB->c == -1)
                    { 
                        auxA = auxA->s;
                        auxA = auxA->e;
                        auxB = auxB->s;
                        auxB = auxB->e;
                        break;
                    } 
                      
                }
                if(percorreLinhaA->e == percorreLinhaA)
                {
                    while(auxB->e != percorreLinhaB)
                    {
                        atribui(auxB->info, auxB->l, auxB->c, matrizC);
                        auxB = auxB->e;
                    }
                }

                if(percorreLinhaB->e == percorreLinhaB)
                {
                    while(auxA->e != percorreLinhaA)
                    {
                        atribui(auxA->info, auxA->l, auxA->c, matrizC);
                        auxA = auxA->e;
                    }
                } 
                //auxA = auxA->e;  auxB = auxB->e;
            }
            linhaA = linhaA->s;
            linhaB = linhaB->s;
            
        }
    }
    return matrizC;
}
